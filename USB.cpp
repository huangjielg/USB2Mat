// USB.cpp: CUSB 的实现

#include "pch.h"
#include "USB.h"

#include <atlsafe.h>
// CUSB



STDMETHODIMP CUSB::Start()
{
    // TODO: 在此处添加实现代码
    DWORD err=m_pDlg->Start();

    return AtlHresultFromWin32(err);
}


STDMETHODIMP CUSB::Stop()
{
    m_pDlg->Stop();
    return S_OK;
}

STDMETHODIMP CUSB::ReadDouble(LONG len, SAFEARRAY** pRetVal)
{
    return Read(len, pRetVal);
}
STDMETHODIMP CUSB::ReadDoubleSync(LONG len, SAFEARRAY** pRetVal)
{
    return ReadSync(len, pRetVal);
}
/*
STDMETHODIMP CUSB::ReadV(LONG len, VARIANT* pRetVal)
{
    if (len % 2) {
        CComSafeArray<unsigned char>* pSar;
        pSar = new CComSafeArray<unsigned char>(len);
        *pRetVal = pSar->Detach();
    }
    else {
        CComSafeArray<double>* pSar;
        pSar = new CComSafeArray<double>(len);
        *pRetVal = pSar->Detach();
    }
    return S_OK;
}
*/
STDMETHODIMP CUSB::Read(LONG len, SAFEARRAY** pRetVal)
{
    
    if (m_strOutFormat.IsEmpty()) {
        CComSafeArray<unsigned char>* pSar;
        pSar = new CComSafeArray<unsigned char>(len);

        INT l = len;
        m_pDlg->Read((PBYTE)pSar->m_psa->pvData, l, FALSE);
        if (l != len)
        {
            pSar->Resize(l);
        }
        *pRetVal = pSar->Detach();
    }
    else {
        if (m_strOutFormat.CompareNoCase(_T("%f")) == 0)
        {
            CComSafeArray<double>* pSar;
            
            int l = len * 4;
            m_vectReadBuffer.resize(l);
            
            m_pDlg->Read(m_vectReadBuffer.data(), l, FALSE);
            if (l != len * 4)
            {
                //如果没有对齐到4的倍数,则读取对齐
                int r;
                r = (len * 4 - l )  % 4 ;
                m_pDlg->Read(m_vectReadBuffer.data()+l, r, TRUE);
                l += r;
            }
            pSar = new CComSafeArray<double>(l/4);
            double d;
            for (int i = 0; i < l; i+=4) {
                int ii=0;
                ii =  m_vectReadBuffer[i] <<8;
                ii |= m_vectReadBuffer[i+1]<<16;
                ii |= m_vectReadBuffer[i+2]<<24;

                d = ii/256;
                ((double*)pSar->m_psa->pvData)[i / 4] = d;
            }

            *pRetVal = pSar->Detach();
        }
    }
    
        
    return S_OK;
}
STDMETHODIMP CUSB::ReadSync(LONG len, SAFEARRAY** pRetVal)
{
    if (m_strOutFormat.IsEmpty()) {
        CComSafeArray<unsigned char>* pSar;
        pSar = new CComSafeArray<unsigned char>(len);

        INT l = len;
        m_pDlg->Read((PBYTE)pSar->m_psa->pvData, l, TRUE);

        *pRetVal = pSar->Detach();
    }else  if (m_strOutFormat.CompareNoCase(_T("%f")) == 0)
    {
        CComSafeArray<double>* pSar;

        int l = len * 4;
        m_vectReadBuffer.resize(l);

        m_pDlg->Read(m_vectReadBuffer.data(), l, TRUE);
      
        pSar = new CComSafeArray<double>(l / 4);
        double d;
        for (int i = 0; i < l; i += 4) {
            int ii = 0;
            ii = m_vectReadBuffer[i] << 8;
            ii |= m_vectReadBuffer[i + 1] << 16;
            ii |= m_vectReadBuffer[i + 2] << 24;

            d = ii / 256;
            ((double*)pSar->m_psa->pvData)[i / 4] = d;
        }

        *pRetVal = pSar->Detach();
    }

    return S_OK;
}


STDMETHODIMP CUSB::get_saveFileName(BSTR* pVal)
{
    // TODO: 在此处添加实现代码
    CComBSTR str;
    str = m_pDlg->m_strFileName;
    *pVal = str.Detach();
    return S_OK;
}


STDMETHODIMP CUSB::put_saveFileName(BSTR newVal)
{
    // TODO: 在此处添加实现代码
    
    m_pDlg->SetFileName(newVal);
   
    
    return S_OK;
}

STDMETHODIMP  CUSB::get_Avial(LONG* pVal)
{
    *pVal=m_pDlg->GetAvial();
    return S_OK;
}

STDMETHODIMP  CUSB::get_readyThreshold(LONG* pVal)
{
    *pVal = m_pDlg->m_nDataReadyThreshold;
    return S_OK;
}

STDMETHODIMP  CUSB::put_readyThreshold(LONG newVal)
{
    m_pDlg->m_nDataReadyThreshold = newVal;
    return S_OK;
}

STDMETHODIMP  CUSB::ReadDirect(LONG len, SAFEARRAY** pRetVal)
{
    CComSafeArray<unsigned char>* pSar;
    pSar = new CComSafeArray<unsigned char>(len);
    DWORD err;
    if ((err=m_pDlg->ReadDirect((UCHAR*)pSar->m_psa->pvData, len)) == 0)
    {
        if (len != pSar->GetCount()) {
            pSar->Resize(len);
        }
        *pRetVal = pSar->Detach();
        return S_OK;
    }
    return AtlHresultFromWin32(err);;
}

STDMETHODIMP  CUSB::WriteDirect(SAFEARRAY* pVal)
{
    CComSafeArray<unsigned char> pSar;
    pSar.Attach(pVal);
    INT len=pSar.GetCount();
    DWORD err;
    if (err=m_pDlg->WriteDirect((PBYTE)pVal->pvData, len) == 0)
        return S_OK;
    else
        return AtlHresultFromWin32(err);

}

STDMETHODIMP CUSB::WriteReg(USHORT addr, USHORT Val)
{
    DWORD err;
    err=m_pDlg->WriteReg(addr, Val);
    return AtlHresultFromWin32(err);
}

STDMETHODIMP CUSB::ReadReg(USHORT addr, USHORT* pVal)
{
    DWORD err;
    err = m_pDlg->ReadReg(addr, pVal);
    return AtlHresultFromWin32(err);
}



STDMETHODIMP CUSB::get_doInit(
    /* [retval][out] */ LONG* pVal)
{
    *pVal = m_pDlg->m_bDoInit;
    return S_OK;
}

STDMETHODIMP CUSB::put_doInit(
    /* [in] */ LONG newVal)
{
    m_pDlg->m_bDoInit = newVal;
    return S_OK;
}


STDMETHODIMP CUSB::get_outFormat(BSTR* pVal)
{
    // TODO: 在此处添加实现代码
    CComBSTR str;
    str=m_strOutFormat;
    *pVal = str.Detach();
    return S_OK;
}


STDMETHODIMP CUSB::put_outFormat(BSTR newVal)
{
    m_strOutFormat = newVal;
    return S_OK;
}



STDMETHODIMP CUSB::get_cmdOutEnable(
    /* [retval][out] */ LONG* pVal)
{
    *pVal = m_pDlg->m_bCmdOutEnable;
    return S_OK;
}

STDMETHODIMP CUSB::put_cmdOutEnable(
    /* [in] */ LONG newVal)
{
    m_pDlg->m_bCmdOutEnable = newVal;
    return S_OK;
}


