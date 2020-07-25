#ifndef CAMERA_H_
#define CAMERA_H_

#include "stdafx.h"
#include "helpers/Globals.h"

using namespace DirectX;

class D3D11Camera {
private:
    XMFLOAT4X4 m_mProjectionMatrix;
    XMFLOAT4X4 m_mViewMatrix;
public:
    D3D11Camera(void);
    ~D3D11Camera(void);
    //projection matrix functions
    XMMATRIX getProjectionMatrix(void);
    void setProjectionMatrix(XMFLOAT4X4* mProjectionMatrix);
    void buildPerspective(float fieldOfView, float zNear, float zFar);
    //view matrix functions
    XMMATRIX getViewMatrix(bool bTranslate = true);
    void setViewMatrix(XMFLOAT4X4* mMatrix);
    //view matrix functions
    //x-axis
    XMFLOAT3 getViewXAxis(void);
    void setViewXAxis(XMFLOAT3 vPosition);
    void setViewXAxis(float fX, float fY, float fZ);
    //y-axis
    XMFLOAT3 getViewYAxis(void);
    void setViewYAxis(XMFLOAT3 vPosition);
    void setViewYAxis(float fX, float fY, float fZ);
    //z-axis
    XMFLOAT3 getViewZAxis(void);
    void setViewZAxis(XMFLOAT3 vPosition);
    void setViewZAxis(float fX, float fY, float fZ);
    //set camera view position
    XMFLOAT3 getViewPosition(void);
    void setViewPosition(XMFLOAT3 vPosition);
    void setViewPosition(float fX, float fY, float fZ);

    void viewRotateLocalX(float fAngle);
    void viewRotateLocalY(float fAngle);
    void viewRotateLocalZ(float fAngle);

    void viewTranslateLocal(XMFLOAT3 vAxis, bool bFPS = false);
    void viewTranslateLocalX(float fScale, bool bFPS = false);
    void viewTranslateLocalY(float fScale, bool bFPS = false);
    void viewTranslateLocalZ(float fScale, bool bFPS = false);

};


#endif //CAMERA_H_