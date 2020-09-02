// USB2Mat.cpp: WinMain 的实现


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "USB2Mat_i.h"
#include "USB.h"
#include "CMainDialog.h"
using namespace ATL;


class CUSB2MatModule : public ATL::CAtlExeModuleT< CUSB2MatModule >
{
	
public :
	CMainDialog dlg;
	DECLARE_LIBID(LIBID_USB2MatLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_USB2MAT, "{e8d74eae-27df-4feb-a0ff-604455bda9af}")
	HRESULT Run(_In_ int nShowCmd = SW_HIDE) throw()
	{
		dlg.Create(NULL);
		dlg.ShowWindow(SW_SHOW);
		HRESULT hr=ATL::CAtlExeModuleT< CUSB2MatModule >::Run(nShowCmd);
		dlg.DestroyWindow();
		return hr;
	}
	void RunMessageLoop() throw()
	{
		MSG msg;
		while (GetMessage(&msg, 0, 0, 0) > 0)
		{
			if (msg.message == WM_MY_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
};

CUSB2MatModule _AtlModule;

 CMainDialog* GetMainDialog()
{
	return & _AtlModule.dlg;
}

//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}


