

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 21:14:07 2038
 */
/* Compiler settings for GDIMotorStatus.idl:
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


#ifndef __GDIMotorStatusidl_h__
#define __GDIMotorStatusidl_h__

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

#ifndef ___DGDIMotorStatus_FWD_DEFINED__
#define ___DGDIMotorStatus_FWD_DEFINED__
typedef interface _DGDIMotorStatus _DGDIMotorStatus;

#endif 	/* ___DGDIMotorStatus_FWD_DEFINED__ */


#ifndef ___DGDIMotorStatusEvents_FWD_DEFINED__
#define ___DGDIMotorStatusEvents_FWD_DEFINED__
typedef interface _DGDIMotorStatusEvents _DGDIMotorStatusEvents;

#endif 	/* ___DGDIMotorStatusEvents_FWD_DEFINED__ */


#ifndef __GDIMotorStatus_FWD_DEFINED__
#define __GDIMotorStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class GDIMotorStatus GDIMotorStatus;
#else
typedef struct GDIMotorStatus GDIMotorStatus;
#endif /* __cplusplus */

#endif 	/* __GDIMotorStatus_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_GDIMotorStatus_0000_0000 */
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


extern RPC_IF_HANDLE __MIDL_itf_GDIMotorStatus_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GDIMotorStatus_0000_0000_v0_0_s_ifspec;


#ifndef __GDIMotorStatusLib_LIBRARY_DEFINED__
#define __GDIMotorStatusLib_LIBRARY_DEFINED__

/* library GDIMotorStatusLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_GDIMotorStatusLib;

#ifndef ___DGDIMotorStatus_DISPINTERFACE_DEFINED__
#define ___DGDIMotorStatus_DISPINTERFACE_DEFINED__

/* dispinterface _DGDIMotorStatus */
/* [uuid] */ 


EXTERN_C const IID DIID__DGDIMotorStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7A6E2211-0E84-4774-B8DF-2CDE779C7EC7")
    _DGDIMotorStatus : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGDIMotorStatusVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGDIMotorStatus * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGDIMotorStatus * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGDIMotorStatus * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGDIMotorStatus * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGDIMotorStatus * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGDIMotorStatus * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGDIMotorStatus * This,
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
    } _DGDIMotorStatusVtbl;

    interface _DGDIMotorStatus
    {
        CONST_VTBL struct _DGDIMotorStatusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGDIMotorStatus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGDIMotorStatus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGDIMotorStatus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGDIMotorStatus_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGDIMotorStatus_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGDIMotorStatus_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGDIMotorStatus_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGDIMotorStatus_DISPINTERFACE_DEFINED__ */


#ifndef ___DGDIMotorStatusEvents_DISPINTERFACE_DEFINED__
#define ___DGDIMotorStatusEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DGDIMotorStatusEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DGDIMotorStatusEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BAFD3B1F-3D5B-450B-9AF9-53FC76CD7D5B")
    _DGDIMotorStatusEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGDIMotorStatusEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGDIMotorStatusEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGDIMotorStatusEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGDIMotorStatusEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGDIMotorStatusEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGDIMotorStatusEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGDIMotorStatusEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGDIMotorStatusEvents * This,
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
    } _DGDIMotorStatusEventsVtbl;

    interface _DGDIMotorStatusEvents
    {
        CONST_VTBL struct _DGDIMotorStatusEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGDIMotorStatusEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGDIMotorStatusEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGDIMotorStatusEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGDIMotorStatusEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGDIMotorStatusEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGDIMotorStatusEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGDIMotorStatusEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGDIMotorStatusEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GDIMotorStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("FA59A8CA-FAC8-4A3A-9CCF-1CC219C84072")
GDIMotorStatus;
#endif
#endif /* __GDIMotorStatusLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


