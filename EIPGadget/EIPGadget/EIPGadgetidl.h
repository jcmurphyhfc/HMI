

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri May 20 13:55:05 2016
 */
/* Compiler settings for EIPGadget.idl:
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


#ifndef __EIPGadgetidl_h__
#define __EIPGadgetidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DEIPGadget_FWD_DEFINED__
#define ___DEIPGadget_FWD_DEFINED__
typedef interface _DEIPGadget _DEIPGadget;
#endif 	/* ___DEIPGadget_FWD_DEFINED__ */


#ifndef ___DEIPGadgetEvents_FWD_DEFINED__
#define ___DEIPGadgetEvents_FWD_DEFINED__
typedef interface _DEIPGadgetEvents _DEIPGadgetEvents;
#endif 	/* ___DEIPGadgetEvents_FWD_DEFINED__ */


#ifndef __EIPGadget_FWD_DEFINED__
#define __EIPGadget_FWD_DEFINED__

#ifdef __cplusplus
typedef class EIPGadget EIPGadget;
#else
typedef struct EIPGadget EIPGadget;
#endif /* __cplusplus */

#endif 	/* __EIPGadget_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __EIPGadgetLib_LIBRARY_DEFINED__
#define __EIPGadgetLib_LIBRARY_DEFINED__

/* library EIPGadgetLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_EIPGadgetLib;

#ifndef ___DEIPGadget_DISPINTERFACE_DEFINED__
#define ___DEIPGadget_DISPINTERFACE_DEFINED__

/* dispinterface _DEIPGadget */
/* [uuid] */ 


EXTERN_C const IID DIID__DEIPGadget;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F0C901EA-E990-41C4-8F3C-7BDB18919899")
    _DEIPGadget : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEIPGadgetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEIPGadget * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEIPGadget * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEIPGadget * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEIPGadget * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEIPGadget * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEIPGadget * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEIPGadget * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEIPGadgetVtbl;

    interface _DEIPGadget
    {
        CONST_VTBL struct _DEIPGadgetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEIPGadget_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEIPGadget_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEIPGadget_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEIPGadget_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEIPGadget_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEIPGadget_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEIPGadget_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEIPGadget_DISPINTERFACE_DEFINED__ */


#ifndef ___DEIPGadgetEvents_DISPINTERFACE_DEFINED__
#define ___DEIPGadgetEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DEIPGadgetEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DEIPGadgetEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("20C79ABD-247E-4F57-BF3C-9CB9CBBE6779")
    _DEIPGadgetEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEIPGadgetEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEIPGadgetEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEIPGadgetEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEIPGadgetEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEIPGadgetEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEIPGadgetEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEIPGadgetEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEIPGadgetEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEIPGadgetEventsVtbl;

    interface _DEIPGadgetEvents
    {
        CONST_VTBL struct _DEIPGadgetEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEIPGadgetEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEIPGadgetEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEIPGadgetEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEIPGadgetEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEIPGadgetEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEIPGadgetEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEIPGadgetEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEIPGadgetEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EIPGadget;

#ifdef __cplusplus

class DECLSPEC_UUID("F5260866-E6BB-4A2D-A2D9-336B96C6EF1B")
EIPGadget;
#endif
#endif /* __EIPGadgetLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


