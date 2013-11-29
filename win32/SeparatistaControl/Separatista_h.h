

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Nov 29 20:56:38 2013
 */
/* Compiler settings for Separatista.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Separatista_h_h__
#define __Separatista_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIBAN_FWD_DEFINED__
#define __IIBAN_FWD_DEFINED__
typedef interface IIBAN IIBAN;

#endif 	/* __IIBAN_FWD_DEFINED__ */


#ifndef __IBAN_FWD_DEFINED__
#define __IBAN_FWD_DEFINED__

#ifdef __cplusplus
typedef class IBAN IBAN;
#else
typedef struct IBAN IBAN;
#endif /* __cplusplus */

#endif 	/* __IBAN_FWD_DEFINED__ */


#ifndef __IMT940SRecordset_FWD_DEFINED__
#define __IMT940SRecordset_FWD_DEFINED__
typedef interface IMT940SRecordset IMT940SRecordset;

#endif 	/* __IMT940SRecordset_FWD_DEFINED__ */


#ifndef __MT940SRecordset_FWD_DEFINED__
#define __MT940SRecordset_FWD_DEFINED__

#ifdef __cplusplus
typedef class MT940SRecordset MT940SRecordset;
#else
typedef struct MT940SRecordset MT940SRecordset;
#endif /* __cplusplus */

#endif 	/* __MT940SRecordset_FWD_DEFINED__ */


#ifndef __IMT940SDocument_FWD_DEFINED__
#define __IMT940SDocument_FWD_DEFINED__
typedef interface IMT940SDocument IMT940SDocument;

#endif 	/* __IMT940SDocument_FWD_DEFINED__ */


#ifndef __MT940SDocument_FWD_DEFINED__
#define __MT940SDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class MT940SDocument MT940SDocument;
#else
typedef struct MT940SDocument MT940SDocument;
#endif /* __cplusplus */

#endif 	/* __MT940SDocument_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Separatista_LIBRARY_DEFINED__
#define __Separatista_LIBRARY_DEFINED__

/* library Separatista */
/* [version][lcid][helpstring][uuid] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_Separatista_0001_0003_0001
    {
        OK	= 0,
        E_FILE	= ( OK + 1 ) ,
        E_FORMAT	= ( E_FILE + 1 ) 
    } 	MT940SOpenStatus;


EXTERN_C const IID LIBID_Separatista;

#ifndef __IIBAN_INTERFACE_DEFINED__
#define __IIBAN_INTERFACE_DEFINED__

/* interface IIBAN */
/* [object][dual][oleautomation][helpstring][uuid] */ 


EXTERN_C const IID IID_IIBAN;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3CDADD67-109C-49b4-9B1B-5C10B7121EB6")
    IIBAN : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IIBANVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIBAN * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIBAN * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIBAN * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIBAN * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIBAN * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIBAN * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIBAN * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IIBANVtbl;

    interface IIBAN
    {
        CONST_VTBL struct IIBANVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIBAN_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIBAN_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIBAN_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIBAN_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIBAN_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIBAN_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIBAN_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIBAN_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_IBAN;

#ifdef __cplusplus

class DECLSPEC_UUID("2BD7342E-B12D-45b0-A5D6-ADF118386112")
IBAN;
#endif

#ifndef __IMT940SRecordset_INTERFACE_DEFINED__
#define __IMT940SRecordset_INTERFACE_DEFINED__

/* interface IMT940SRecordset */
/* [object][dual][oleautomation][helpstring][uuid] */ 


EXTERN_C const IID IID_IMT940SRecordset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B61526D3-1B0E-42c0-A276-C0F1DAA94CC8")
    IMT940SRecordset : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_CurrencyClient( 
            /* [retval][out] */ BSTR *pCurrencyClient) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_TransactionReference( 
            /* [retval][out] */ BSTR *pTransactionReference) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_SerialNumber( 
            /* [retval][out] */ BSTR *pSerialNumber) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_IBANClient( 
            /* [retval][out] */ IIBAN **ppIBANClient) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_PreviousBalance( 
            /* [retval][out] */ VARIANT *pPreviousBalance) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_PreviousBalanceDate( 
            /* [retval][out] */ DATE *pPreviousBalanceDate) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_CurrentBalance( 
            /* [retval][out] */ VARIANT *pCurrentBalance) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_CurrentBalanceDate( 
            /* [retval][out] */ DATE *pCurrentBalanceDate) = 0;
        
        virtual /* [helpstring] */ HRESULT __stdcall MoveFirst( void) = 0;
        
        virtual /* [helpstring] */ HRESULT __stdcall MoveNext( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_EOF( 
            /* [retval][out] */ BOOL *pEOF) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_TransactionDate( 
            /* [retval][out] */ DATE *pTransactionDate) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMT940SRecordsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMT940SRecordset * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMT940SRecordset * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMT940SRecordset * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMT940SRecordset * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMT940SRecordset * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMT940SRecordset * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMT940SRecordset * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_CurrencyClient )( 
            IMT940SRecordset * This,
            /* [retval][out] */ BSTR *pCurrencyClient);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_TransactionReference )( 
            IMT940SRecordset * This,
            /* [retval][out] */ BSTR *pTransactionReference);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_SerialNumber )( 
            IMT940SRecordset * This,
            /* [retval][out] */ BSTR *pSerialNumber);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_IBANClient )( 
            IMT940SRecordset * This,
            /* [retval][out] */ IIBAN **ppIBANClient);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_PreviousBalance )( 
            IMT940SRecordset * This,
            /* [retval][out] */ VARIANT *pPreviousBalance);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_PreviousBalanceDate )( 
            IMT940SRecordset * This,
            /* [retval][out] */ DATE *pPreviousBalanceDate);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_CurrentBalance )( 
            IMT940SRecordset * This,
            /* [retval][out] */ VARIANT *pCurrentBalance);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_CurrentBalanceDate )( 
            IMT940SRecordset * This,
            /* [retval][out] */ DATE *pCurrentBalanceDate);
        
        /* [helpstring] */ HRESULT ( __stdcall *MoveFirst )( 
            IMT940SRecordset * This);
        
        /* [helpstring] */ HRESULT ( __stdcall *MoveNext )( 
            IMT940SRecordset * This);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_EOF )( 
            IMT940SRecordset * This,
            /* [retval][out] */ BOOL *pEOF);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_TransactionDate )( 
            IMT940SRecordset * This,
            /* [retval][out] */ DATE *pTransactionDate);
        
        END_INTERFACE
    } IMT940SRecordsetVtbl;

    interface IMT940SRecordset
    {
        CONST_VTBL struct IMT940SRecordsetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMT940SRecordset_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMT940SRecordset_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMT940SRecordset_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMT940SRecordset_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMT940SRecordset_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMT940SRecordset_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMT940SRecordset_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMT940SRecordset_get_CurrencyClient(This,pCurrencyClient)	\
    ( (This)->lpVtbl -> get_CurrencyClient(This,pCurrencyClient) ) 

#define IMT940SRecordset_get_TransactionReference(This,pTransactionReference)	\
    ( (This)->lpVtbl -> get_TransactionReference(This,pTransactionReference) ) 

#define IMT940SRecordset_get_SerialNumber(This,pSerialNumber)	\
    ( (This)->lpVtbl -> get_SerialNumber(This,pSerialNumber) ) 

#define IMT940SRecordset_get_IBANClient(This,ppIBANClient)	\
    ( (This)->lpVtbl -> get_IBANClient(This,ppIBANClient) ) 

#define IMT940SRecordset_get_PreviousBalance(This,pPreviousBalance)	\
    ( (This)->lpVtbl -> get_PreviousBalance(This,pPreviousBalance) ) 

#define IMT940SRecordset_get_PreviousBalanceDate(This,pPreviousBalanceDate)	\
    ( (This)->lpVtbl -> get_PreviousBalanceDate(This,pPreviousBalanceDate) ) 

#define IMT940SRecordset_get_CurrentBalance(This,pCurrentBalance)	\
    ( (This)->lpVtbl -> get_CurrentBalance(This,pCurrentBalance) ) 

#define IMT940SRecordset_get_CurrentBalanceDate(This,pCurrentBalanceDate)	\
    ( (This)->lpVtbl -> get_CurrentBalanceDate(This,pCurrentBalanceDate) ) 

#define IMT940SRecordset_MoveFirst(This)	\
    ( (This)->lpVtbl -> MoveFirst(This) ) 

#define IMT940SRecordset_MoveNext(This)	\
    ( (This)->lpVtbl -> MoveNext(This) ) 

#define IMT940SRecordset_get_EOF(This,pEOF)	\
    ( (This)->lpVtbl -> get_EOF(This,pEOF) ) 

#define IMT940SRecordset_get_TransactionDate(This,pTransactionDate)	\
    ( (This)->lpVtbl -> get_TransactionDate(This,pTransactionDate) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMT940SRecordset_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MT940SRecordset;

#ifdef __cplusplus

class DECLSPEC_UUID("343F637E-DA0B-43a4-A802-8F9EF2DCC5DF")
MT940SRecordset;
#endif

#ifndef __IMT940SDocument_INTERFACE_DEFINED__
#define __IMT940SDocument_INTERFACE_DEFINED__

/* interface IMT940SDocument */
/* [object][dual][oleautomation][helpstring][uuid] */ 


EXTERN_C const IID IID_IMT940SDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("051E4622-F5B0-40c4-81BC-F12EB35F1868")
    IMT940SDocument : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT __stdcall Open( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ MT940SOpenStatus *pStatus) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT __stdcall get_RecordsetCount( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT __stdcall get_Item( 
            /* [in] */ VARIANT vIndex,
            /* [retval][out] */ IMT940SRecordset **ppIMT940SRecordset) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT __stdcall get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMT940SDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMT940SDocument * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMT940SDocument * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMT940SDocument * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMT940SDocument * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMT940SDocument * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMT940SDocument * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMT940SDocument * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring] */ HRESULT ( __stdcall *Open )( 
            IMT940SDocument * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ MT940SOpenStatus *pStatus);
        
        /* [helpstring][propget] */ HRESULT ( __stdcall *get_RecordsetCount )( 
            IMT940SDocument * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpstring][id][propget] */ HRESULT ( __stdcall *get_Item )( 
            IMT940SDocument * This,
            /* [in] */ VARIANT vIndex,
            /* [retval][out] */ IMT940SRecordset **ppIMT940SRecordset);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( __stdcall *get__NewEnum )( 
            IMT940SDocument * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        END_INTERFACE
    } IMT940SDocumentVtbl;

    interface IMT940SDocument
    {
        CONST_VTBL struct IMT940SDocumentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMT940SDocument_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMT940SDocument_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMT940SDocument_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMT940SDocument_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMT940SDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMT940SDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMT940SDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMT940SDocument_Open(This,Path,pStatus)	\
    ( (This)->lpVtbl -> Open(This,Path,pStatus) ) 

#define IMT940SDocument_get_RecordsetCount(This,plCount)	\
    ( (This)->lpVtbl -> get_RecordsetCount(This,plCount) ) 

#define IMT940SDocument_get_Item(This,vIndex,ppIMT940SRecordset)	\
    ( (This)->lpVtbl -> get_Item(This,vIndex,ppIMT940SRecordset) ) 

#define IMT940SDocument_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMT940SDocument_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MT940SDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("6DF05A76-0582-415a-9B96-163F76914250")
MT940SDocument;
#endif
#endif /* __Separatista_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


