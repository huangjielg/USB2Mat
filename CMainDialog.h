#pragma once
#include "CByteBuffer.h"
#include "cpp/inc/CyAPI.h"
class CUSB;
class CMainDialog : public CDialogImpl <CMainDialog>
	, public CMessageFilter
	, public CWinDataExchange<CMainDialog>
{

	CUSB* m_pUSB;
	CComboBox m_cboDevices;
	CComboBox m_cboEndpointIN;
	CComboBox m_cboEndpointOUT;
	CEdit m_edtBytesOut;
	CEdit m_edtBytesIN;
	CEdit m_edtBytesMatlab;
	CEdit m_edtSpeed;
	CEdit m_edtBytesDiscard;
	CStatic m_stcDataReadyNum;
	CButton m_btnStart;
	CCyUSBDevice* m_selectedUSBDevice;
	BOOL m_bStarted;
	BOOL m_bUSB2MatlabCompleted;
	HANDLE m_hThread;
	CHandle m_hevtQuit;
	CByteBuffer m_buffer;
	INT64 m_llMatlabRead;
	INT64 m_llDiscard;
	INT64 m_llInBytes;
	INT64 m_llOutBytes;
	INT64 m_llDataReady;
	LONG  m_nDataReady;
	LONG  m_nReadyNum;
	

public:
	CString m_strFileName;
	LONG m_nDataReadyThreshold;
	enum { IDD = IDD_DIALOG_MAINDLG };
	VOID SetUSB(CUSB *p) {
		m_pUSB = p;
	}

	BEGIN_MSG_MAP(CMainDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_MY_DATAREADY, OnDataReady)

		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_BTN_START, BN_CLICKED, OnBnClickedBtnStart)
		COMMAND_HANDLER(IDC_BUTTON_REG, BN_CLICKED, OnBnClickedBtnReg)
		COMMAND_HANDLER(IDC_BUTTON_UNREG, BN_CLICKED, OnBnClickedBtnUnReg)
		COMMAND_HANDLER(IDC_BUTTON_HELP, BN_CLICKED, OnBnClickedBtnHelp)
		
	END_MSG_MAP()



	BEGIN_DDX_MAP(CMainDialog)

		DDX_CONTROL_HANDLE(IDC_CBO_DEVICES, m_cboDevices)
		DDX_CONTROL_HANDLE(IDC_CBO_IN_ENDPOINTS, m_cboEndpointIN)
		DDX_CONTROL_HANDLE(IDC_CBO_OUTENDPOINTS, m_cboEndpointOUT)

		DDX_CONTROL_HANDLE(IDC_EDT_BYTE_OUT, m_edtBytesOut)
		DDX_CONTROL_HANDLE(IDC_EDT_BYTE_IN, m_edtBytesIN)
		DDX_CONTROL_HANDLE(IDC_EDT_BYTE_MATLAB, m_edtBytesMatlab)
		DDX_CONTROL_HANDLE(IDC_EDT_BYTE_DISCARD, m_edtBytesDiscard)

		

		DDX_CONTROL_HANDLE(IDC_EDT_SPEED, m_edtSpeed)
		DDX_CONTROL_HANDLE(IDC_BTN_START, m_btnStart)
		DDX_CONTROL_HANDLE(IDC_STATIC_DATAREADY_NUM, m_stcDataReadyNum)
		
		DDX_TEXT(IDC_EDIT_FILESAVE, m_strFileName)

	END_DDX_MAP()




	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return ::IsDialogMessage(m_hWnd, pMsg);
	}
	LRESULT OnTimer(UINT  uMsg, WPARAM  wParam, LPARAM  lParam, BOOL& bHandled);


	LRESULT OnDestroy(UINT  uMsg , WPARAM  wParam, LPARAM  lParam , BOOL& bHandled)
	{
		//CDialogImpl <CMainDialog>::OnDestroy(uMsg, wParam, lParam, bHandled);
		if (m_bStarted) {
			BOOL b;
			OnBnClickedBtnStart(0, 0, 0, b);
		}
		if (m_selectedUSBDevice)
			delete m_selectedUSBDevice;

		return 0;
	}
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDI_ICON_USB, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDI_ICON_USB, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);

		DoDataExchange(FALSE);
		//m_selectedUSBDevice = new CCyUSBDevice(this->m_hWnd, CYUSBDRV_GUID, true);
		m_selectedUSBDevice = new CCyUSBDevice(NULL, CYUSBDRV_GUID, true);
		SurveyExistingDevices();
		EnumerateEndpointForTheSelectedDevice();
		m_hevtQuit.Attach(CreateEvent(NULL, TRUE, FALSE, NULL));
		if (!m_buffer.Initialize(1024 * 1024*256))
		{
			MessageBox(_T("Cannot alloc buffer"), MB_OK);
			BOOL b;
			OnCancel(0, 0, NULL, b);
		}
		return TRUE;
	}
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		return 0;
	}
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		LONG lLocks = _pAtlModule->GetLockCount();
		if (lLocks == 0) {
		//	DestroyWindow();
			PostThreadMessage(GetCurrentThreadId(), WM_MY_QUIT, 0, 0);
		}
		return 0;
	}
	VOID Start() {
		if (!m_bStarted) {
			BOOL b;
			OnBnClickedBtnStart(0, 0, 0, b);
		}
	}
	VOID Stop() {
		if (m_bStarted) {
			BOOL b;
			OnBnClickedBtnStart(0, 0, 0, b);
		}
	}
	VOID Read(PBYTE p, INT& len,BOOL bSync);
	VOID SetFileName(LPCTSTR str) {
		m_strFileName = str;
		DoDataExchange(FALSE);
	}
	LONG GetAvial() {
		return m_buffer.Avial();
	}

	CMainDialog() {
		m_selectedUSBDevice = NULL;
		m_bStarted = FALSE;
		m_bUSB2MatlabCompleted = FALSE;
		m_llMatlabRead = 0;
		m_nDataReady = 0;
		m_nDataReadyThreshold=10240;
		m_pUSB = NULL;
		m_llDiscard = 0;
		m_llDataReady = 0;
		m_llInBytes = 0;
		m_llOutBytes = 0;
		m_hThread = NULL;
	}
	BOOL EnumerateEndpointForTheSelectedDevice();
	BOOL SurveyExistingDevices();
	LRESULT OnBnClickedBtnReg(WORD, WORD, HWND, BOOL&);
	LRESULT OnBnClickedBtnUnReg(WORD, WORD, HWND, BOOL&);
	LRESULT OnBnClickedBtnHelp(WORD, WORD, HWND, BOOL&);
	LRESULT OnDataReady(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnBnClickedBtnStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	static unsigned WINAPI _PerformUSB2MatlabTransfer(LPVOID lParam);
	unsigned PerformUSB2MatlabTransfer();
};

