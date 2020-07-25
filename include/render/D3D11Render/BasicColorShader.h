#ifndef BASICCOLORSHADER_H_
#define BASICCOLORSHADER_H_

#include "BaseShader.h"

class BasicColorShader : public BaseShader {

private:
    struct VS_CONSTANT_BUFFER {
        DirectX::XMMATRIX mWorldViewProj;

        VS_CONSTANT_BUFFER(DirectX::XMMATRIX m) {
            this->mWorldViewProj = m;
        }
    } m_sConstantBuffer;
    D3D11_MAPPED_SUBRESOURCE m_sMappedResource;

    ID3D11Buffer* m_pCBuffer;
    //TODO - debating if device and/or the context should be stored in the baseshader class
    //This would require a shader management class that the renderer would know to update on loss of device
    void initShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
public:
    BasicColorShader(void);
    void initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath);
    void updateShader(ID3D11DeviceContext* pDeviceContext, DirectX::XMMATRIX mWVP);
};

#endif
