#include "render/Camera.h"

Camera::Camera(void)
{
    m_mProjectionMatrix = glm::mat4(1.0f);
    m_mViewMatrix = glm::mat4(1.0f);
}

Camera::~Camera(void)
{
}

glm::mat4 Camera::getProjectionMatrix(void)
{
    return m_mProjectionMatrix;
}

void Camera::setProjectionMatrix(glm::mat4* mProjectionMatrix)
{
    memcpy(&m_mProjectionMatrix, mProjectionMatrix, sizeof(glm::mat4));
}

void Camera::buildPerspective(float fieldOfView, float zNear, float zFar)
{
    Globals& globals = Globals::getInstance();
    m_mProjectionMatrix = glm::perspectiveFovLH(fieldOfView, (float)globals.getWindowWidth(),
        (float)globals.getWindowHeight(), zNear, zFar);
}

glm::mat4 Camera::getViewMatrix(bool bTranslate)
{
    glm::mat4 mRotation(m_mViewMatrix), mTransform(1.0f);
    mRotation[3][0] = mRotation[3][1] = mRotation[3][2] = 0;
    mRotation = glm::transpose(mRotation);

    mTransform[3][0] = -(m_mViewMatrix[3][0]);
    mTransform[3][1] = -(m_mViewMatrix[3][1]);
    mTransform[3][2] = -(m_mViewMatrix[3][2]);

    mTransform = mTransform * mRotation;
    return (bTranslate ? mTransform : mRotation);
}

void Camera::setViewMatrix(glm::mat4* mViewMatrix)
{
    memcpy(&this->m_mViewMatrix, mViewMatrix, sizeof(glm::mat4));
}

glm::vec3 Camera::getViewXAxis(void)
{
    return glm::vec3(m_mViewMatrix[0][0],
                     m_mViewMatrix[0][1],
                     m_mViewMatrix[0][2]);
}

void Camera::setViewXAxis(glm::vec3 vPosition)
{
    m_mViewMatrix[0][0] = vPosition.x;
    m_mViewMatrix[0][1] = vPosition.y;
    m_mViewMatrix[0][2] = vPosition.z;
}

void Camera::setViewXAxis(float fX, float fY, float fZ)
{
    m_mViewMatrix[0][0] = fX;
    m_mViewMatrix[0][1] = fY;
    m_mViewMatrix[0][2] = fZ;
}

glm::vec3 Camera::getViewYAxis(void)
{
    return glm::vec3(m_mViewMatrix[1][0],
                     m_mViewMatrix[1][1],
                     m_mViewMatrix[1][2]);
}

void Camera::setViewYAxis(glm::vec3 vPosition)
{
    m_mViewMatrix[1][0] = vPosition.x;
    m_mViewMatrix[1][1] = vPosition.y;
    m_mViewMatrix[1][2] = vPosition.z;
}

void Camera::setViewYAxis(float fX, float fY, float fZ)
{
    m_mViewMatrix[1][0] = fX;
    m_mViewMatrix[1][1] = fY;
    m_mViewMatrix[1][2] = fZ;
}

glm::vec3 Camera::getViewZAxis(void)
{
    return glm::vec3(m_mViewMatrix[2][0],
                     m_mViewMatrix[2][1],
                     m_mViewMatrix[2][2]);
}

void Camera::setViewZAxis(glm::vec3 vPosition)
{
    m_mViewMatrix[2][0] = vPosition.x;
    m_mViewMatrix[2][1] = vPosition.y;
    m_mViewMatrix[2][2] = vPosition.z;
}

void Camera::setViewZAxis(float fX, float fY, float fZ)
{
    m_mViewMatrix[2][0] = fX;
    m_mViewMatrix[2][1] = fY;
    m_mViewMatrix[2][2] = fZ;
}

glm::vec3 Camera::getViewPosition(void)
{
    return glm::vec3(m_mViewMatrix[3][0],
                     m_mViewMatrix[3][1],
                     m_mViewMatrix[3][2]);
}

void Camera::setViewPosition(glm::vec3 vPosition)
{
    m_mViewMatrix[3][0] = vPosition.x;
    m_mViewMatrix[3][1] = vPosition.y;
    m_mViewMatrix[3][2] = vPosition.z;
}

void Camera::setViewPosition(float fX, float fY, float fZ)
{
    m_mViewMatrix[3][0] = fX;
    m_mViewMatrix[3][1] = fY;
    m_mViewMatrix[3][2] = fZ;
}