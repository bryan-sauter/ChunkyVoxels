#include "render/D3D11Render/D3D11Camera.h"

D3D11Camera::D3D11Camera(void)
{
    XMStoreFloat4x4(&this->m_mProjectionMatrix, XMMatrixIdentity());
    XMStoreFloat4x4(&this->m_mViewMatrix, XMMatrixIdentity());
}

D3D11Camera::~D3D11Camera(void)
{
}

XMMATRIX D3D11Camera::getProjectionMatrix(void)
{
    return XMLoadFloat4x4(&m_mProjectionMatrix);
}

void D3D11Camera::setProjectionMatrix(XMFLOAT4X4* mProjectionMatrix)
{
    memcpy(&m_mProjectionMatrix, mProjectionMatrix, sizeof(XMFLOAT4X4));
}

void D3D11Camera::buildPerspective(float fieldOfView, float zNear, float zFar)
{
    Globals& globals = Globals::getInstance();
    XMStoreFloat4x4(&this->m_mProjectionMatrix, XMMatrixPerspectiveFovLH(fieldOfView, (float)globals.getWindowWidth() /
        (float)globals.getWindowHeight(), zNear, zFar));
}

XMMATRIX D3D11Camera::getViewMatrix(bool bTranslate)
{
    XMFLOAT4X4 mRotation(this->m_mViewMatrix), mTransform;
    mRotation._41 = mRotation._42 = mRotation._43 = 0;
    XMStoreFloat4x4(&mRotation, XMMatrixTranspose(XMLoadFloat4x4(&mRotation)));

    XMStoreFloat4x4(&mTransform, XMMatrixIdentity());
    mTransform._41 = -(this->m_mViewMatrix._41);
    mTransform._42 = -(this->m_mViewMatrix._42);
    mTransform._43 = -(this->m_mViewMatrix._43);

    XMStoreFloat4x4(&mTransform, 
        XMMatrixMultiply(XMLoadFloat4x4(&mTransform), XMLoadFloat4x4(&mRotation)));
    return (bTranslate ? XMLoadFloat4x4(&mTransform) : XMLoadFloat4x4(&mRotation));
}

void D3D11Camera::setViewMatrix(XMFLOAT4X4* mViewMatrix)
{
    memcpy(&this->m_mViewMatrix, mViewMatrix, sizeof(XMFLOAT4X4));
}

XMFLOAT3 D3D11Camera::getViewXAxis(void)
{
    return XMFLOAT3(m_mViewMatrix._11,
                    m_mViewMatrix._12,
                    m_mViewMatrix._13);
}

void D3D11Camera::setViewXAxis(XMFLOAT3 vPosition)
{
    setViewXAxis(vPosition.x, vPosition.y, vPosition.z);
}

void D3D11Camera::setViewXAxis(float fX, float fY, float fZ)
{
    this->m_mViewMatrix._11 = fX;
    this->m_mViewMatrix._12 = fY;
    this->m_mViewMatrix._13 = fZ;
}

XMFLOAT3 D3D11Camera::getViewYAxis(void)
{
    return XMFLOAT3(m_mViewMatrix._21,
                    m_mViewMatrix._22,
                    m_mViewMatrix._23);
}

void D3D11Camera::setViewYAxis(XMFLOAT3 vPosition)
{
    setViewYAxis(vPosition.x, vPosition.y, vPosition.z);
}

void D3D11Camera::setViewYAxis(float fX, float fY, float fZ)
{
    this->m_mViewMatrix._21 = fX;
    this->m_mViewMatrix._22 = fY;
    this->m_mViewMatrix._23 = fZ;
}

XMFLOAT3 D3D11Camera::getViewZAxis(void)
{
    return XMFLOAT3(m_mViewMatrix._31,
                    m_mViewMatrix._32,
                    m_mViewMatrix._33);
}

void D3D11Camera::setViewZAxis(XMFLOAT3 vPosition)
{
    setViewZAxis(vPosition.x, vPosition.y, vPosition.z);
}

void D3D11Camera::setViewZAxis(float fX, float fY, float fZ)
{
    this->m_mViewMatrix._31 = fX;
    this->m_mViewMatrix._32 = fY;
    this->m_mViewMatrix._33 = fZ;
}

XMFLOAT3 D3D11Camera::getViewPosition(void)
{
    return XMFLOAT3(m_mViewMatrix._41,
                    m_mViewMatrix._42,
                    m_mViewMatrix._43);
}

void D3D11Camera::setViewPosition(XMFLOAT3 vPosition)
{
    setViewPosition(vPosition.x, vPosition.y, vPosition.z);
}

void D3D11Camera::setViewPosition(float fX, float fY, float fZ)
{
    this->m_mViewMatrix._41 = fX;
    this->m_mViewMatrix._42 = fY;
    this->m_mViewMatrix._43 = fZ;
}

void D3D11Camera::viewRotateLocalX(float fAngle)
{
    XMFLOAT4X4 mRotation;
    XMFLOAT3 vLocalX(m_mViewMatrix._11, m_mViewMatrix._12, m_mViewMatrix._13);
    XMStoreFloat4x4(&mRotation, XMMatrixRotationAxis(XMLoadFloat3(&vLocalX), fAngle));

    XMFLOAT4 Position(this->m_mViewMatrix._41, this->m_mViewMatrix._42,
        this->m_mViewMatrix._43, this->m_mViewMatrix._44);
    this->m_mViewMatrix._41 = this->m_mViewMatrix._42 = this->m_mViewMatrix._43 = 0.0f;

    XMStoreFloat4x4(&m_mViewMatrix,
        XMMatrixMultiply(XMLoadFloat4x4(&m_mViewMatrix), XMLoadFloat4x4(&mRotation)));
    this->m_mViewMatrix._41 = Position.x; this->m_mViewMatrix._42 = Position.y;
    this->m_mViewMatrix._43 = Position.z; this->m_mViewMatrix._44 = Position.w;
}

void D3D11Camera::viewRotateLocalY(float fAngle)
{
    XMFLOAT4X4 mRotation;
    XMFLOAT3 vLocalY(m_mViewMatrix._21, m_mViewMatrix._22, m_mViewMatrix._23);
    XMStoreFloat4x4(&mRotation, XMMatrixRotationAxis(XMLoadFloat3(&vLocalY), fAngle));

    XMFLOAT4 Position(this->m_mViewMatrix._41, this->m_mViewMatrix._42,
        this->m_mViewMatrix._43, this->m_mViewMatrix._44);
    this->m_mViewMatrix._41 = this->m_mViewMatrix._42 = this->m_mViewMatrix._43 = 0.0f;

    XMStoreFloat4x4(&m_mViewMatrix,
        XMMatrixMultiply(XMLoadFloat4x4(&m_mViewMatrix), XMLoadFloat4x4(&mRotation)));
    this->m_mViewMatrix._41 = Position.x; this->m_mViewMatrix._42 = Position.y;
    this->m_mViewMatrix._43 = Position.z; this->m_mViewMatrix._44 = Position.w;
}

void D3D11Camera::viewRotateLocalZ(float fAngle)
{
    XMFLOAT4X4 mRotation;
    XMFLOAT3 vLocalZ(m_mViewMatrix._31, m_mViewMatrix._32, m_mViewMatrix._33);
    XMStoreFloat4x4(&mRotation, XMMatrixRotationAxis(XMLoadFloat3(&vLocalZ), fAngle));

    XMFLOAT4 Position(this->m_mViewMatrix._41, this->m_mViewMatrix._42,
        this->m_mViewMatrix._43, this->m_mViewMatrix._44);
    this->m_mViewMatrix._41 = this->m_mViewMatrix._42 = this->m_mViewMatrix._43 = 0.0f;

    XMStoreFloat4x4(&m_mViewMatrix,
        XMMatrixMultiply(XMLoadFloat4x4(&m_mViewMatrix), XMLoadFloat4x4(&mRotation)));
    this->m_mViewMatrix._41 = Position.x; this->m_mViewMatrix._42 = Position.y;
    this->m_mViewMatrix._43 = Position.z; this->m_mViewMatrix._44 = Position.w;
}

void D3D11Camera::viewTranslateLocal(XMFLOAT3 vAxis, bool bFPS)
{
    if (bFPS)
    {
        viewTranslateLocalX(vAxis.x, bFPS);
        viewTranslateLocalY(vAxis.y, bFPS);
        viewTranslateLocalZ(vAxis.z, bFPS);
        return;
    }

    viewTranslateLocalX(vAxis.x);
    viewTranslateLocalY(vAxis.y);
    viewTranslateLocalZ(vAxis.z);
}

void D3D11Camera::viewTranslateLocalX(float fScale, bool bFPS)
{
    if (bFPS)
    {
        XMFLOAT3 vTranslate((this->m_mViewMatrix._11),
            0.0f,
            (this->m_mViewMatrix._13));
        XMVECTOR xmvTranslate = XMLoadFloat3(&vTranslate);
        xmvTranslate = XMVector3Normalize(xmvTranslate);
        XMStoreFloat3(&vTranslate, XMVector3Normalize(xmvTranslate));

        this->m_mViewMatrix._41 += vTranslate.x * fScale;
        this->m_mViewMatrix._42 += vTranslate.y * fScale;
        this->m_mViewMatrix._43 += vTranslate.z * fScale;

        return;
    }
    this->m_mViewMatrix._41 += (this->m_mViewMatrix._11 * fScale);
    this->m_mViewMatrix._42 += (this->m_mViewMatrix._12 * fScale);
    this->m_mViewMatrix._43 += (this->m_mViewMatrix._13 * fScale);
}

void D3D11Camera::viewTranslateLocalY(float fScale, bool bFPS)
{
    if (bFPS)
    {
        XMFLOAT3 vTranslate((this->m_mViewMatrix._21),
            0.0f,
            (this->m_mViewMatrix._23));
        XMVECTOR xmvTranslate = XMLoadFloat3(&vTranslate);
        xmvTranslate = XMVector3Normalize(xmvTranslate);
        XMStoreFloat3(&vTranslate, XMVector3Normalize(xmvTranslate));

        this->m_mViewMatrix._41 += vTranslate.x * fScale;
        this->m_mViewMatrix._42 += vTranslate.y * fScale;
        this->m_mViewMatrix._43 += vTranslate.z * fScale;

        return;
    }
    this->m_mViewMatrix._41 += (this->m_mViewMatrix._21 * fScale);
    this->m_mViewMatrix._42 += (this->m_mViewMatrix._22 * fScale);
    this->m_mViewMatrix._43 += (this->m_mViewMatrix._23 * fScale);
}

void D3D11Camera::viewTranslateLocalZ(float fScale, bool bFPS)
{
    if (bFPS)
    {
        XMFLOAT3 vTranslate((this->m_mViewMatrix._31),
                                                 0.0f,
                             (this->m_mViewMatrix._33));
        XMVECTOR xmvTranslate = XMLoadFloat3(&vTranslate);
        xmvTranslate = XMVector3Normalize(xmvTranslate);
        XMStoreFloat3(&vTranslate, XMVector3Normalize(xmvTranslate));

        this->m_mViewMatrix._41 += vTranslate.x * fScale;
        this->m_mViewMatrix._42 += vTranslate.y * fScale;
        this->m_mViewMatrix._43 += vTranslate.z * fScale;

        return;
    }
    this->m_mViewMatrix._41 += (this->m_mViewMatrix._31 * fScale);
    this->m_mViewMatrix._42 += (this->m_mViewMatrix._32 * fScale);
    this->m_mViewMatrix._43 += (this->m_mViewMatrix._33 * fScale);
}
