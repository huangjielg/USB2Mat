// USB.h: CUSB 的声明

#pragma once
#include "resource.h"       // 主符号

#include "CMainDialog.h"

#include "USB2Mat_i.h"
#include "_IUSBEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;
extern CMainDialog*GetMainDialog();



class ATL_NO_VTABLE CUSB :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUSB, &CLSID_USB>,
	public IDispatchImpl<IUSB, &IID_IUSB, &LIBID_USB2MatLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IConnectionPointContainerImpl<CUSB>,
	public CProxy_IUSBEvents<CUSB>

{
	CMainDialog *m_pDlg;
	CString m_strOutFormat;
	std::vector<unsigned char> m_vectReadBuffer;
public:

	DECLARE_CLASSFACTORY_SINGLETON(CUSB)
	CUSB()
	{
		m_pDlg = GetMainDialog();
		m_pDlg->SetUSB(this);
	}
	~CUSB() {
		//m_dlg.DestroyWindow();
	}
DECLARE_REGISTRY_RESOURCEID(IDR_USB)


BEGIN_COM_MAP(CUSB)
	COM_INTERFACE_ENTRY(IUSB)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUSB)
	CONNECTION_POINT_ENTRY(__uuidof(_IUSBEvents))
END_CONNECTION_POINT_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}


	
public:

	STDMETHOD(Start)();
	STDMETHOD(Stop)();
	STDMETHOD(Read)(LONG len, SAFEARRAY** pRetVal);
	STDMETHOD(ReadSync)(LONG len, SAFEARRAY** pRetVal);
	STDMETHOD(get_saveFileName)(BSTR* pVal);
	STDMETHOD(put_saveFileName)(BSTR newVal);
	STDMETHOD(get_Avial)(LONG* pVal);


	STDMETHOD(get_readyThreshold)(
		/* [retval][out] */ LONG* pVal);

	STDMETHOD(put_readyThreshold)(
		/* [in] */ LONG newVal);
	STDMETHOD(ReadDirect)(LONG len, SAFEARRAY** pRetVal);
	STDMETHOD(WriteDirect)(SAFEARRAY* pVal);

	STDMETHOD(WriteReg)(
		/* [in] */ USHORT addr,
		/* [in] */ USHORT Val);

	STDMETHOD(ReadReg)(
		/* [in] */ USHORT addr,
		/* [retval][out] */ USHORT* pVal);



	STDMETHOD(get_doInit)(
		/* [retval][out] */ LONG* pVal);

	STDMETHOD(put_doInit)(
			/* [in] */ LONG newVal);

	STDMETHOD(get_outFormat)(BSTR* pVal);
	STDMETHOD(put_outFormat)(BSTR newVal);

	STDMETHOD(ReadDouble)(LONG len, SAFEARRAY** pRetVal);
	STDMETHOD(ReadDoubleSync)(LONG len, SAFEARRAY** pRetVal);
	//STDMETHOD(ReadV)(	/* [in] */ LONG len,	/* [retval][out] */ VARIANT* pRetVal);


	STDMETHOD(get_cmdOutEnable)(
		/* [retval][out] */ LONG* pVal);

	STDMETHOD(put_cmdOutEnable)(
		/* [in] */ LONG newVal);

};

OBJECT_ENTRY_AUTO(__uuidof(USB), CUSB)
