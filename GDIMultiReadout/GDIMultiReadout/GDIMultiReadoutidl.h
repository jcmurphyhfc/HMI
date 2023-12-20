

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jan 17 09:21:03 2019
 */
/* Compiler settings for GDIMultiReadout.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
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


#ifndef __GDIMultiReadoutidl_h__
#define __GDIMultiReadoutidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DGDIMultiReadout_FWD_DEFINED__
#define ___DGDIMultiReadout_FWD_DEFINED__
typedef interface _DGDIMultiReadout _DGDIMultiReadout;
#endif 	/* ___DGDIMultiReadout_FWD_DEFINED__ */


#ifndef ___DGDIMultiReadoutEvents_FWD_DEFINED__
#define ___DGDIMultiReadoutEvents_FWD_DEFINED__
typedef interface _DGDIMultiReadoutEvents _DGDIMultiReadoutEvents;
#endif 	/* ___DGDIMultiReadoutEvents_FWD_DEFINED__ */


#ifndef __GDIMultiReadout_FWD_DEFINED__
#define __GDIMultiReadout_FWD_DEFINED__

#ifdef __cplusplus
typedef class GDIMultiReadout GDIMultiReadout;
#else
typedef struct GDIMultiReadout GDIMultiReadout;
#endif /* __cplusplus */

#endif 	/* __GDIMultiReadout_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __GDIMultiReadoutLib_LIBRARY_DEFINED__
#define __GDIMultiReadoutLib_LIBRARY_DEFINED__

/* library GDIMultiReadoutLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_GDIMultiReadoutLib;

#ifndef ___DGDIMultiReadout_DISPINTERFACE_DEFINED__
#define ___DGDIMultiReadout_DISPINTERFACE_DEFINED__

/* dispinterface _DGDIMultiReadout */
/* [uuid] */ 


EXTERN_C const IID DIID__DGDIMultiReadout;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BB7CA3F9-2539-4504-B491-7A6048C90645")
    _DGDIMultiReadout : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGDIMultiReadoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGDIMultiReadout * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGDIMultiReadout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGDIMultiReadout * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGDIMultiReadout * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGDIMultiReadout * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGDIMultiReadout * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGDIMultiReadout * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DGDIMultiReadoutVtbl;

    interface _DGDIMultiReadout
    {
        CONST_VTBL struct _DGDIMultiReadoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGDIMultiReadout_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGDIMultiReadout_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGDIMultiReadout_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGDIMultiReadout_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGDIMultiReadout_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGDIMultiReadout_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGDIMultiReadout_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGDIMultiReadout_DISPINTERFACE_DEFINED__ */


#ifndef ___DGDIMultiReadoutEvents_DISPINTERFACE_DEFINED__
#define ___DGDIMultiReadoutEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DGDIMultiReadoutEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DGDIMultiReadoutEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("27E66378-B0F9-43D7-B22F-F0BA8366D753")
    _DGDIMultiReadoutEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGDIMultiReadoutEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGDIMultiReadoutEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGDIMultiReadoutEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGDIMultiReadoutEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGDIMultiReadoutEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGDIMultiReadoutEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGDIMultiReadoutEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGDIMultiReadoutEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DGDIMultiReadoutEventsVtbl;

    interface _DGDIMultiReadoutEvents
    {
        CONST_VTBL struct _DGDIMultiReadoutEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGDIMultiReadoutEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGDIMultiReadoutEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGDIMultiReadoutEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGDIMultiReadoutEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGDIMultiReadoutEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGDIMultiReadoutEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGDIMultiReadoutEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGDIMultiReadoutEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GDIMultiReadout;

#ifdef __cplusplus

class DECLSPEC_UUID("9F01B6E1-2CA6-470B-8270-F13E8CECE68F")
GDIMultiReadout;
#endif
#endif /* __GDIMultiReadoutLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


