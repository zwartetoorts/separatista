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
XERCES_CPP_NAMESPACE_END;
#else
// Forward declare xerces classes
namespace xercesc
{
	class DOMDocument;
	class XercesDOMParser;
};
#endif

namespace Separatista
{

/**
	Base class for all Separatista documents.
*/
class SeparatistaDocument
{
public:
	SEPARATISTA_EXTERN SeparatistaDocument();
	SEPARATISTA_EXTERN virtual ~SeparatistaDocument();

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
		Default contructor for creating an new document
	*/
	SEPARATISTA_EXTERN DirectDebitDocument();

	/**
		Construct a document from a source
	*/
	SEPARATISTA_EXTERN DirectDebitDocument(xercesc::DOMDocument *pDocument);

	SEPARATISTA_EXTERN virtual ~DirectDebitDocument();

	/**
	Namespace URI
	*/
	SEPARATISTA_EXTERN static const wchar_t *NamespaceURI;
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

	SEPARATISTA_EXTERN const DocumentStatus readDocument(const wchar_t *path);

	/// Set schema validation, default is true
	SEPARATISTA_EXTERN void setValidate(bool validate);

	SEPARATISTA_EXTERN bool getValidate() const;

private:
	wchar_t* m_path;
	DocumentStatus m_status;
	wchar_t *m_pErrorMessage;
	SeparatistaDocument *m_pDocument;
	bool m_validate;
};

};

#endif // !defined SEPARATISTA_H

