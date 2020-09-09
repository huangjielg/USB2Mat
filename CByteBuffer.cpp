#include "pch.h"
#include "CByteBuffer.h"

CByteBuffer::CByteBuffer():m_pBuffer(NULL), m_nReadPtr(0), m_nWritePtr(0),m_nSize(0)
{


}



BOOL CByteBuffer::Initialize(INT nSize)
{
	m_pBuffer = (PBYTE)malloc(nSize);
	if (m_pBuffer == NULL)
		return FALSE;
	m_nSize = nSize;
	m_nReadPtr = 0;
	m_nWritePtr = 0;
	m_nAvail = 0;
	m_evtWait.Attach(CreateEvent(NULL, FALSE, FALSE,NULL));
	m_cs.Init();
	return TRUE;
}

VOID CByteBuffer::Clean()
{
	if (m_pBuffer) {
		free(m_pBuffer);
		m_pBuffer = NULL;
	}
	
	return VOID();
}

VOID CByteBuffer::Reset()
{
	m_nReadPtr = 0;
	m_nWritePtr = 0;
	m_nAvail = 0;
	return VOID();
}

ULONG CByteBuffer::Write(PBYTE p, INT size,INT &discard)
{
	CComCritSecLock<CComAutoDeleteCriticalSection> l(m_cs);
	
	if (size+m_nAvail >m_nSize) {
		discard = m_nAvail;
		m_nReadPtr = 0;
		m_nWritePtr = 0;
		m_nAvail = 0;
	}
	else {
		discard = 0;
	}
	INT cp;
	if (m_nWritePtr + size > m_nSize) {
		cp = m_nSize - m_nWritePtr;
		memcpy(m_pBuffer + m_nWritePtr, p, cp);
		memcpy(m_pBuffer, p+cp, size-cp);
	}
	else {
		cp = size;
		memcpy(m_pBuffer + m_nWritePtr, p, size);

	}
	m_nWritePtr += size;
	m_nWritePtr = m_nWritePtr % m_nSize;
	m_nAvail += size;

	
	PulseEvent(m_evtWait);
	return 0;
}

VOID CByteBuffer::Read(PBYTE p, INT& size)
{
	CComCritSecLock<CComAutoDeleteCriticalSection> l(m_cs);
	

	if (size > m_nAvail) {
		size = m_nAvail;
	}
	if (size != 0) {
		if (m_nReadPtr + size > m_nSize) {
			INT cp = m_nSize - m_nReadPtr;
			memcpy(p,m_pBuffer + m_nReadPtr,  cp);
			memcpy(p+cp,m_pBuffer,  size - cp);

		}
		else {
			memcpy(p, m_nReadPtr + m_pBuffer, size);
		}

		m_nAvail -=size;
		m_nReadPtr += size;
		m_nReadPtr %= m_nSize;
	}
	
	

	return VOID();
}

VOID CByteBuffer::WaitData()
{
	//WaitForSingleObject(m_evtWait, INFINITE);
	//return;

	BOOL bContinue = TRUE;
	while (bContinue)
	{
		MSG msg;
		DWORD ret = MsgWaitForMultipleObjects(1, &m_evtWait.m_h, FALSE, INFINITE, QS_ALLINPUT);
		switch (ret)
		{
		case WAIT_OBJECT_0:
			bContinue = FALSE;
			break;
		case WAIT_OBJECT_0 + 1:
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			break;
		}

	}
}
