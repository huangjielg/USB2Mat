#include "pch.h"

#include <atlframe.h>
#include <atlgdi.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include "CMainDialog.h"
#include "USB.h"

#include "chelpdialog.h"
#ifdef _M_X64
#pragma comment(lib,"cpp/lib/x64/cyapi.lib")
#else
#pragma comment(lib,"cpp/lib/x86/cyapi.lib")
#endif

#pragma comment(lib,"setupapi.lib")
#pragma comment(lib,"legacy_stdio_definitions.lib")

#define     PACKETS_PER_TRANSFER                32
#define     NUM_TRANSFER_PER_TRANSACTION        64
#define     MAX_QUEUE_SZ                        NUM_TRANSFER_PER_TRANSACTION
#define     TIMEOUT_PER_TRANSFER_MILLI_SEC      1500


LRESULT CMainDialog::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == 0) {
		CString s;
		s.Format(L"%lld", m_llInBytes);
		m_edtBytesIN.SetWindowText(s);
		s.Format(L"%lld", m_llOutBytes);
		m_edtBytesOut.SetWindowText(s);

		s.Format(_T("%lld"), m_llMatlabRead);
		m_edtBytesMatlab.SetWindowText(s);


		s.Format(_T("%lld"), m_llDiscard);
		m_edtBytesDiscard.SetWindowText(s);

		s.Format(_T("DataReady:%lld"), m_llDataReady);
		m_stcDataReadyNum.SetWindowText(s);
	}
	else if (wParam == 1) {
		if (!m_selectedUSBDevice->IsOpen()) {
			SurveyExistingDevices();
			EnumerateEndpointForTheSelectedDevice();
			if (m_selectedUSBDevice->IsOpen())
			{
				KillTimer(1);
			}
		}
	}
	return LRESULT(0);
}

VOID CMainDialog::Read(PBYTE p, INT& len,BOOL bSync)
{
	INT oldlen = len;
	INT l;
	do {
		l = len;
		m_buffer.Read(p, l);
		len -= l;
		p += l;
		if (bSync) {
			m_buffer.WaitData();
		}
		m_llMatlabRead += l;
	} while (bSync && len);
	if (bSync) {
		len = oldlen;
	}
	else {
		len = l;
	}

	return VOID();
}

BOOL CMainDialog::EnumerateEndpointForTheSelectedDevice()
{
	int nDeviceIndex = 0;
	// Is there any FX device connected to system?
	if ((nDeviceIndex = m_cboDevices.GetCurSel()) == -1 || m_selectedUSBDevice == NULL) return FALSE;

	// There are devices connected in the system.       
	m_selectedUSBDevice->Open(nDeviceIndex);
	int interfaces = this->m_selectedUSBDevice->AltIntfcCount() + 1;
	m_cboEndpointIN.ResetContent();
	m_cboEndpointOUT.ResetContent();

	for (int nDeviceInterfaces = 0; nDeviceInterfaces < interfaces; nDeviceInterfaces++)
	{
		m_selectedUSBDevice->SetAltIntfc(nDeviceInterfaces);
		int eptCnt = m_selectedUSBDevice->EndPointCount();

		// Fill the EndPointsBox
		for (int endPoint = 1; endPoint < eptCnt; endPoint++)
		{
			CCyUSBEndPoint* ept = m_selectedUSBDevice->EndPoints[endPoint];

			// INTR, BULK and ISO endpoints are supported.
			if (ept->Attributes == 2)
			{
				CString strData(L""), strTemp;

				strData += ((ept->Attributes == 1) ? L"ISOC " : ((ept->Attributes == 2) ? L"BULK " : L"INTR "));
				strData += (ept->bIn ? L"IN, " : L"OUT, ");
				//strTemp.Format(L"%d  Bytes,", ept->MaxPktSize);
				//strData += strTemp;
				//
				//if(m_selectedUSBDevice->BcdUSB == USB30)
				//{
				//    strTemp.Format(L"%d  MaxBurst,", ept->ssmaxburst);
				//    strData += strTemp;
				//}

				strTemp.Format(L"AltInt - %d and EpAddr - 0x%02X", nDeviceInterfaces, ept->Address);
				strData += strTemp;
				if (ept->bIn) this->m_cboEndpointIN.AddString(strData);
				else this->m_cboEndpointOUT.AddString(strData);
			}
		}
	}

	if (m_cboEndpointOUT.GetCount() > 0) m_cboEndpointOUT.SetCurSel(0);
	if (m_cboEndpointIN.GetCount() > 0) m_cboEndpointIN.SetCurSel(0);

	this->m_btnStart.EnableWindow((m_cboEndpointIN.GetCount() > 0 && m_cboEndpointIN.GetCount() > 0));

	return TRUE;

}
BOOL CMainDialog::SurveyExistingDevices()
{
	CCyUSBDevice* USBDevice;
	USBDevice = new CCyUSBDevice(this->m_hWnd, CYUSBDRV_GUID, true);
	CString strDevice(L"");
	int nCboIndex = -1;
	if (m_cboDevices.GetCount() > 0) m_cboDevices.GetWindowText(strDevice);

	m_cboDevices.ResetContent();

	if (USBDevice != NULL)
	{
		int nInsertionCount = 0;
		int nDeviceCount = USBDevice->DeviceCount();
		for (int nCount = 0; nCount < nDeviceCount; nCount++)
		{
			CString strDeviceData;
			USBDevice->Open(nCount);
			strDeviceData.Format(L"(0x%04X - 0x%04X) %s", USBDevice->VendorID, USBDevice->ProductID, CString(USBDevice->FriendlyName));
			m_cboDevices.InsertString(nInsertionCount++, strDeviceData);
			if (nCboIndex == -1 && strDevice.IsEmpty() == FALSE && strDevice == strDeviceData)
				nCboIndex = nCount;

			USBDevice->Close();
		}
		delete USBDevice;
		if (m_cboDevices.GetCount() >= 1)
		{
			if (nCboIndex != -1) m_cboDevices.SetCurSel(nCboIndex);
			else m_cboDevices.SetCurSel(0);
		}
		SetFocus();
	}
	else return FALSE;

	return TRUE;
}
LRESULT CMainDialog::OnBnClickedBtnReg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (AtlComModuleRegisterServer(&_AtlComModule, TRUE, NULL) != S_OK)
	{
		MessageBox(_T("Register Failed,Please runas Administrator"));
	}
	else {
		MessageBox(_T("Register Success"));
	}
	return 0;
}
LRESULT CMainDialog::OnBnClickedBtnUnReg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (AtlComModuleUnregisterServer(&_AtlComModule, TRUE, NULL) != S_OK) {
		MessageBox(_T("UnRegister Failed,Please runas Administrator"));
	}
	else {
		MessageBox(_T("UnRegister Success"));
	}
	return 0;
}

LRESULT CMainDialog::OnBnClickedBtnHelp(WORD, WORD, HWND, BOOL&)
{
	CHelpDialog dlg;
	return  dlg.DoModal();

}

LRESULT CMainDialog::OnBnClickedBtnStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	if (!m_bStarted)
	{
		if (!DoDataExchange(TRUE))
			return -1;
		m_nReadyNum = 0;
		m_llDiscard = 0;
		m_llMatlabRead = 0;
		 m_llInBytes=0;
		 m_llDataReady = 0;
		 m_llOutBytes=0;
		 m_buffer.Reset();
	//	 m_threadIdMain = GetCurrentThreadId();
		m_edtBytesDiscard.SetWindowText(_T(""));
		m_edtBytesMatlab.SetWindowText(_T(""));
		m_btnStart.SetWindowText(L"Stop");
		//m_pThread = AfxBeginThread((AFX_THREADPROC)PerformUSB2MatlabTransfer, (LPVOID)this);
		unsigned id;
		m_hThread =(HANDLE) _beginthreadex(NULL, 0, _PerformUSB2MatlabTransfer, this,0,&id);
		m_bUSB2MatlabCompleted = FALSE;
		m_bStarted = TRUE;
		SetTimer(0, 1000, NULL);
		
	}
	else {
		KillTimer(0);
		m_bUSB2MatlabCompleted = TRUE;
		BOOL bContinue=TRUE;
		while(bContinue)
		{
			MSG msg;
			DWORD ret=MsgWaitForMultipleObjects(1, &m_hevtQuit.m_h, FALSE, INFINITE, QS_ALLINPUT);
			switch (ret)
			{
			case WAIT_OBJECT_0:
				bContinue = FALSE;
				break;
			case WAIT_OBJECT_0+1:
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				break;

			}

		}

		//WaitForSingleObject(m_hThread, INFINITE);
		ResetEvent(m_hevtQuit);
		CloseHandle(m_hThread);
		m_btnStart.SetWindowText(L"Start");
		BOOL b;
		OnTimer(0, 0, 0, b);
		m_bStarted = FALSE;
	}
	return 0;
}

unsigned  WINAPI CMainDialog::_PerformUSB2MatlabTransfer(LPVOID lParam)
{
	CMainDialog* pThis = (CMainDialog*)lParam;
	int ret=pThis->PerformUSB2MatlabTransfer();

	//if (m_bQuitApp || m_bDeviceChanging) PostMessage(WM_EXIT_APP, 0, 0);
	ATLTRACE(_T("WorkThread Quit\n"));
	SetEvent(pThis->m_hevtQuit);
	return ret;

}
unsigned  CMainDialog::PerformUSB2MatlabTransfer()
{
	ATLTRACE(_T("WorkThread Started %d\n"),GetCurrentThreadId());

	if ((m_cboEndpointIN.GetCount() == 0) || (m_cboEndpointOUT.GetCount() == 0))
	{
		return 0;
	}

	m_edtBytesIN.SetWindowText(L"0x0");
	m_edtBytesOut.SetWindowText(L"0x0");

	m_cboEndpointIN.EnableWindow(FALSE);
	m_cboEndpointOUT.EnableWindow(FALSE);

	CAtlFile fileSave;
	BOOL bDoSave= !m_strFileName.IsEmpty();
	if (bDoSave) {
		fileSave.Create(m_strFileName, GENERIC_WRITE, 0, CREATE_ALWAYS);
	}



	CString strINData, strOutData;
	TCHAR* pEnd;
	BYTE inEpAddress = 0x0, outEpAddress = 0x0;
	m_cboEndpointIN.GetWindowText(strINData);
	m_cboEndpointOUT.GetWindowText(strOutData);

	// Extract the endpoint addresses........
	strINData = strINData.Right(4);
	strOutData = strOutData.Right(4);

	inEpAddress = (BYTE)wcstoul(strINData.GetBuffer(0), &pEnd, 16);
	outEpAddress = (BYTE)wcstoul(strOutData.GetBuffer(0), &pEnd, 16);
	CCyUSBEndPoint* epBulkOut = m_selectedUSBDevice->EndPointOf(outEpAddress);
	CCyUSBEndPoint* epBulkIn = m_selectedUSBDevice->EndPointOf(inEpAddress);

	if (epBulkOut == NULL || epBulkIn == NULL) return 1;

	//
	// Get the max packet size (USB Frame Size).
	// For bulk burst transfer, this size represent bulk burst size.
	// Transfer size is now multiple USB frames defined by PACKETS_PER_TRANSFER
	//
	ULONG QueueSize = NUM_TRANSFER_PER_TRANSACTION;
	long totalTransferSize = epBulkIn->MaxPktSize * PACKETS_PER_TRANSFER;
	epBulkIn->SetXferSize(totalTransferSize);

	long totalOutTransferSize = epBulkOut->MaxPktSize * PACKETS_PER_TRANSFER;
	epBulkOut->SetXferSize(totalOutTransferSize);

	PUCHAR* buffersInput = new PUCHAR[QueueSize];
	PUCHAR* contextsInput = new PUCHAR[QueueSize];
	OVERLAPPED		inOvLap[MAX_QUEUE_SZ];

	// Allocate all the buffers for the queues
	for (int nCount = 0; nCount < QueueSize; nCount++)
	{
		buffersInput[nCount] = new UCHAR[totalTransferSize];
		inOvLap[nCount].hEvent = CreateEvent(NULL, false, false, NULL);

		memset(buffersInput[nCount], 0xEF, totalTransferSize);
	}

	
	OVERLAPPED  outOvLap;
	UCHAR* bufferOutput = new UCHAR[totalOutTransferSize];
	outOvLap.hEvent = CreateEvent(NULL, false, false, NULL);
	
	LONG len;
	BOOL bok;
#if 0

	// 1) 停止 AD采集
	 len = 1024;
	UCHAR wrStopCmd[] = { 0x57,0x52,0x00,0x00,0x00,0x00,0x00,0x00 };
	len = sizeof(wrStopCmd);
	epBulkOut->XferData(wrStopCmd, len);



	// 2) 清空 Input Pipe
	ULONG oldTimeout = epBulkIn->TimeOut;
	epBulkIn->TimeOut = 500;

	/*	do {
		len = totalTransferSize;

		bok=epBulkIn->XferData(buffersInput[0], len);
		} while (bok);
		*/
	epBulkIn->TimeOut = oldTimeout;

	//3) 开始AD采集
	UCHAR wrStartCmd[] = { 0x57,0x52,0x00,0x00,0x01,0x00,0x00,0x00 };
	len = sizeof(wrStartCmd);
	epBulkOut->XferData(wrStartCmd, len);
#endif
	// 4) 读取结果
	len = totalTransferSize;
	bok = epBulkIn->XferData(buffersInput[0], len);

	epBulkOut->TimeOut = TIMEOUT_PER_TRANSFER_MILLI_SEC;
	LARGE_INTEGER now, freq;
	::QueryPerformanceCounter(&now);
	::QueryPerformanceFrequency(&freq);


	// Queue-up the first batch of transfer requests
	for (int nCount = 0; nCount < QueueSize; nCount++)
	{
		////////////////////BeginDataXFer will kick start the IN transactions.................
		inOvLap[nCount].Internal = 0;
		inOvLap[nCount].InternalHigh = 0;
		inOvLap[nCount].Offset = 0;
		inOvLap[nCount].OffsetHigh = 0;
		contextsInput[nCount] = epBulkIn->BeginDataXfer(buffersInput[nCount], totalTransferSize, &inOvLap[nCount]);
		if (epBulkIn->NtStatus || epBulkIn->UsbdStatus)
		{
			// BeginDataXfer failed
			// Handle the error now.
			epBulkIn->Abort();
			for (int j = 0; j < QueueSize; j++)
			{
				CloseHandle(inOvLap[j].hEvent);
				delete[] buffersInput[j];
			}

			// Bail out......
			delete[]contextsInput;
			delete[] buffersInput;
			CString strMsg;
			strMsg.Format(L"BeginDataXfer Failed with (NT Status = 0x%X and USBD Status = 0x%X). Bailing out...", epBulkIn->NtStatus, epBulkIn->UsbdStatus);
			MessageBox(strMsg);
			return 0;
		}
	}



	long nCount = 0;
	long BytesXferred = 0;
	long outTransferred = 0;

	long speedc = 0;

	while (!m_bUSB2MatlabCompleted)
	{
		long readLength = totalTransferSize;
		//////////Wait till the transfer completion..///////////////////////////
		if (!epBulkIn->WaitForXfer(&inOvLap[nCount], TIMEOUT_PER_TRANSFER_MILLI_SEC))
		{
			epBulkIn->Abort();
			if (epBulkIn->LastError == ERROR_IO_PENDING)
				WaitForSingleObject(inOvLap[nCount].hEvent, TIMEOUT_PER_TRANSFER_MILLI_SEC);
		}

		////////////Read the trasnferred data from the device///////////////////////////////////////
		if (epBulkIn->FinishDataXfer(buffersInput[nCount], readLength, &inOvLap[nCount], contextsInput[nCount]))
			BytesXferred += totalTransferSize;


		//m_serverMatlab.PushData(d, sizeof(double) * readLength / 4);
		INT discard=0;
		m_buffer.Write(buffersInput[nCount], readLength,discard);

		if (bDoSave) {
			fileSave.Write(buffersInput[nCount], readLength);
		}
		if (m_pUSB) {

			
			LONG t;
			m_nReadyNum += readLength;
			if (m_nReadyNum >=m_nDataReadyThreshold) {
				if (t = InterlockedExchangeAdd(&m_nDataReady, 1))
				{
					m_nReadyNum -= m_nDataReadyThreshold;
					ATLTRACE(_T("dataReadNum =%d\n"), m_nDataReady);
					PostMessage(WM_MY_DATAREADY, 0, 0);
				}
			}
			
		}
		m_llDiscard += discard;
		m_llInBytes += readLength;
		
		if(discard!=0)
		{
			CString s;
			s.Format(_T("%lld"), m_llDiscard);
			m_edtBytesDiscard.SetWindowText(s);
		}
	

		

		// Re-submit this queue element to keep the queue full
		contextsInput[nCount] = epBulkIn->BeginDataXfer(buffersInput[nCount], totalTransferSize, &inOvLap[nCount]);
		if (epBulkIn->NtStatus || epBulkIn->UsbdStatus)
		{
			// BeginDataXfer failed............
			// Time to bail out now............
			epBulkIn->Abort();
			for (int j = 0; j < QueueSize; j++)
			{
				CloseHandle(inOvLap[j].hEvent);
				delete[] buffersInput[j];
			}
			delete[]contextsInput;

			CString strMsg;
			strMsg.Format(L"BeginDataXfer Failed during buffer re-cycle (NT Status = 0x%X and USBD Status = 0x%X). Bailing out...", epBulkIn->NtStatus, epBulkIn->UsbdStatus);
			MessageBox(strMsg);
			return 0;
		}
		if (++nCount >= QueueSize) {
			nCount = 0;
			speedc += totalTransferSize * QueueSize;
			if (speedc > 1024 * 1024)
			{
				LARGE_INTEGER now2;
				::QueryPerformanceCounter(&now2);
				ULONG speed = freq.QuadPart * speedc / (now2.QuadPart - now.QuadPart);
				CString s;
				s.Format(_T("%d Bytes/Sec"), speed);
				m_edtSpeed.SetWindowText(s);
				now = now2;
				speedc = 0;
			}
		}

	}

	epBulkIn->Abort();
	for (int j = 0; j < QueueSize; j++)
	{
		CloseHandle(inOvLap[j].hEvent);
		delete[] buffersInput[j];
	}

	// Bail out......
	delete[]contextsInput;
	delete[] buffersInput;
	delete[] bufferOutput;
	CloseHandle(outOvLap.hEvent);

	m_cboEndpointIN.EnableWindow(TRUE);
	m_cboEndpointOUT.EnableWindow(TRUE);

	fileSave.Close();

	return 1;
}

LRESULT CMainDialog::OnDataReady(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pUSB) {
		if (m_buffer.Avial() > m_nDataReadyThreshold) {
			if (InterlockedExchangeAdd(&m_nDataReady, -1)) {
				m_llDataReady++;
				m_pUSB->Fire_DataReady();
				return 0;
			}
		}
	}
	return 0;
}