

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 21:14:07 2038
 */
/* Compiler settings for GDIButtonXL.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __GDIButtonXLidl_h__
#define __GDIButtonXLidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef ___DGDIButtonXL_FWD_DEFINED__
#define ___DGDIButtonXL_FWD_DEFINED__
typedef interface _DGDIButtonXL _DGDIButtonXL;

#endif 	/* ___DGDIButtonXL_FWD_DEFINED__ */


#ifndef ___DGDIButtonXLEvents_FWD_DEFINED__
#define ___DGDIButtonXLEvents_FWD_DEFINED__
typedef interface _DGDIButtonXLEvents _DGDIButtonXLEvents;

#endif 	/* ___DGDIButtonXLEvents_FWD_DEFINED__ */


#ifndef __GDIButtonXL_FWD_DEFINED__
#define __GDIButtonXL_FWD_DEFINED__

#ifdef __cplusplus
typedef class GDIButtonXL GDIButtonXL;
#else
typedef struct GDIButtonXL GDIButtonXL;
#endif /* __cplusplus */

#endif 	/* __GDIButtonXL_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_GDIButtonXL_0000_0000 */
/* [local] */ 

#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
#pragma warning(pop)
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_GDIButtonXL_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GDIButtonXL_0000_0000_v0_0_s_ifspec;


#ifndef __GDIButtonXLLib_LIBRARY_DEFINED__
#define __GDIButtonXLLib_LIBRARY_DEFINED__

/* library GDIButtonXLLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_GDIButtonXLLib;

#ifndef ___DGDIButtonXL_DISPINTERFACE_DEFINED__
#define ___DGDIButtonXL_DISPINTERFACE_DEFINED__

/* dispinterface _DGDIButtonXL */
/* [uuid] */ 


EXTERN_C const IID DIID__DGDIButtonXL;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B28DFE52-8499-4AD4-AE4C-DF4FC292ABB8")
    _DGDIButtonXL : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGDIButtonXLVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGDIButtonXL * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGDIButtonXL * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGDIButtonXL * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGDIButtonXL * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGDIButtonXL * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGDIButtonXL * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGDIButtonXL * This,
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
    } _DGDIButtonXLVtbl;

    interface _DGDIButtonXL
    {
        CONST_VTBL struct _DGDIButtonXLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGDIButtonXL_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGDIButtonXL_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGDIButtonXL_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGDIButtonXL_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGDIButtonXL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGDIButtonXL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGDIButtonXL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGDIButtonXL_DISPINTERFACE_DEFINED__ */


#ifndef ___DGDIButtonXLEvents_DISPINTERFACE_DEFINED__
#define ___DGDIButtonXLEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DGDIButtonXLEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DGDIButtonXLEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("408FF230-3234-46D8-AEC6-288CB7B74337")
    _DGDIButtonXLEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGDIButtonXLEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGDIButtonXLEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGDIButtonXLEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGDIButtonXLEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGDIButtonXLEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGDIButtonXLEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGDIButtonXLEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGDIButtonXLEvents * This,
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
    } _DGDIButtonXLEventsVtbl;

    interface _DGDIButtonXLEvents
    {
        CONST_VTBL struct _DGDIButtonXLEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGDIButtonXLEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGDIButtonXLEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGDIButtonXLEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGDIButtonXLEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGDIButtonXLEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGDIButtonXLEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGDIButtonXLEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGDIButtonXLEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GDIButtonXL;

#ifdef __cplusplus

class DECLSPEC_UUID("7F078F87-2F90-4A93-A093-A519F6C545DC")
GDIButtonXL;
#endif
#endif /* __GDIButtonXLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


