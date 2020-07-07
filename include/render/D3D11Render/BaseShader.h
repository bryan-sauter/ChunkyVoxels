#ifndef BASESHADER_H_
#define BASESHADER_H_

#include "stdafx.h"

class BaseShader {

protected:
    ID3D11VertexShader* m_pVertexShader;
    ID3D11PixelShader* m_pPixelShader;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11SamplerState* m_pSampleState;
    ID3D11Buffer* m_pMatrixBuffer;
    ID3D11Buffer* m_pLightBuffer;

    BaseShader();
    bool Initialize(ID3D11Device* pDevice, WCHAR* vsFilePath, WCHAR* psFilePath);
public:

};


#endif //BASESHADER_H_
