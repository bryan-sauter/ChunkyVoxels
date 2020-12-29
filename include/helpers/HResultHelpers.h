#ifndef HRESULTHELPERS_H_
#define HRESULTHELPERS_H_

#include "stdafx.h"

inline std::string HrToString(HRESULT hr)
{
    char s_str[64] = {};
    sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    return std::string(s_str);
}

class HrException : public std::runtime_error
{
public:
    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
    HRESULT Error() const { return m_hr; }
private:
    const HRESULT m_hr;
};

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw HrException(hr);
    }
}

#define SAFE_RELEASE(p)if(p){p->Release();p=nullptr;}
#define SAFE_DELETE(p)if(p){delete p; p=nullptr;}
#define SAFE_SHUTDOWN(p)if(p){p->shutdown();SAFE_DELETE(p);}

#endif //HRESULTHELPERS_H_