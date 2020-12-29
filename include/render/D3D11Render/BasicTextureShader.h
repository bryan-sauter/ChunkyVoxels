#ifndef BASICTEXTURESHADER_H_
#define BASICTEXTURESHADER_H_

#include "BaseShader.h"
class BasicTextureShader : public BaseShader
{
private:
    struct VS_CONSTANT_BUFFER {
        DirectX::XMMATRIX mWorldViewProj;

        VS_CONSTANT_BUFFER(DirectX::XMMATRIX m) {
            this->mWorldViewProj = m;
        }
    } m_sConstantBuffer;
    D3D11_MAPPED_SUBRESOURCE m_sMappedResource;
    ID3D11Buffer* m_pCBuffer;

    ID3D11Resource* m_pTexture;
    ID3D11ShaderResourceView* m_pResourceView;
    ID3D11SamplerState* m_pSampleState;
    //TODO - debating if device and/or the context should be stored in the baseshader class
    //This would require a shader management class that the renderer would know to update on loss of device
    void initShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
public:
    BasicTextureShader(void);
    ~BasicTextureShader(void);
    void initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, LPCWSTR vsFilePath, LPCWSTR psFilePath);
    void loadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const wchar_t* texFilePath);
    void updateShader(ID3D11DeviceContext* pDeviceContext, DirectX::XMMATRIX mWVP);
    void updateShader(ID3D11DeviceContext* pDeviceContext, glm::mat4 mWVP);
};

#endif //BASICTEXTURESHADER_H_
