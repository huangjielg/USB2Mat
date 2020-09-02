// USB.cpp: CUSB 的实现

#include "pch.h"
#include "USB.h"

#include <atlsafe.h>
// CUSB



STDMETHODIMP CUSB::Start()
{
    // TODO: 在此处添加实现代码
    m_pDlg->Start();

    return S_OK;
}


STDMETHODIMP CUSB::Stop()
{
    m_pDlg->Stop();
    return S_OK;
}


STDMETHODIMP CUSB::Read(LONG len, SAFEARRAY** pRetVal)
{
    // TODO: 在此处添加实现代码
    CComSafeArray<unsigned char>* pSar;
    pSar = new CComSafeArray<unsigned char>(len);
    
    INT l = len;
    m_pDlg->Read((PBYTE)pSar->m_psa->pvData, l,FALSE);
    if (l != len)
    {
        pSar->Resize(l);
    }
    *pRetVal = pSar->Detach();
        
    return S_OK;
}
STDMETHODIMP CUSB::ReadSync(LONG len, SAFEARRAY** pRetVal)
{
    // TODO: 在此处添加实现代码
    CComSafeArray<unsigned char>* pSar;
    pSar = new CComSafeArray<unsigned char>(len);

    INT l = len;
    m_pDlg->Read((PBYTE)pSar->m_psa->pvData, l, TRUE);

    *pRetVal = pSar->Detach();

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

STDMETHODIMP_(HRESULT __stdcall) CUSB::get_Avial(LONG* pVal)
{
    *pVal=m_pDlg->GetAvial();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) CUSB::get_readyThreshold(LONG* pVal)
{
    *pVal = m_pDlg->m_nDataReadyThreshold;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) CUSB::put_readyThreshold(LONG newVal)
{
    m_pDlg->m_nDataReadyThreshold = newVal;
    return S_OK;
}
