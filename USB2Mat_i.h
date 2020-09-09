

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for USB2Mat.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __USB2Mat_i_h__
#define __USB2Mat_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IUSB_FWD_DEFINED__
#define __IUSB_FWD_DEFINED__
typedef interface IUSB IUSB;

#endif 	/* __IUSB_FWD_DEFINED__ */


#ifndef ___IUSBEvents_FWD_DEFINED__
#define ___IUSBEvents_FWD_DEFINED__
typedef interface _IUSBEvents _IUSBEvents;

#endif 	/* ___IUSBEvents_FWD_DEFINED__ */


#ifndef __USB_FWD_DEFINED__
#define __USB_FWD_DEFINED__

#ifdef __cplusplus
typedef class USB USB;
#else
typedef struct USB USB;
#endif /* __cplusplus */

#endif 	/* __USB_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IUSB_INTERFACE_DEFINED__
#define __IUSB_INTERFACE_DEFINED__

/* interface IUSB */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IUSB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0e75bdde-9867-48aa-915a-c57277a22e42")
    IUSB : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadSync( 
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_saveFileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_saveFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Avial( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_readyThreshold( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_readyThreshold( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadDirect( 
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WriteDirect( 
            SAFEARRAY * Val) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WriteReg( 
            /* [in] */ USHORT addr,
            /* [in] */ USHORT Val) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadReg( 
            /* [in] */ USHORT addr,
            /* [retval][out] */ USHORT *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_doInit( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_doInit( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_outFormat( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_outFormat( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadDouble( 
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadDoubleSync( 
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_cmdOutEnable( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_cmdOutEnable( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUSBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUSB * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUSB * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUSB * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUSB * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUSB * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUSB * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUSB * This,
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
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IUSB * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IUSB * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IUSB * This,
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadSync )( 
            IUSB * This,
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_saveFileName )( 
            IUSB * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_saveFileName )( 
            IUSB * This,
            /* [in] */ BSTR newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Avial )( 
            IUSB * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_readyThreshold )( 
            IUSB * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_readyThreshold )( 
            IUSB * This,
            /* [in] */ LONG newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadDirect )( 
            IUSB * This,
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WriteDirect )( 
            IUSB * This,
            SAFEARRAY * Val);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WriteReg )( 
            IUSB * This,
            /* [in] */ USHORT addr,
            /* [in] */ USHORT Val);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadReg )( 
            IUSB * This,
            /* [in] */ USHORT addr,
            /* [retval][out] */ USHORT *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_doInit )( 
            IUSB * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_doInit )( 
            IUSB * This,
            /* [in] */ LONG newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_outFormat )( 
            IUSB * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_outFormat )( 
            IUSB * This,
            /* [in] */ BSTR newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadDouble )( 
            IUSB * This,
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadDoubleSync )( 
            IUSB * This,
            /* [in] */ LONG len,
            /* [retval][out] */ SAFEARRAY * *pRetVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_cmdOutEnable )( 
            IUSB * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_cmdOutEnable )( 
            IUSB * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IUSBVtbl;

    interface IUSB
    {
        CONST_VTBL struct IUSBVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUSB_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUSB_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUSB_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUSB_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUSB_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUSB_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUSB_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IUSB_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define IUSB_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define IUSB_Read(This,len,pRetVal)	\
    ( (This)->lpVtbl -> Read(This,len,pRetVal) ) 

#define IUSB_ReadSync(This,len,pRetVal)	\
    ( (This)->lpVtbl -> ReadSync(This,len,pRetVal) ) 

#define IUSB_get_saveFileName(This,pVal)	\
    ( (This)->lpVtbl -> get_saveFileName(This,pVal) ) 

#define IUSB_put_saveFileName(This,newVal)	\
    ( (This)->lpVtbl -> put_saveFileName(This,newVal) ) 

#define IUSB_get_Avial(This,pVal)	\
    ( (This)->lpVtbl -> get_Avial(This,pVal) ) 

#define IUSB_get_readyThreshold(This,pVal)	\
    ( (This)->lpVtbl -> get_readyThreshold(This,pVal) ) 

#define IUSB_put_readyThreshold(This,newVal)	\
    ( (This)->lpVtbl -> put_readyThreshold(This,newVal) ) 

#define IUSB_ReadDirect(This,len,pRetVal)	\
    ( (This)->lpVtbl -> ReadDirect(This,len,pRetVal) ) 

#define IUSB_WriteDirect(This,Val)	\
    ( (This)->lpVtbl -> WriteDirect(This,Val) ) 

#define IUSB_WriteReg(This,addr,Val)	\
    ( (This)->lpVtbl -> WriteReg(This,addr,Val) ) 

#define IUSB_ReadReg(This,addr,pVal)	\
    ( (This)->lpVtbl -> ReadReg(This,addr,pVal) ) 

#define IUSB_get_doInit(This,pVal)	\
    ( (This)->lpVtbl -> get_doInit(This,pVal) ) 

#define IUSB_put_doInit(This,newVal)	\
    ( (This)->lpVtbl -> put_doInit(This,newVal) ) 

#define IUSB_get_outFormat(This,pVal)	\
    ( (This)->lpVtbl -> get_outFormat(This,pVal) ) 

#define IUSB_put_outFormat(This,newVal)	\
    ( (This)->lpVtbl -> put_outFormat(This,newVal) ) 

#define IUSB_ReadDouble(This,len,pRetVal)	\
    ( (This)->lpVtbl -> ReadDouble(This,len,pRetVal) ) 

#define IUSB_ReadDoubleSync(This,len,pRetVal)	\
    ( (This)->lpVtbl -> ReadDoubleSync(This,len,pRetVal) ) 

#define IUSB_get_cmdOutEnable(This,pVal)	\
    ( (This)->lpVtbl -> get_cmdOutEnable(This,pVal) ) 

#define IUSB_put_cmdOutEnable(This,newVal)	\
    ( (This)->lpVtbl -> put_cmdOutEnable(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUSB_INTERFACE_DEFINED__ */



#ifndef __USB2MatLib_LIBRARY_DEFINED__
#define __USB2MatLib_LIBRARY_DEFINED__

/* library USB2MatLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_USB2MatLib;

#ifndef ___IUSBEvents_DISPINTERFACE_DEFINED__
#define ___IUSBEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUSBEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IUSBEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0e75bdde-9867-48aa-915a-c57277a22e43")
    _IUSBEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUSBEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IUSBEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IUSBEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IUSBEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IUSBEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IUSBEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IUSBEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IUSBEvents * This,
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
    } _IUSBEventsVtbl;

    interface _IUSBEvents
    {
        CONST_VTBL struct _IUSBEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUSBEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IUSBEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IUSBEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IUSBEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IUSBEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IUSBEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IUSBEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUSBEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_USB;

#ifdef __cplusplus

class DECLSPEC_UUID("b0a07713-3940-4dee-940a-d8d2ac284272")
USB;
#endif
#endif /* __USB2MatLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


