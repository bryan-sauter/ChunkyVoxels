#ifndef BASESHADER_H_
#define BASESHADER_H_

#include "stdafx.h"

class BaseShader {

    //give access to child classes
protected:
    ID3D11VertexShader* m_pVS;
    ID3D11PixelShader* m_pPS;
    ID3D11InputLayout* m_pLayout;

    void checkForShaderCompileError(HRESULT hr, ID3DBlob* shaderBlob, ID3DBlob* errorBlob);
    void baseInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath);
public:
    BaseShader();
    virtual void initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath) = 0;
    virtual void updateShader(ID3D11DeviceContext* pDeviceContext, DirectX::XMMATRIX mWVP) = 0;
};


#endif //BASESHADER_H_
