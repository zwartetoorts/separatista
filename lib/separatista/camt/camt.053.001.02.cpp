

#include "separatista/elementdescriptor.h"
#include "separatista/leafelement.h"
#include "separatista/attributedleafelement.h"
#include "separatista/branchelement.h"
#include "separatista/choiceelement.h"
#include "separatista/validator.h"
#include "camt.053.001.02.h"

namespace Separatista
{
	namespace camt_053_001_02 
	{
		const wchar_t* Namespace = TEXT("urn:iso:std:iso:20022:tech:xsd:camt.053.001.02");
		
    
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
		
    
		static const Separatista::ElementDescriptor AccountInterest2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			AccountInterest2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AccountInterest2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&InterestType1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rate"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&Rate3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FrToDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DateTimePeriodDetails								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rsn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor AccountStatement2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			14,												// Child element count
			AccountStatement2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AccountStatement2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ElctrncSeqNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Number								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("LglSeqNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Number								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CreDtTm"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODateTime								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FrToDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DateTimePeriodDetails								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CpyDplctInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&CopyDuplicate1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RptgSrc"),				// Tag
					0,										// Min
						1,										// Max
							
					&ReportingSource1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Acct"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CashAccount20								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdAcct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Intrst"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&AccountInterest2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Bal"),				// Tag
					1,										// Min
						
							0,																		//Max
							
					&CashBalance3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TxsSummry"),				// Tag
					0,										// Min
						1,										// Max
							
					&TotalTransactions2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ntry"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ReportEntry2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlStmtInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max500Text								// ElementDescriptor
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

    
		static const Separatista::ElementDescriptor AlternateSecurityIdentification2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			AlternateSecurityIdentification2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AlternateSecurityIdentification2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor AmountAndCurrencyExchange3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			5,												// Child element count
			AmountAndCurrencyExchange3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AmountAndCurrencyExchange3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("InstdAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&AmountAndCurrencyExchangeDetails3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TxAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&AmountAndCurrencyExchangeDetails3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CntrValAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&AmountAndCurrencyExchangeDetails3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AnncdPstngAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&AmountAndCurrencyExchangeDetails3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PrtryAmt"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&AmountAndCurrencyExchangeDetails4								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor AmountAndCurrencyExchangeDetails3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			AmountAndCurrencyExchangeDetails3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AmountAndCurrencyExchangeDetails3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CcyXchg"),				// Tag
					0,										// Min
						1,										// Max
							
					&CurrencyExchange5								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor AmountAndCurrencyExchangeDetails4 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			AmountAndCurrencyExchangeDetails4ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AmountAndCurrencyExchangeDetails4ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CcyXchg"),				// Tag
					0,										// Min
						1,										// Max
							
					&CurrencyExchange5								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor AmountRangeBoundary1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			AmountRangeBoundary1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor AmountRangeBoundary1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("BdryAmt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ImpliedCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Incl"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&YesNoIndicator								// ElementDescriptor
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

    
		static const Separatista::ElementDescriptor BalanceSubType1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			BalanceSubType1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BalanceSubType1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalBalanceSubType1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor BalanceType12 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			BalanceType12ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BalanceType12ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("CdOrPrtry"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BalanceType5Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SubTp"),				// Tag
					0,										// Min
						1,										// Max
							
					&BalanceSubType1Choice								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_BalanceType12Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("XPCD"),

					TEXT("OPAV"),

					TEXT("ITAV"),

					TEXT("CLAV"),

					TEXT("FWAV"),

					TEXT("CLBD"),

					TEXT("ITBD"),

					TEXT("OPBD"),

					TEXT("PRCD"),

					TEXT("INFO")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor BalanceType12Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_BalanceType12Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor BalanceType5Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			BalanceType5ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BalanceType5ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&BalanceType12Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor BankToCustomerStatementV02 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			BankToCustomerStatementV02ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BankToCustomerStatementV02ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("GrpHdr"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&GroupHeader42								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Stmt"),				// Tag
					1,										// Min
						
							0,																		//Max
							
					&AccountStatement2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor BankTransactionCodeStructure4 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			BankTransactionCodeStructure4ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BankTransactionCodeStructure4ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Domn"),				// Tag
					0,										// Min
						1,										// Max
							
					&BankTransactionCodeStructure5								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					0,										// Min
						1,										// Max
							
					&ProprietaryBankTransactionCodeStructure1								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor BankTransactionCodeStructure5 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			BankTransactionCodeStructure5ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BankTransactionCodeStructure5ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ExternalBankTransactionDomain1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Fmly"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BankTransactionCodeStructure6								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor BankTransactionCodeStructure6 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			BankTransactionCodeStructure6ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BankTransactionCodeStructure6ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ExternalBankTransactionFamily1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SubFmlyCd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ExternalBankTransactionSubFamily1Code								// ElementDescriptor
				},
				

        
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

    
		static const Separatista::ElementDescriptor BatchInformation2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			5,												// Child element count
			BatchInformation2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor BatchInformation2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("MsgId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PmtInfId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("NbOfTxs"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max15NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

        
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
		
    
		static const Separatista::ElementDescriptor CashAccount20 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			CashAccount20ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CashAccount20ChildElements[] =
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
				

            
				{
					SEPARATISTA_TAG("Ownr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Svcr"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
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

    
		static const Separatista::ElementDescriptor CashBalance3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			CashBalance3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CashBalance3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BalanceType12								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtLine"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditLine2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&DateAndDateTimeChoice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Avlbty"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&CashBalanceAvailability2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CashBalanceAvailability2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			CashBalanceAvailability2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CashBalanceAvailability2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Dt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CashBalanceAvailabilityDate1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CashBalanceAvailabilityDate1 = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			CashBalanceAvailabilityDate1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CashBalanceAvailabilityDate1ChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("NbOfDays"),				// Tag
					1,																// Min
					1,																// Max
					&Max15PlusSignedNumericText							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("ActlDt"),				// Tag
					1,																// Min
					1,																// Max
					&ISODate							// ElementDescriptor
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

    
		void validate_ChargeType1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("BRKF"),

					TEXT("COMM")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor ChargeType1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ChargeType1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor ChargeType2Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ChargeType2ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ChargeType2ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ChargeType1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&GenericIdentification3							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor ChargesInformation6 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			8,												// Child element count
			ChargesInformation6ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ChargesInformation6ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("TtlChrgsAndTaxAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
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
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&ChargeType2Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rate"),				// Tag
					0,										// Min
						1,										// Max
							
					&PercentageRate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Br"),				// Tag
					0,										// Min
						1,										// Max
							
					&ChargeBearerType1Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Pty"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Tax"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxCharges2								// ElementDescriptor
				},
				

        
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
		
    
		void validate_CopyDuplicate1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("CODU"),

					TEXT("COPY"),

					TEXT("DUPL")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor CopyDuplicate1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_CopyDuplicate1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor CorporateAction1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			CorporateAction1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CorporateAction1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Nb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
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

    
		static const Separatista::ElementDescriptor CreditLine2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			CreditLine2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CreditLine2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Incl"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&TrueFalseIndicator								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor CurrencyAndAmountRange2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			CurrencyAndAmountRange2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CurrencyAndAmountRange2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ImpliedCurrencyAmountRangeChoice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ccy"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyCode								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor CurrencyExchange5 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			CurrencyExchange5ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor CurrencyExchange5ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("SrcCcy"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TrgtCcy"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("UnitCcy"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("XchgRate"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BaseOneRate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CtrctId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("QtnDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODateTime								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor DateAndDateTimeChoice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			DateAndDateTimeChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor DateAndDateTimeChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Dt"),				// Tag
					1,																// Min
					1,																// Max
					&ISODate							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("DtTm"),				// Tag
					1,																// Min
					1,																// Max
					&ISODateTime							// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor DateTimePeriodDetails = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			DateTimePeriodDetailsChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor DateTimePeriodDetailsChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("FrDtTm"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODateTime								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ToDtTm"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ISODateTime								// ElementDescriptor
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
					SEPARATISTA_TAG("BkToCstmrStmt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BankToCustomerStatementV02								// ElementDescriptor
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

    
		static const Separatista::ElementDescriptor EntryDetails1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			EntryDetails1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor EntryDetails1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Btch"),				// Tag
					0,										// Min
						1,										// Max
							
					&BatchInformation2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TxDtls"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&EntryTransaction2								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_EntryStatus2Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("BOOK"),

					TEXT("PDNG"),

					TEXT("INFO")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor EntryStatus2Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_EntryStatus2Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor EntryTransaction2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			20,												// Child element count
			EntryTransaction2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor EntryTransaction2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Refs"),				// Tag
					0,										// Min
						1,										// Max
							
					&TransactionReferences2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AmtDtls"),				// Tag
					0,										// Min
						1,										// Max
							
					&AmountAndCurrencyExchange3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Avlbty"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&CashBalanceAvailability2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BkTxCd"),				// Tag
					0,										// Min
						1,										// Max
							
					&BankTransactionCodeStructure4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Chrgs"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ChargesInformation6								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Intrst"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&TransactionInterest2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdPties"),				// Tag
					0,										// Min
						1,										// Max
							
					&TransactionParty2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdAgts"),				// Tag
					0,										// Min
						1,										// Max
							
					&TransactionAgents2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Purp"),				// Tag
					0,										// Min
						1,										// Max
							
					&Purpose2Choice								// ElementDescriptor
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
				

            
				{
					SEPARATISTA_TAG("RltdDts"),				// Tag
					0,										// Min
						1,										// Max
							
					&TransactionDates2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdPric"),				// Tag
					0,										// Min
						1,										// Max
							
					&TransactionPrice2Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RltdQties"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&TransactionQuantities1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FinInstrmId"),				// Tag
					0,										// Min
						1,										// Max
							
					&SecurityIdentification4Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Tax"),				// Tag
					0,										// Min
						1,										// Max
							
					&TaxInformation3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RtrInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&ReturnReasonInformation10								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CorpActn"),				// Tag
					0,										// Min
						1,										// Max
							
					&CorporateAction1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SfkpgAcct"),				// Tag
					0,										// Min
						1,										// Max
							
					&CashAccount16								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlTxInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max500Text								// ElementDescriptor
				},
				

        
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

    
		void validate_ExternalBalanceSubType1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalBalanceSubType1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalBalanceSubType1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalBankTransactionDomain1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalBankTransactionDomain1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalBankTransactionDomain1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalBankTransactionFamily1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalBankTransactionFamily1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalBankTransactionFamily1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalBankTransactionSubFamily1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalBankTransactionSubFamily1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalBankTransactionSubFamily1Code ,	// Validator
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

    
		void validate_ExternalReportingSource1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalReportingSource1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalReportingSource1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalReturnReason1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalReturnReason1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalReturnReason1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_ExternalTechnicalInputChannel1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("4"), pElement);
					
		}

		static const Separatista::ElementDescriptor ExternalTechnicalInputChannel1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ExternalTechnicalInputChannel1Code ,	// Validator
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
		
    
		static const Separatista::ElementDescriptor FinancialInstrumentQuantityChoice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			3,												// Child element count
			FinancialInstrumentQuantityChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor FinancialInstrumentQuantityChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Unit"),				// Tag
					1,																// Min
					1,																// Max
					&DecimalNumber							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("FaceAmt"),				// Tag
					1,																// Min
					1,																// Max
					&ImpliedCurrencyAndAmount							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("AmtsdVal"),				// Tag
					1,																// Min
					1,																// Max
					&ImpliedCurrencyAndAmount							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor FromToAmountRange = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			FromToAmountRangeChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor FromToAmountRangeChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("FrAmt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&AmountRangeBoundary1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ToAmt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&AmountRangeBoundary1								// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor GenericIdentification3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			GenericIdentification3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GenericIdentification3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor GroupHeader42 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			5,												// Child element count
			GroupHeader42ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor GroupHeader42ChildElements[] =
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
					SEPARATISTA_TAG("MsgRcpt"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("MsgPgntn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Pagination								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max500Text								// ElementDescriptor
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

    
		void validate_ISINIdentifier(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[A-Z0-9]{12,12}"), pElement);
					
		}

		static const Separatista::ElementDescriptor ISINIdentifier = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ISINIdentifier ,	// Validator
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

    
		static const Separatista::ElementDescriptor ImpliedCurrencyAmountRangeChoice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			5,												// Child element count
			ImpliedCurrencyAmountRangeChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ImpliedCurrencyAmountRangeChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("FrAmt"),				// Tag
					1,																// Min
					1,																// Max
					&AmountRangeBoundary1							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("ToAmt"),				// Tag
					1,																// Min
					1,																// Max
					&AmountRangeBoundary1							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("FrToAmt"),				// Tag
					1,																// Min
					1,																// Max
					&FromToAmountRange							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("EQAmt"),				// Tag
					1,																// Min
					1,																// Max
					&ImpliedCurrencyAndAmount							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("NEQAmt"),				// Tag
					1,																// Min
					1,																// Max
					&ImpliedCurrencyAndAmount							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_ImpliedCurrencyAndAmount(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateDecimal(pValue, pElement);
			
			Separatista::Validator::validateMinInclusive(pValue, TEXT("0"), pElement);
					
			Separatista::Validator::validateFractionDigits(pValue, TEXT("5"), pElement);
					
			Separatista::Validator::validateTotalDigits(pValue, TEXT("18"), pElement);
					
		}

		static const Separatista::ElementDescriptor ImpliedCurrencyAndAmount = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_ImpliedCurrencyAndAmount ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		static const Separatista::ElementDescriptor InterestType1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			InterestType1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor InterestType1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&InterestType1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		void validate_InterestType1Code(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("INDY"),

					TEXT("OVRN")
				},
				pElement);

		}

		static const Separatista::ElementDescriptor InterestType1Code = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_InterestType1Code ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max105Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("105"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max105Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max105Text ,	// Validator
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

    
		void validate_Max15PlusSignedNumericText(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[+]{0,1}[0-9]{1,15}"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max15PlusSignedNumericText = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max15PlusSignedNumericText ,	// Validator
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

    
		void validate_Max500Text(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validateMinLength(pValue, TEXT("1"), pElement);
					
			Separatista::Validator::validateMaxLength(pValue, TEXT("500"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max500Text = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max500Text ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_Max5NumericText(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateString(pValue, pElement);
			
			Separatista::Validator::validatePattern(pValue, TEXT("[0-9]{1,5}"), pElement);
					
		}

		static const Separatista::ElementDescriptor Max5NumericText = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_Max5NumericText ,	// Validator
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

    
		static const Separatista::ElementDescriptor MessageIdentification2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			MessageIdentification2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor MessageIdentification2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("MsgNmId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("MsgId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
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

    
		static const Separatista::ElementDescriptor NumberAndSumOfTransactions1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			NumberAndSumOfTransactions1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor NumberAndSumOfTransactions1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("NbOfNtries"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max15NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Sum"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor NumberAndSumOfTransactions2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			NumberAndSumOfTransactions2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor NumberAndSumOfTransactions2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("NbOfNtries"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max15NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Sum"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlNetNtryAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

        
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
		
    
		static const Separatista::ElementDescriptor Pagination = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			PaginationChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor PaginationChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("PgNb"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max5NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("LastPgInd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&YesNoIndicator								// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor ProprietaryAgent2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryAgent2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryAgent2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Agt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ProprietaryBankTransactionCodeStructure1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryBankTransactionCodeStructure1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryBankTransactionCodeStructure1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Issr"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ProprietaryDate2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryDate2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryDate2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&DateAndDateTimeChoice								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ProprietaryParty2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryParty2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryParty2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Pty"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ProprietaryPrice2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryPrice2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryPrice2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Pric"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ProprietaryQuantity1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryQuantity1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryQuantity1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Qty"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ProprietaryReference1 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			ProprietaryReference1ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ProprietaryReference1ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Ref"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
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
		
    
		static const Separatista::ElementDescriptor Rate3 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			2,												// Child element count
			Rate3ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor Rate3ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&RateType4Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("VldtyRg"),				// Tag
					0,										// Min
						1,										// Max
							
					&CurrencyAndAmountRange2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor RateType4Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			RateType4ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor RateType4ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Pctg"),				// Tag
					1,																// Min
					1,																// Max
					&PercentageRate							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Othr"),				// Tag
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

    
		static const Separatista::ElementDescriptor ReportEntry2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			18,												// Child element count
			ReportEntry2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReportEntry2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("NtryRef"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RvslInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&TrueFalseIndicator								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Sts"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&EntryStatus2Code								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BookgDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DateAndDateTimeChoice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ValDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DateAndDateTimeChoice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AcctSvcrRef"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Avlbty"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&CashBalanceAvailability2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BkTxCd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BankTransactionCodeStructure4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ComssnWvrInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&YesNoIndicator								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlInfInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&MessageIdentification2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AmtDtls"),				// Tag
					0,										// Min
						1,										// Max
							
					&AmountAndCurrencyExchange3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Chrgs"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ChargesInformation6								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TechInptChanl"),				// Tag
					0,										// Min
						1,										// Max
							
					&TechnicalInputChannel1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Intrst"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&TransactionInterest2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("NtryDtls"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&EntryDetails1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlNtryInf"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max500Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor ReportingSource1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ReportingSource1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReportingSource1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalReportingSource1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor ReturnReason5Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			ReturnReason5ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReturnReason5ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalReturnReason1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor ReturnReasonInformation10 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			ReturnReasonInformation10ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor ReturnReasonInformation10ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("OrgnlBkTxCd"),				// Tag
					0,										// Min
						1,										// Max
							
					&BankTransactionCodeStructure4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Orgtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rsn"),				// Tag
					0,										// Min
						1,										// Max
							
					&ReturnReason5Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AddtlInf"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&Max105Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor SecurityIdentification4Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			SecurityIdentification4ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor SecurityIdentification4ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("ISIN"),				// Tag
					1,																// Min
					1,																// Max
					&ISINIdentifier							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&AlternateSecurityIdentification2							// ElementDescriptor
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
		
    
		static const Separatista::ElementDescriptor TaxCharges2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			3,												// Child element count
			TaxCharges2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TaxCharges2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Id"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rate"),				// Tag
					0,										// Min
						1,										// Max
							
					&PercentageRate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
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

    
		static const Separatista::ElementDescriptor TechnicalInputChannel1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			TechnicalInputChannel1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TechnicalInputChannel1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Cd"),				// Tag
					1,																// Min
					1,																// Max
					&ExternalTechnicalInputChannel1Code							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&Max35Text							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor TotalTransactions2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			4,												// Child element count
			TotalTransactions2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TotalTransactions2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("TtlNtries"),				// Tag
					0,										// Min
						1,										// Max
							
					&NumberAndSumOfTransactions2								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlCdtNtries"),				// Tag
					0,										// Min
						1,										// Max
							
					&NumberAndSumOfTransactions1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlDbtNtries"),				// Tag
					0,										// Min
						1,										// Max
							
					&NumberAndSumOfTransactions1								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlNtriesPerBkTxCd"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&TotalsPerBankTransactionCode2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TotalsPerBankTransactionCode2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			7,												// Child element count
			TotalsPerBankTransactionCode2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TotalsPerBankTransactionCode2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("NbOfNtries"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max15NumericText								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Sum"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TtlNetNtryAmt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DecimalNumber								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FcstInd"),				// Tag
					0,										// Min
						1,										// Max
							
					&TrueFalseIndicator								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("BkTxCd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&BankTransactionCodeStructure4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Avlbty"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&CashBalanceAvailability2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TransactionAgents2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			10,												// Child element count
			TransactionAgents2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionAgents2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("DbtrAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtrAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt1"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt2"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrmyAgt3"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("RcvgAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DlvrgAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IssgAgt"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("SttlmPlc"),				// Tag
					0,										// Min
						1,										// Max
							
					&BranchAndFinancialInstitutionIdentification4								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ProprietaryAgent2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TransactionDates2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			8,												// Child element count
			TransactionDates2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionDates2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("AccptncDtTm"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODateTime								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TradActvtyCtrctlSttlmDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TradDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("IntrBkSttlmDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("StartDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("EndDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODate								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TxDtTm"),				// Tag
					0,										// Min
						1,										// Max
							
					&ISODateTime								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ProprietaryDate2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TransactionInterest2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			6,												// Child element count
			TransactionInterest2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionInterest2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("Amt"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&ActiveOrHistoricCurrencyAndAmount								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("CdtDbtInd"),				// Tag
					
							1,																		// Min
						
							1,																		// Max
							
					&CreditDebitCode								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Tp"),				// Tag
					0,										// Min
						1,										// Max
							
					&InterestType1Choice								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rate"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&Rate3								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("FrToDt"),				// Tag
					0,										// Min
						1,										// Max
							
					&DateTimePeriodDetails								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Rsn"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TransactionParty2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			9,												// Child element count
			TransactionParty2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionParty2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("InitgPty"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Dbtr"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("DbtrAcct"),				// Tag
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
					SEPARATISTA_TAG("TradgPty"),				// Tag
					0,										// Min
						1,										// Max
							
					&PartyIdentification32								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					0,										// Min
						
							0,																		//Max
							
					&ProprietaryParty2								// ElementDescriptor
				},
				

        
		};
		
    
		static const Separatista::ElementDescriptor TransactionPrice2Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			TransactionPrice2ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionPrice2ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("DealPric"),				// Tag
					1,																// Min
					1,																// Max
					&ActiveOrHistoricCurrencyAndAmount							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&ProprietaryPrice2							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor TransactionQuantities1Choice = 
		{
			NULL,												// Parent type
			
			Separatista::ChoiceElement::createElement,						// Creator
				
			NULL,												// Validator
			2,												// Child element count
			TransactionQuantities1ChoiceChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionQuantities1ChoiceChildElements[] =
		{
				
            
                
				{
					SEPARATISTA_TAG("Qty"),				// Tag
					1,																// Min
					1,																// Max
					&FinancialInstrumentQuantityChoice							// ElementDescriptor
				},
				

                
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					1,																// Min
					1,																// Max
					&ProprietaryQuantity1							// ElementDescriptor
				},
				

            
        
		};
		
    
		static const Separatista::ElementDescriptor TransactionReferences2 = 
		{
			NULL,												// Parent type
			
			Separatista::BranchElement::createElement,
				
			NULL,												// Validator
			10,												// Child element count
			TransactionReferences2ChildElements											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor TransactionReferences2ChildElements[] =
		{
				
            
				{
					SEPARATISTA_TAG("MsgId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("AcctSvcrRef"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("PmtInfId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("InstrId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("EndToEndId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("TxId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("MndtId"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ChqNb"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("ClrSysRef"),				// Tag
					0,										// Min
						1,										// Max
							
					&Max35Text								// ElementDescriptor
				},
				

            
				{
					SEPARATISTA_TAG("Prtry"),				// Tag
					0,										// Min
						1,										// Max
							
					&ProprietaryReference1								// ElementDescriptor
				},
				

        
		};
		
    
		void validate_TrueFalseIndicator(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateBoolean(pValue, pElement);
			
		}

		static const Separatista::ElementDescriptor TrueFalseIndicator = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_TrueFalseIndicator ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};

    
		void validate_YesNoIndicator(const wchar_t *pValue, Separatista::Element *pElement)
		{
			
			Separatista::Validator::validateBoolean(pValue, pElement);
			
		}

		static const Separatista::ElementDescriptor YesNoIndicator = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			validate_YesNoIndicator ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};


	}
}
