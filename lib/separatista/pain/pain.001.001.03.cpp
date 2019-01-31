

#include "separatista/elementdescriptor.h"
#include "separatista/leafelement.h"
#include "separatista/attributedleafelement.h"
#include "separatista/branchelement.h"
#include "separatista/choiceelement.h"
#include "separatista/validator.h"
#include "pain.001.001.03.h"

namespace Separatista
{
	namespace pain_001_001_03 
	{
		const wchar_t* Namespace = TEXT("urn:iso:std:iso:20022:tech:xsd:pain.001.001.03");
		
    
		const Separatista::ChildElementDescriptor DocumentElementDescriptor = 
		{
			SEPARATISTA_TAG("Document"), // Tag
			1,			// Min
			1,			// Max
			&Document
		};

    
		static const Separatista::ElementDescriptor AccountIdentification4Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			AccountIdentification4ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AccountIdentification4ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("IBAN"),				// Tag
					1,																// Min
					1,																// Max
					&IBAN2007Identifier							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Othr"),				// Tag
					1,																// Min
					1,																// Max
					&GenericAccountIdentification1							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor AccountSchemeName1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			AccountSchemeName1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AccountSchemeName1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalAccountIdentification1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_ActiveOrHistoricCurrencyAndAmount_SimpleType(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDecimal(pValue, pElement);
			
			Separatista::Validator::validateMinInclusive(pValue, TEXT("0"), pElement);
					
			Separatista::Validator::validateFractionDigits(pValue, TEXT("5"), pElement);
					
			Separatista::Validator::validateTotalDigits(pValue, TEXT("18"), pElement);
					
		}

		static const Separatista::ElementDescriptor ActiveOrHistoricCurrencyAndAmount_SimpleType = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ActiveOrHistoricCurrencyAndAmount_SimpleType ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor ActiveOrHistoricCurrencyAndAmount =
		{
			&ActiveOrHistoricCurrencyAndAmount_SimpleType,				// Parent type
			Separatista::AttributedLeafElement::createElement,				// Creator
			NULL,															// Validator
			0,																// Child element count
			NULL															// Child element descriptors
		};
		
    
		void validate_ActiveOrHistoricCurrencyCode(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[A-Z]{3,3}"), pElement);
					
		}

		static const Separatista::ElementDescriptor ActiveOrHistoricCurrencyCode = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ActiveOrHistoricCurrencyCode ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_AddressType2Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("ADDR"),

					TEXT("PBOX"),

					TEXT("HOME"),

					TEXT("BIZZ"),

					TEXT("MLTO"),

					TEXT("DLVY")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor AddressType2Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_AddressType2Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor AmountType3Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			AmountType3ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AmountType3ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("InstdAmt"),				// Tag
					1,																// Min
					1,																// Max
					&ActiveOrHistoricCurrencyAndAmount							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("EqvtAmt"),				// Tag
					1,																// Min
					1,																// Max
					&EquivalentAmount2							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_AnyBICIdentifier(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[A-Z]{6,6}[A-Z2-9][A-NP-Z0-9]([A-Z0-9]{3,3}){0,1}"), pElement);
					
		}

		static const Separatista::ElementDescriptor AnyBICIdentifier = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_AnyBICIdentifier ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor Authorisation1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			Authorisation1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor Authorisation1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&Authorisation1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max128Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_Authorisation1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("AUTH"),

					TEXT("FDET"),

					TEXT("FSUM"),

					TEXT("ILEV")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor Authorisation1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Authorisation1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_BICIdentifier(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[A-Z]{6,6}[A-Z2-9][A-NP-Z0-9]([A-Z0-9]{3,3}){0,1}"), pElement);
					
		}

		static const Separatista::ElementDescriptor BICIdentifier = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_BICIdentifier ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_BaseOneRate(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDecimal(pValue, pElement);
			
			Separatista::Validator::validateFractionDigits(pValue, TEXT("10"), pElement);
					
			Separatista::Validator::validateTotalDigits(pValue, TEXT("11"), pElement);
					
		}

		static const Separatista::ElementDescriptor BaseOneRate = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_BaseOneRate ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_BatchBookingIndicator(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateBoolean(pValue, pElement);
			
		}

		static const Separatista::ElementDescriptor BatchBookingIndicator = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_BatchBookingIndicator ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor BranchAndFinancialInstitutionIdentification4 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			BranchAndFinancialInstitutionIdentification4ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BranchAndFinancialInstitutionIdentification4ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("FinInstnId"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&FinancialInstitutionIdentification7								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BrnchId"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchData2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor BranchData2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			BranchData2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BranchData2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PstlAdr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PostalAddress6								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CashAccount16 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			CashAccount16ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CashAccount16ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&AccountIdentification4Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccountType2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ccy"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max70Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CashAccountType2 = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			CashAccountType2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CashAccountType2ChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&CashAccountType4Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_CashAccountType4Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CASH"),

					TEXT("CHAR"),

					TEXT("COMM"),

					TEXT("TAXE"),

					TEXT("CISH"),

					TEXT("TRAS"),

					TEXT("SACC"),

					TEXT("CACC"),

					TEXT("SVGS"),

					TEXT("ONDP"),

					TEXT("MGLD"),

					TEXT("NREX"),

					TEXT("MOMA"),

					TEXT("LOAN"),

					TEXT("SLRY"),

					TEXT("ODFT")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor CashAccountType4Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_CashAccountType4Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor CategoryPurpose1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			CategoryPurpose1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CategoryPurpose1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalCategoryPurpose1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_ChargeBearerType1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("DEBT"),

					TEXT("CRED"),

					TEXT("SHAR"),

					TEXT("SLEV")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor ChargeBearerType1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ChargeBearerType1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor Cheque6 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			11,												// Child element count
			Cheque6ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor Cheque6ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("ChqTp"),				// Tag
					0,										// Min
						1,										// Max
							
					&ChequeType2Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChqNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChqFr"),				// Tag
					0,										// Min
						1,										// Max
							
					&NameAndAddress10								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DlvryMtd"),				// Tag
					0,										// Min
						1,										// Max
							
					&ChequeDeliveryMethod1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DlvrTo"),				// Tag
					0,										// Min
						1,										// Max
							
					&NameAndAddress10								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("InstrPrty"),				// Tag
					0,										// Min
						1,										// Max
							
					&Priority2Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChqMtrtyDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FrmsCd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("MemoFld"),				// Tag
					0,										// Min
						2,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RgnlClrZone"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PrtLctn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_ChequeDelivery1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("MLDB"),

					TEXT("MLCD"),

					TEXT("MLFA"),

					TEXT("CRDB"),

					TEXT("CRCD"),

					TEXT("CRFA"),

					TEXT("PUDB"),

					TEXT("PUCD"),

					TEXT("PUFA"),

					TEXT("RGDB"),

					TEXT("RGCD"),

					TEXT("RGFA")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor ChequeDelivery1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ChequeDelivery1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor ChequeDeliveryMethod1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ChequeDeliveryMethod1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ChequeDeliveryMethod1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ChequeDelivery1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_ChequeType2Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CCHQ"),

					TEXT("CCCH"),

					TEXT("BCHQ"),

					TEXT("DRFT"),

					TEXT("ELDR")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor ChequeType2Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ChequeType2Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor ClearingSystemIdentification2Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ClearingSystemIdentification2ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ClearingSystemIdentification2ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalClearingSystemIdentification1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor ClearingSystemMemberIdentification2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ClearingSystemMemberIdentification2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ClearingSystemMemberIdentification2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("ClrSysId"),				// Tag
					0,										// Min
						1,										// Max
							
					&ClearingSystemIdentification2Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("MmbId"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ContactDetails2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			7,												// Child element count
			ContactDetails2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ContactDetails2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("NmPrfx"),				// Tag
					0,										// Min
						1,										// Max
							
					&NamePrefix1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PhneNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&PhoneNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("MobNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&PhoneNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FaxNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&PhoneNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("EmailAdr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max2048Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Othr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_CountryCode(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[A-Z]{2,2}"), pElement);
					
		}

		static const Separatista::ElementDescriptor CountryCode = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_CountryCode ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_CreditDebitCode(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CRDT"),

					TEXT("DBIT")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor CreditDebitCode = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_CreditDebitCode ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor CreditTransferTransactionInformation10 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			25,												// Child element count
			CreditTransferTransactionInformation10ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CreditTransferTransactionInformation10ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("PmtId"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&PaymentIdentification1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PmtTpInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&PaymentTypeInformation19								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&AmountType3Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("XchgRateInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&ExchangeRateInformation1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChrgBr"),				// Tag
					0,										// Min
						1,										// Max
							
					&ChargeBearerType1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChqInstr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Cheque6								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("UltmtDbtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt1"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt1Acct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt2"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt2Acct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt3"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt3Acct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtrAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtrAgtAcct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Cdtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtrAcct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("UltmtCdtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("InstrForCdtrAgt"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&InstructionForCreditorAgent1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("InstrForDbtrAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Purp"),				// Tag
					0,										// Min
						1,										// Max
							
					&Purpose2Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RgltryRptg"),				// Tag
					0,										// Min
						10,										// Max
							
					&RegulatoryReporting3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Tax"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxInformation3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdRmtInf"),				// Tag
					0,										// Min
						10,										// Max
							
					&RemittanceLocation2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RmtInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&RemittanceInformation5								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CreditorReferenceInformation2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			CreditorReferenceInformation2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CreditorReferenceInformation2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditorReferenceType2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ref"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CreditorReferenceType1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			CreditorReferenceType1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CreditorReferenceType1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&DocumentType3Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor CreditorReferenceType2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			CreditorReferenceType2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CreditorReferenceType2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("CdOrPrtry"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CreditorReferenceType1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CustomerCreditTransferInitiationV03 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			CustomerCreditTransferInitiationV03ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CustomerCreditTransferInitiationV03ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("GrpHdr"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&GroupHeader32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PmtInf"),				// Tag
					1,										// Min
						
							0,																		//Max
							
					&PaymentInstructionInformation3								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor DateAndPlaceOfBirth = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			DateAndPlaceOfBirthChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor DateAndPlaceOfBirthChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("BirthDt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PrvcOfBirth"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CityOfBirth"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtryOfBirth"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CountryCode								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor DatePeriodDetails = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			DatePeriodDetailsChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor DatePeriodDetailsChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("FrDt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ToDt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODate								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_DecimalNumber(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDecimal(pValue, pElement);
			
			Separatista::Validator::validateFractionDigits(pValue, TEXT("17"), pElement);
					
			Separatista::Validator::validateTotalDigits(pValue, TEXT("18"), pElement);
					
		}

		static const Separatista::ElementDescriptor DecimalNumber = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_DecimalNumber ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor Document = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			1,												// Child element count
			DocumentChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor DocumentChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("CstmrCdtTrfInitn"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CustomerCreditTransferInitiationV03								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor DocumentAdjustment1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			DocumentAdjustment1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor DocumentAdjustment1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rsn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max4Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_DocumentType3Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("RADM"),

					TEXT("RPIN"),

					TEXT("FXDR"),

					TEXT("DISP"),

					TEXT("PUOR"),

					TEXT("SCOR")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor DocumentType3Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_DocumentType3Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_DocumentType5Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("MSIN"),

					TEXT("CNFA"),

					TEXT("DNFA"),

					TEXT("CINV"),

					TEXT("CREN"),

					TEXT("DEBN"),

					TEXT("HIRI"),

					TEXT("SBIN"),

					TEXT("CMCN"),

					TEXT("SOAC"),

					TEXT("DISP"),

					TEXT("BOLD"),

					TEXT("VCHR"),

					TEXT("AROI"),

					TEXT("TSUT")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor DocumentType5Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_DocumentType5Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor EquivalentAmount2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			EquivalentAmount2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor EquivalentAmount2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CcyOfTrf"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyCode								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ExchangeRateInformation1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			ExchangeRateInformation1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ExchangeRateInformation1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("XchgRate"),				// Tag
					0,										// Min
						1,										// Max
							
					&BaseOneRate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RateTp"),				// Tag
					0,										// Min
						1,										// Max
							
					&ExchangeRateType1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtrctId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_ExchangeRateType1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("SPOT"),

					TEXT("SALE"),

					TEXT("AGRD")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor ExchangeRateType1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExchangeRateType1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalAccountIdentification1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalAccountIdentification1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalAccountIdentification1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalCategoryPurpose1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalCategoryPurpose1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalCategoryPurpose1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalClearingSystemIdentification1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("5"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalClearingSystemIdentification1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalClearingSystemIdentification1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalFinancialInstitutionIdentification1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalFinancialInstitutionIdentification1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalFinancialInstitutionIdentification1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalLocalInstrument1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("35"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalLocalInstrument1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalLocalInstrument1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalOrganisationIdentification1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalOrganisationIdentification1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalOrganisationIdentification1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalPersonIdentification1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalPersonIdentification1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalPersonIdentification1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalPurpose1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalPurpose1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalPurpose1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalServiceLevel1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalServiceLevel1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalServiceLevel1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor FinancialIdentificationSchemeName1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			FinancialIdentificationSchemeName1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor FinancialIdentificationSchemeName1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalFinancialInstitutionIdentification1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor FinancialInstitutionIdentification7 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			5,												// Child element count
			FinancialInstitutionIdentification7ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor FinancialInstitutionIdentification7ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("BIC"),				// Tag
					0,										// Min
						1,										// Max
							
					&BICIdentifier								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ClrSysMmbId"),				// Tag
					0,										// Min
						1,										// Max
							
					&ClearingSystemMemberIdentification2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PstlAdr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PostalAddress6								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Othr"),				// Tag
					0,										// Min
						1,										// Max
							
					&GenericFinancialIdentification1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor GenericAccountIdentification1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			GenericAccountIdentification1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GenericAccountIdentification1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max34Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SchmeNm"),				// Tag
					0,										// Min
						1,										// Max
							
					&AccountSchemeName1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor GenericFinancialIdentification1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			GenericFinancialIdentification1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GenericFinancialIdentification1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SchmeNm"),				// Tag
					0,										// Min
						1,										// Max
							
					&FinancialIdentificationSchemeName1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor GenericOrganisationIdentification1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			GenericOrganisationIdentification1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GenericOrganisationIdentification1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SchmeNm"),				// Tag
					0,										// Min
						1,										// Max
							
					&OrganisationIdentificationSchemeName1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor GenericPersonIdentification1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			GenericPersonIdentification1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GenericPersonIdentification1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SchmeNm"),				// Tag
					0,										// Min
						1,										// Max
							
					&PersonIdentificationSchemeName1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor GroupHeader32 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			7,												// Child element count
			GroupHeader32ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GroupHeader32ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("MsgId"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CreDtTm"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODateTime								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Authstn"),				// Tag
					0,										// Min
						2,										// Max
							
					&Authorisation1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("NbOfTxs"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max15NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtrlSum"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("InitgPty"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FwdgAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_IBAN2007Identifier(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[A-Z]{2,2}[0-9]{2,2}[a-zA-Z0-9]{1,30}"), pElement);
					
		}

		static const Separatista::ElementDescriptor IBAN2007Identifier = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_IBAN2007Identifier ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ISODate(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDate(pValue, pElement);
			
		}

		static const Separatista::ElementDescriptor ISODate = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ISODate ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ISODateTime(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDateTime(pValue, pElement);
			
		}

		static const Separatista::ElementDescriptor ISODateTime = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ISODateTime ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Instruction3Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CHQB"),

					TEXT("HOLD"),

					TEXT("PHOB"),

					TEXT("TELB")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor Instruction3Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Instruction3Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor InstructionForCreditorAgent1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			InstructionForCreditorAgent1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor InstructionForCreditorAgent1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Instruction3Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("InstrInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor LocalInstrument2Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			LocalInstrument2ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor LocalInstrument2ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalLocalInstrument1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_Max10Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("10"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max10Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max10Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max128Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("128"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max128Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max128Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max140Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("140"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max140Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max140Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max15NumericText(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[0-9]{1,15}"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max15NumericText = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max15NumericText ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max16Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("16"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max16Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max16Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max2048Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("2048"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max2048Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max2048Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max34Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("34"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max34Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max34Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max35Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("35"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max35Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max35Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max4Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max4Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max4Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max70Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("70"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max70Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max70Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor NameAndAddress10 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			NameAndAddress10ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor NameAndAddress10ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Adr"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&PostalAddress6								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_NamePrefix1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("DOCT"),

					TEXT("MIST"),

					TEXT("MISS"),

					TEXT("MADM")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor NamePrefix1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_NamePrefix1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Number(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDecimal(pValue, pElement);
			
			Separatista::Validator::validateFractionDigits(pValue, TEXT("0"), pElement);
					
			Separatista::Validator::validateTotalDigits(pValue, TEXT("18"), pElement);
					
		}

		static const Separatista::ElementDescriptor Number = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Number ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor OrganisationIdentification4 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			OrganisationIdentification4ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor OrganisationIdentification4ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("BICOrBEI"),				// Tag
					0,										// Min
						1,										// Max
							
					&AnyBICIdentifier								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Othr"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&GenericOrganisationIdentification1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor OrganisationIdentificationSchemeName1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			OrganisationIdentificationSchemeName1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor OrganisationIdentificationSchemeName1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalOrganisationIdentification1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor Party6Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			Party6ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor Party6ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("OrgId"),				// Tag
					1,																// Min
					1,																// Max
					&OrganisationIdentification4							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("PrvtId"),				// Tag
					1,																// Min
					1,																// Max
					&PersonIdentification5							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor PartyIdentification32 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			5,												// Child element count
			PartyIdentification32ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PartyIdentification32ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PstlAdr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PostalAddress6								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					0,										// Min
						1,										// Max
							
					&Party6Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtryOfRes"),				// Tag
					0,										// Min
						1,										// Max
							
					&CountryCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtctDtls"),				// Tag
					0,										// Min
						1,										// Max
							
					&ContactDetails2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor PaymentIdentification1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			PaymentIdentification1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PaymentIdentification1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("InstrId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("EndToEndId"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor PaymentInstructionInformation3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			17,												// Child element count
			PaymentInstructionInformation3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PaymentInstructionInformation3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("PmtInfId"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PmtMtd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&PaymentMethod3Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BtchBookg"),				// Tag
					0,										// Min
						1,										// Max
							
					&BatchBookingIndicator								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("NbOfTxs"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max15NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtrlSum"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PmtTpInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&PaymentTypeInformation19								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ReqdExctnDt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PoolgAdjstmntDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dbtr"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DbtrAcct"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DbtrAgt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DbtrAgtAcct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("UltmtDbtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChrgBr"),				// Tag
					0,										// Min
						1,										// Max
							
					&ChargeBearerType1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChrgsAcct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChrgsAcctAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtTrfTxInf"),				// Tag
					1,										// Min
						
							0,																		//Max
							
					&CreditTransferTransactionInformation10								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_PaymentMethod3Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CHK"),

					TEXT("TRF"),

					TEXT("TRA")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor PaymentMethod3Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_PaymentMethod3Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor PaymentTypeInformation19 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			PaymentTypeInformation19ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PaymentTypeInformation19ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("InstrPrty"),				// Tag
					0,										// Min
						1,										// Max
							
					&Priority2Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SvcLvl"),				// Tag
					0,										// Min
						1,										// Max
							
					&ServiceLevel8Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("LclInstrm"),				// Tag
					0,										// Min
						1,										// Max
							
					&LocalInstrument2Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtgyPurp"),				// Tag
					0,										// Min
						1,										// Max
							
					&CategoryPurpose1Choice								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_PercentageRate(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDecimal(pValue, pElement);
			
			Separatista::Validator::validateFractionDigits(pValue, TEXT("10"), pElement);
					
			Separatista::Validator::validateTotalDigits(pValue, TEXT("11"), pElement);
					
		}

		static const Separatista::ElementDescriptor PercentageRate = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_PercentageRate ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor PersonIdentification5 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			PersonIdentification5ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PersonIdentification5ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("DtAndPlcOfBirth"),				// Tag
					0,										// Min
						1,										// Max
							
					&DateAndPlaceOfBirth								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Othr"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&GenericPersonIdentification1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor PersonIdentificationSchemeName1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			PersonIdentificationSchemeName1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PersonIdentificationSchemeName1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalPersonIdentification1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_PhoneNumber(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("\\+[0-9]{1,3}-[0-9()+\\-]{1,30}"), pElement);
					
		}

		static const Separatista::ElementDescriptor PhoneNumber = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_PhoneNumber ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor PostalAddress6 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			10,												// Child element count
			PostalAddress6ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PostalAddress6ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("AdrTp"),				// Tag
					0,										// Min
						1,										// Max
							
					&AddressType2Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dept"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max70Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SubDept"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max70Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("StrtNm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max70Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BldgNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max16Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PstCd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max16Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TwnNm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtrySubDvsn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ctry"),				// Tag
					0,										// Min
						1,										// Max
							
					&CountryCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AdrLine"),				// Tag
					0,										// Min
						7,										// Max
							
					&Max70Text								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_Priority2Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("HIGH"),

					TEXT("NORM")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor Priority2Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Priority2Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor Purpose2Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			Purpose2ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor Purpose2ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalPurpose1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor ReferredDocumentInformation3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			ReferredDocumentInformation3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReferredDocumentInformation3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&ReferredDocumentType2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ReferredDocumentType1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ReferredDocumentType1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReferredDocumentType1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&DocumentType5Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor ReferredDocumentType2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ReferredDocumentType2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReferredDocumentType2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("CdOrPrtry"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ReferredDocumentType1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor RegulatoryAuthority2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			RegulatoryAuthority2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor RegulatoryAuthority2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ctry"),				// Tag
					0,										// Min
						1,										// Max
							
					&CountryCode								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor RegulatoryReporting3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			RegulatoryReporting3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor RegulatoryReporting3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("DbtCdtRptgInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&RegulatoryReportingType1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Authrty"),				// Tag
					0,										// Min
						1,										// Max
							
					&RegulatoryAuthority2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dtls"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&StructuredRegulatoryReporting3								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_RegulatoryReportingType1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CRED"),

					TEXT("DEBT"),

					TEXT("BOTH")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor RegulatoryReportingType1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_RegulatoryReportingType1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor RemittanceAmount1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			RemittanceAmount1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor RemittanceAmount1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("DuePyblAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DscntApldAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtNoteAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TaxAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AdjstmntAmtAndRsn"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&DocumentAdjustment1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RmtdAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor RemittanceInformation5 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			RemittanceInformation5ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor RemittanceInformation5ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Ustrd"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Strd"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&StructuredRemittanceInformation7								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor RemittanceLocation2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			RemittanceLocation2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor RemittanceLocation2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("RmtId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RmtLctnMtd"),				// Tag
					0,										// Min
						1,										// Max
							
					&RemittanceLocationMethod2Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RmtLctnElctrncAdr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max2048Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RmtLctnPstlAdr"),				// Tag
					0,										// Min
						1,										// Max
							
					&NameAndAddress10								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_RemittanceLocationMethod2Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("FAXI"),

					TEXT("EDIC"),

					TEXT("URID"),

					TEXT("EMAL"),

					TEXT("POST"),

					TEXT("SMSM")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor RemittanceLocationMethod2Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_RemittanceLocationMethod2Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor ServiceLevel8Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ServiceLevel8ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ServiceLevel8ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalServiceLevel1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor StructuredRegulatoryReporting3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			StructuredRegulatoryReporting3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor StructuredRegulatoryReporting3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ctry"),				// Tag
					0,										// Min
						1,										// Max
							
					&CountryCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max10Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Inf"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor StructuredRemittanceInformation7 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			StructuredRemittanceInformation7ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor StructuredRemittanceInformation7ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("RfrdDocInf"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ReferredDocumentInformation3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RfrdDocAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&RemittanceAmount1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtrRefInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditorReferenceInformation2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Invcr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Invcee"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlRmtInf"),				// Tag
					0,										// Min
						3,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxAmount1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			TaxAmount1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxAmount1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Rate"),				// Tag
					0,										// Min
						1,										// Max
							
					&PercentageRate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TaxblBaseAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dtls"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&TaxRecordDetails1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxAuthorisation1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			TaxAuthorisation1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxAuthorisation1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Titl"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nm"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxInformation3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			10,												// Child element count
			TaxInformation3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxInformation3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Cdtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxParty1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dbtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxParty2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AdmstnZn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RefNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Mtd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlTaxblBaseAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlTaxAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SeqNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Number								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rcrd"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&TaxRecord1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxParty1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			TaxParty1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxParty1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("TaxId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RegnId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TaxTp"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxParty2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			TaxParty2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxParty2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("TaxId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RegnId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TaxTp"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Authstn"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxAuthorisation1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxPeriod1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			TaxPeriod1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxPeriod1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Yr"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxRecordPeriod1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FrToDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DatePeriodDetails								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxRecord1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			9,												// Child element count
			TaxRecord1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxRecord1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ctgy"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtgyDtls"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DbtrSts"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CertId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FrmsCd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prd"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxPeriod1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TaxAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxAmount1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max140Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TaxRecordDetails1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			TaxRecordDetails1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxRecordDetails1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Prd"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxPeriod1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_TaxRecordPeriod1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("MM01"),

					TEXT("MM02"),

					TEXT("MM03"),

					TEXT("MM04"),

					TEXT("MM05"),

					TEXT("MM06"),

					TEXT("MM07"),

					TEXT("MM08"),

					TEXT("MM09"),

					TEXT("MM10"),

					TEXT("MM11"),

					TEXT("MM12"),

					TEXT("QTR1"),

					TEXT("QTR2"),

					TEXT("QTR3"),

					TEXT("QTR4"),

					TEXT("HLF1"),

					TEXT("HLF2")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor TaxRecordPeriod1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_TaxRecordPeriod1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};


	}
}
