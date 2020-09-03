#pragma once
class CHelpDialog : public CDialogImpl <CHelpDialog>
	, public CMessageFilter
	, public CWinDataExchange<CHelpDialog>
{
	CEdit m_edtHelpText;
public:
	enum { IDD = IDD_DIALOG_HELP };
	BEGIN_MSG_MAP(CHelpDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)


		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(ID_BUTTON_GENFILE, BN_CLICKED, OnGenFile)

	END_MSG_MAP()


	BEGIN_DDX_MAP(CMainDialog)
		DDX_CONTROL_HANDLE(IDC_EDIT_TEXT, m_edtHelpText)
	END_DDX_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return ::IsDialogMessage(m_hWnd, pMsg);
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


		CString s;
		s = _T("1: Runas Administrator ,clk reg\r\n"
			"2: Launch matlab:\r\n"
			"3: a=actxserver('USB2Mat.USB');\r\n"
			"4: a.saveFileName='d:\\a.bin';\r\n"
			"7: a.Start();\r\n"
			"6.1: a.Read(100);%read atmost 100 bytes\r\n"
		"6.2: a.ReadSync(100);%Wait Until 100bytes read\r\n"
		"6.3: a.Avial;\r\n"
		"7: a.Stop();\r\n"
			"8: delete(a);\r\n"
			"9: readyThreshold : send DataReady threshold\r\n"
			" registerevent(a,{'DataReady', @myReady})\r\n"
			"function myReady(~, ~, ~, ~)\r\n"
			"	1 \r\n"
			"	end \r\n"
			);
		m_edtHelpText.SetWindowText(s);
		return TRUE;
	}
	LRESULT OnGenFile(WORD, WORD, HWND, BOOL&)
	{
		TCHAR szModule1[MAX_PATH];
		TCHAR szModule2[MAX_PATH];
		TCHAR* pszFileName;
		
		DWORD dwFLen = ::GetModuleFileName(NULL, szModule1 , MAX_PATH);
		if (dwFLen == 0 || dwFLen == MAX_PATH)
			return FALSE;
		DWORD dwRet = ::GetFullPathName(szModule1, MAX_PATH, szModule2, &pszFileName);
		if (dwRet == 0 || dwRet > MAX_PATH)
		{
			return FALSE;
		}
		CString sDir = szModule2;
		sDir.SetAt(sDir.ReverseFind(_T('\\')), 0);
		struct {
			LPCTSTR name;
			INT id;
		}matlabfiles[] = { {_T("USBReady.m"),IDR_MAT_DATAREADY},
							{_T("testMat2USB.m"),IDR_MAT_MAINTEST},
		};
		for (int i = 0; i < sizeof(matlabfiles) / sizeof(matlabfiles[0]); i++) {
			HRSRC hRsrc = FindResource(ModuleHelper::GetResourceInstance(), MAKEINTRESOURCE(matlabfiles[i].id), TEXT("MATLAB"));


			HGLOBAL hglob = LoadResource(ModuleHelper::GetResourceInstance(), hRsrc);

			DWORD dwSize = SizeofResource(NULL, hRsrc);
			LPVOID pBuffer = LockResource(hglob);
			CString sFileName;
			sFileName.Format(_T("%s\\%s"), sDir, matlabfiles[i].name);
			CAtlFile f;
			f.Create(sFileName, GENERIC_WRITE, 0, CREATE_ALWAYS);
			f.Write(pBuffer, dwSize);
			f.Close();
			MessageBox(sFileName, _T("fileCreated"));
			UnlockResource(hglob);
		}
	
		return 0;
	}
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		return EndDialog(IDOK);
	
	}
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		return EndDialog(IDCANCEL);

	}
};

