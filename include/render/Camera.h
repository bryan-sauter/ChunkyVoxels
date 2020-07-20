#ifndef CAMERA_H_
#define CAMERA_H_

#include "stdafx.h"
#include "helpers/Globals.h"

class Camera {
private:
    glm::mat4 m_mProjectionMatrix;
    glm::mat4 m_mViewMatrix;
public:
    Camera(void);
    ~Camera(void);
    //projection matrix functions
    glm::mat4 getProjectionMatrix(void);
    void setProjectionMatrix(glm::mat4* mProjectionMatrix);
    void buildPerspective(float fieldOfView, float zNear, float zFar);
    //view matrix functions
    glm::mat4 getViewMatrix(bool bTranslate = true);
    void setViewMatrix(glm::mat4* mMatrix);
    //view axis functions
    //x-axis
    glm::vec3 getViewXAxis(void);
    void setViewXAxis(glm::vec3 vPosition);
    void setViewXAxis(float fX, float fY, float fZ);
    //y-axis
    glm::vec3 getViewYAxis(void);
    void setViewYAxis(glm::vec3 vPosition);
    void setViewYAxis(float fX, float fY, float fZ);
    //z-axis
    glm::vec3 getViewZAxis(void);
    void setViewZAxis(glm::vec3 vPosition);
    void setViewZAxis(float fX, float fY, float fZ);
    //set camera view position
    glm::vec3 getViewPosition(void);
    void setViewPosition(glm::vec3 vPosition);
    void setViewPosition(float fX, float fY, float fZ);

};


#endif //CAMERA_H_