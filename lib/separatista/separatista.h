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
#include <ctime>
#include <cinttypes>


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

namespace SeparatistaPrivate
{
	// Forward decl
	class CustomerDirectDebitInitiationV02;
	typedef CustomerDirectDebitInitiationV02 CustomerDirectDebitInitiation;
};

namespace Separatista
{

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

#define SEPARATISTA_DECLARE_TAG_GET(name) \
	virtual const wchar_t* get##name() = 0;

#define SEPARATISTA_DECLARE_TAG_SET(name) \
	virtual void set##name(const wchar_t *pValue) = 0;

#define SEPARATISTA_DECLARE_TAG(name) \
	SEPARATISTA_DECLARE_TAG_GET(name) \
	SEPARATISTA_DECLARE_TAG_SET(name)

#define SEPARATISTA_DECLARE_TAG_TIME_GET(name) \
	virtual std::time_t get##name() = 0;

#define SEPARATISTA_DECLARE_TAG_TIME(name) \
	SEPARATISTA_DECLARE_TAG_TIME_GET(name) \
	SEPARATISTA_DECLARE_TAG_SET(name)

#define SEPARATISTA_DECLARE_TAG_LONG_GET(name) \
	virtual long get##name() = 0;

#define SEPARATISTA_DECLARE_TAG_LONG(name) \
	SEPARATISTA_DECLARE_TAG_LONG_GET(name) \
	SEPARATISTA_DECLARE_TAG_SET(name)

#define SEPARATISTA_DECLARE_TAG_UINT64_GET(name) \
	virtual uint64_t get##name() = 0;

#define SEPARATISTA_DECLARE_TAG_UINT64(name) \
	SEPARATISTA_DECLARE_TAG_UINT64_GET(name) \
	SEPARATISTA_DECLARE_TAG_SET(name)

#define SEPARATISTA_DECLARE_TAG_CLASS_GET(cls, name) \
	virtual cls& get##name() = 0;

#define SEPARATISTA_DECLARE_TAG_CLASS(cls, name) \
	SEPARATISTA_DECLARE_TAG_CLASS_GET(cls, name)

#define SEPARATISTA_DECLARE_TAG_TYPE_GET(type, name) \
	virtual type get##name() = 0;

#define SEPARATISTA_DECLARE_TAG_TYPE(type, name) \
	SEPARATISTA_DECLARE_TAG_TYPE_GET(type, name) \
	virtual void set##name(type val) = 0;

#define SEPARATISTA_DECLARE_CHILD(type, name) \
	SEPARATISTA_DECLARE_TAG_CLASS_GET(type, name)

#define SEPARATISTA_DECLARE_CHILD_MULTI(type, name) \
	virtual type& get##name(size_t index) = 0;

#define SEPARATISTA_DECLARE_TAG_MULTI(name) \
	virtual const wchar_t* get##name(size_t index) = 0;

#define SEPARATISTA_DECLARE_TAG_ENUM(type, name) \
	SEPARATISTA_DECLARE_TAG_TYPE(type, name)

class CashAccount16
{
public:
	SEPARATISTA_DECLARE_TAG(Identification);
	SEPARATISTA_DECLARE_TAG(Type);
	SEPARATISTA_DECLARE_TAG(Currency);
	SEPARATISTA_DECLARE_TAG(Name);
};

class CodeOrProprietary
{
public:
	SEPARATISTA_DECLARE_TAG(Code);
	SEPARATISTA_DECLARE_TAG(Proprietary);
};

class BranchAndFinancialInstitutionIdentification4
{
	SEPARATISTA_DECLARE_TAG(FinancialInstitutionIdentification)
	SEPARATISTA_DECLARE_TAG(BranchIdentification)
};

class PaymentTypeInformation20
{
public:
	SEPARATISTA_DECLARE_TAG(InstructionPriority)
	SEPARATISTA_DECLARE_TAG_CLASS(CodeOrProprietary, ServiceLevel)
	SEPARATISTA_DECLARE_TAG_CLASS(CodeOrProprietary, LocalInstrument)
	SEPARATISTA_DECLARE_TAG(SequenceType)
	SEPARATISTA_DECLARE_TAG_CLASS(CodeOrProprietary, CategoryPurpose)
};

class GenericOrganisationIdentification1
{
public:
	SEPARATISTA_DECLARE_TAG(Identification)
	SEPARATISTA_DECLARE_CHILD(CodeOrProprietary, SchemeName)
	SEPARATISTA_DECLARE_TAG(Issuer)
};

class OrganisationIdentification8
{
public:
	SEPARATISTA_DECLARE_TAG(AnyBIC)
	SEPARATISTA_DECLARE_CHILD(GenericOrganisationIdentification1, Other)
};

class DateAndPlaceOfBirth
{
public:
	SEPARATISTA_DECLARE_TAG_TIME(BirthDate)
	SEPARATISTA_DECLARE_TAG(ProvinceOfBirth)
	SEPARATISTA_DECLARE_TAG(CityOfBirth)
	SEPARATISTA_DECLARE_TAG(CountryOfBirth)
};

class PersonIdentification5
{
public:
	SEPARATISTA_DECLARE_CHILD(DateAndPlaceOfBirth, DateAndPlaceOfBirth)
	SEPARATISTA_DECLARE_CHILD(GenericOrganisationIdentification1, Other)
};

class Party11Choice
{
public:
	SEPARATISTA_DECLARE_CHILD(OrganisationIdentification8, OrganisationIdentification)
	SEPARATISTA_DECLARE_CHILD(PersonIdentification5, PrivateIdentification)

};

enum AddressType2Code
{
	AddressType2CodeError = 0,
	Postal,
	POBox,
	Residential,
	Business,
	MailTo,
	DeliveryTo
};

class PostalAddress6
{
public:
	SEPARATISTA_DECLARE_TAG_ENUM(AddressType2Code, AddressType)
	SEPARATISTA_DECLARE_TAG(Department)
	SEPARATISTA_DECLARE_TAG(SubDepartment)
	SEPARATISTA_DECLARE_TAG(StreetName)
	SEPARATISTA_DECLARE_TAG(BuildingNumber)
	SEPARATISTA_DECLARE_TAG(PostCode)
	SEPARATISTA_DECLARE_TAG(TownName)
	SEPARATISTA_DECLARE_TAG(CountrySubDivision)
	SEPARATISTA_DECLARE_TAG(Country)
	SEPARATISTA_DECLARE_TAG_MULTI(AddressLine)
};

enum NamePrefix1Code
{
	NamePrefix1CodeError = 0,
	Doctor,
	Mister,
	Miss,
	Madam
};

class ContactDetails2
{
public:
	SEPARATISTA_DECLARE_TAG_ENUM(Separatista::NamePrefix1Code, NamePrefix)
	SEPARATISTA_DECLARE_TAG(Name)
	SEPARATISTA_DECLARE_TAG(PhoneNumber)
	SEPARATISTA_DECLARE_TAG(MobileNumber)
	SEPARATISTA_DECLARE_TAG(FaxNumber)
	SEPARATISTA_DECLARE_TAG(EmailAddress)
	SEPARATISTA_DECLARE_TAG(Other)
};

class PartyIdentification43
{
public:
	SEPARATISTA_DECLARE_TAG(Name)
	SEPARATISTA_DECLARE_TAG_CLASS(PostalAddress6, PostalAddress)
	SEPARATISTA_DECLARE_CHILD(Party11Choice, Identification)
	SEPARATISTA_DECLARE_TAG(CountryOfResidence)
	SEPARATISTA_DECLARE_CHILD(ContactDetails2, ContactDetails)
};

class PaymentInstructionInformation4
{
	SEPARATISTA_DECLARE_CHILD(PaymentTypeInformation20, PaymentTypeInformation)
	SEPARATISTA_DECLARE_CHILD(PartyIdentification43, Creditor)
	SEPARATISTA_DECLARE_CHILD(CashAccount16, CreditorAccount)
	SEPARATISTA_DECLARE_CHILD(BranchAndFinancialInstitutionIdentification4, CreditorAgent)
	SEPARATISTA_DECLARE_CHILD(PartyIdentification43, UltimateCreditor)
	SEPARATISTA_DECLARE_CHILD(PartyIdentification43, CreditorSchemeIdentification)
	SEPARATISTA_DECLARE_TAG(PaymentInformationIdentification)
	SEPARATISTA_DECLARE_TAG(PaymentMethod)
	SEPARATISTA_DECLARE_TAG(BatchBooking)
	SEPARATISTA_DECLARE_TAG_GET(NumberOfTransactions)
	SEPARATISTA_DECLARE_TAG_GET(ControlSum)
	SEPARATISTA_DECLARE_TAG(RequestedCollectionDate)
	SEPARATISTA_DECLARE_TAG(CreditorAgentAccount)
	SEPARATISTA_DECLARE_TAG(ChargeBearer)
	SEPARATISTA_DECLARE_TAG(ChargesAccount)
	SEPARATISTA_DECLARE_TAG(ChargesAccountAgent)
public:
	static const wchar_t *DirectDebit;
};

class GroupHeader55
{
	SEPARATISTA_DECLARE_CHILD(PartyIdentification43, InitiatingParty)
	SEPARATISTA_DECLARE_TAG(MessageIdentification)
	SEPARATISTA_DECLARE_TAG_TIME(CreationDateTime)
	SEPARATISTA_DECLARE_CHILD_MULTI(CodeOrProprietary, Authorisation)
	SEPARATISTA_DECLARE_TAG_GET(NumberOfTransactions)
	SEPARATISTA_DECLARE_TAG_GET(ControlSum)
	SEPARATISTA_DECLARE_TAG(ForwardingAgent)
};

class DirectDebitDocument : public SeparatistaDocument
{
public:
	/**
		Default contructor for creating an new document, will create a whole new empty DOMDocument
		and initialize the minimal tags
	*/
	SEPARATISTA_EXTERN DirectDebitDocument();

	/**
		Construct a document from a source DOMDocument
	*/
	SEPARATISTA_EXTERN DirectDebitDocument(xercesc::DOMDocument *pDocument);

	/// Destructor
	SEPARATISTA_EXTERN ~DirectDebitDocument();

	SEPARATISTA_EXTERN const SeparatistaDocument::DocumentType getDocumentType() const;

	/// Namespace URI
	SEPARATISTA_EXTERN static const wchar_t *NamespaceURI;
	
	/// Get the GroupHeader for this document
	SEPARATISTA_EXTERN GroupHeader55* getGroupHeader();

	// PaymentInstructionInformation methods
	/// True if we are the end of all PaymentInformations
	SEPARATISTA_EXTERN bool FEOF();
	/// Resets the internal pointer to the first PaymentInformation
	SEPARATISTA_EXTERN void moveFirst();
	/// Moves the internal pointer to the next PaymentInformation
	SEPARATISTA_EXTERN void moveNext();
	/// Get the count of PaymentInformations
	SEPARATISTA_EXTERN size_t getCount();
	/// Get the current PaymentInformation
	SEPARATISTA_EXTERN PaymentInstructionInformation4* getPaymentInstructionInformation();

protected:
	SeparatistaPrivate::CustomerDirectDebitInitiation *m_pCstmrDrctDbtInitn;
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

