#pragma once
class CByteBuffer
{
	PBYTE m_pBuffer;
	ULONG m_nReadPtr;
	ULONG m_nWritePtr;
	ULONG m_nSize;
	ULONG m_nAvail;
	CComAutoDeleteCriticalSection m_cs;
	CHandle        m_evtWait;
public:
	CByteBuffer();
	BOOL Initialize(INT nSize);
	VOID Clean();
	VOID Reset();
	ULONG Write(PBYTE p, INT size, INT& discard);
	VOID  Read(PBYTE p, INT & size);
	VOID WaitData();
	LONG Avial() {
		return m_nAvail;
	}
};

