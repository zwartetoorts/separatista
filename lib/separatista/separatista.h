/***************************************************************************
 *   Copyright (C) 2013 by Okkel Klaver   *
 *   info@vanhetland.nl   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <vector>

#ifndef SEPARATISTA_H
#define SEPARATISTA_H

#ifdef SEPARATISTA_BUILDINGDLL
#	define SEPARATISTA_EXTERN __declspec(dllexport)
#elif defined SEPARATISTA_USINGDLL
#		define SEPARATISTA_EXTERN __declspec(dllimport)
#else
#	define SEPARATISTA_EXTERN
#endif

/**
	Check for xerces headers being included, if not, were not building separatista.
	This means it's neccessary to include xerces headers BEFORE separatista headers.
	All this fuzz is needed because xerces aliases it's namespace so we can't forward declare it.
*/
#ifdef XERCES_HAS_CPP_NAMESPACE
XERCES_CPP_NAMESPACE_BEGIN
class DOMDocument;
class XercesDOMParser;
class SAXParseException;
XERCES_CPP_NAMESPACE_END;
#else
// Forward declare xerces classes
namespace xercesc
{
	class DOMDocument;
	class XercesDOMParser;
	class SAXParseException;
};
#endif

namespace Separatista
{

// Forward decl
class CustomerDirectDebitInitiationV02;
typedef CustomerDirectDebitInitiationV02 CustomerDirectDebitInitiation;

/**
	Error message, collects all error messages. Error message mainly come from xerces exceptions or errors and warnings.
*/
class ErrorMessage
{
public:
	enum ErrorMessageType
	{
		M_WARNING,
		M_ERROR,
		M_FATALERROR
	};

	SEPARATISTA_EXTERN ErrorMessage(ErrorMessageType type);
	SEPARATISTA_EXTERN ErrorMessage(ErrorMessageType type, const xercesc::SAXParseException &e);

	SEPARATISTA_EXTERN ~ErrorMessage();

	SEPARATISTA_EXTERN ErrorMessageType getType() const;
	SEPARATISTA_EXTERN void setType(ErrorMessageType type);

	SEPARATISTA_EXTERN const wchar_t* getPublicId() const;
	SEPARATISTA_EXTERN void setPublicId(const wchar_t *pPublicId);

	SEPARATISTA_EXTERN const wchar_t* getSystemId() const;
	SEPARATISTA_EXTERN void setSystemId(const wchar_t *pSystemId);

	SEPARATISTA_EXTERN const wchar_t* getErrorMessage() const;
	SEPARATISTA_EXTERN void setErrorMessage(const wchar_t *pErrorMessage);

	SEPARATISTA_EXTERN size_t getLineNumber() const;
	SEPARATISTA_EXTERN void setLineNumber(size_t lineNumber);
	
	SEPARATISTA_EXTERN size_t getColumnNumber() const;
	SEPARATISTA_EXTERN void setColumnNumber(size_t columnNumber);
private:
	ErrorMessageType m_type;
	wchar_t *m_pPublicId;
	wchar_t *m_pSystemId;
	wchar_t *m_pErrorMessage;
	size_t m_lineNumber;
	size_t m_columnNumber;
};
	
/**
	Error report. Simple class to enumerate the ErrorMessages in a std::vector<ErrorMessage*> list.
*/
class ErrorReport
{
public:
	SEPARATISTA_EXTERN ErrorReport();
	SEPARATISTA_EXTERN ErrorReport(std::vector<ErrorMessage*> *pErrorList);

	SEPARATISTA_EXTERN void setErrorList(std::vector<ErrorMessage*> *pErrorList);

	/// Get the number of errors
	SEPARATISTA_EXTERN size_t getCount() const;

	/// Get the message at index
	SEPARATISTA_EXTERN const ErrorMessage* getErrorMessage(size_t index);

	/// Move to first message
	SEPARATISTA_EXTERN void reset();

	/// Get message and move to next
	/// @return NULL if there are no more error to report 
	SEPARATISTA_EXTERN const ErrorMessage* getErrorMessage();

private:
	std::vector<ErrorMessage*> *m_pErrorList;
	std::vector<ErrorMessage*>::iterator m_iterator;
};

/**
	Base class for all Separatista documents.
*/
class SeparatistaDocument
{
public:
	SEPARATISTA_EXTERN SeparatistaDocument();
	SEPARATISTA_EXTERN virtual ~SeparatistaDocument();

	enum DocumentType
	{
		DirectDebitDocumentType
	};

	SEPARATISTA_EXTERN virtual const DocumentType getDocumentType() const = 0;

	/// Get error message
	SEPARATISTA_EXTERN const wchar_t* getErrorMessage() const;

	/// Releases the previous error message
	SEPARATISTA_EXTERN void setErrorMessage(const wchar_t* pErrorMessage);

	/// Get DOM Document
	SEPARATISTA_EXTERN xercesc::DOMDocument* getDOMDocument() const;
	SEPARATISTA_EXTERN void setDOMDocument(xercesc::DOMDocument* pDocument);

	/// Get the file path
	SEPARATISTA_EXTERN const wchar_t* getPath() const;
	SEPARATISTA_EXTERN void setPath(const wchar_t *pPath);

	/**
		Tries to fit a SeparatistaDocument subclass to a given DOMDocument.
		@return A pointer to the SeparatistaDocument subclass or NULL if not found
	*/
	SEPARATISTA_EXTERN static SeparatistaDocument* getByDOMDocument(xercesc::DOMDocument* pDOMDocument);

	/**
	Platform specific implementation of loading grammar into xerces. Windows uses resources to ship xsd definitions.
	@param parser The parser to load the grammar into.
	@return true on success, false on fail
	*/
	SEPARATISTA_EXTERN static bool loadSchemas(xercesc::XercesDOMParser *parser);

	/// Document element tag name
	SEPARATISTA_EXTERN static const wchar_t *Document;

protected:
	/// Error message, protected access for convenience
	wchar_t *m_pErrorMessage;

private:
	xercesc::DOMDocument *m_pDOMDocument;
	wchar_t *m_path;
};

/**
	
*/
class DirectDebitDocument : public SeparatistaDocument
{
public:
	/**
		Default contructor for creating an new document, will create a whole new empty DOMDocument
	*/
	SEPARATISTA_EXTERN DirectDebitDocument();

	/**
		Construct a document from a source DOMDocument
	*/
	SEPARATISTA_EXTERN DirectDebitDocument(xercesc::DOMDocument *pDocument);

	SEPARATISTA_EXTERN ~DirectDebitDocument();

	SEPARATISTA_EXTERN const SeparatistaDocument::DocumentType getDocumentType() const;

	/// Namespace URI
	SEPARATISTA_EXTERN static const wchar_t *NamespaceURI;

protected:
	CustomerDirectDebitInitiation *m_pCstmrDrctDbtInitn;
private:
};


/**
	Separatista file reader class.
*/
class SeparatistaFileReader
{
public:
	SEPARATISTA_EXTERN SeparatistaFileReader();

	SEPARATISTA_EXTERN virtual ~SeparatistaFileReader();

	/**
		Code indicating success or failure reading a file
	*/
	enum DocumentStatus
	{
		/// Success
		OK = 0,
		/// Error opening/reading file
		E_FILE,
		/// Error parsing file or not a valid XML file
		E_FORMAT,
		/// No memory available
		E_MEMORY
	};

	/// Returns error message
	SEPARATISTA_EXTERN const wchar_t* getErrorMessage() const;

	/// Releases the previous error message
	SEPARATISTA_EXTERN void setErrorMessage(const wchar_t *pErrorMessage);

	/// Get status
	SEPARATISTA_EXTERN const DocumentStatus getStatus() const;

	SEPARATISTA_EXTERN void setStatus(const DocumentStatus status);

	/// Get document
	SEPARATISTA_EXTERN SeparatistaDocument* getDocument() const;

	SEPARATISTA_EXTERN void setDocument(SeparatistaDocument *pDocument);

	/// Get path the file was loaded from
	SEPARATISTA_EXTERN const wchar_t* getPath() const;

	/**
	Try to read a xml document. If validation is on, the document is checked with all supported xml format
	schemas. 
	@see setValidate
	*/
	SEPARATISTA_EXTERN const DocumentStatus readDocument(const wchar_t *path);

	/// Set schema validation, default is true
	SEPARATISTA_EXTERN void setValidate(bool validate);

	SEPARATISTA_EXTERN bool getValidate() const;

	/// Get the ErrorReport
	SEPARATISTA_EXTERN ErrorReport& getErrorReport();

private:
	wchar_t* m_path;
	DocumentStatus m_status;
	wchar_t *m_pErrorMessage;
	SeparatistaDocument *m_pDocument;
	bool m_validate;
	std::vector<ErrorMessage*> m_errorMessages;
	ErrorReport m_errorReport;
};

};

#endif // !defined SEPARATISTA_H

