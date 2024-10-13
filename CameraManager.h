#pragma once

#include <vector>

#include "Camera.h"

class CameraManager
{
private:
    Camera* mainCamera;
    std::vector<Camera*> cameras;

public:
    Camera* getMainCamera();
    void setMainCamera(Camera* camera);
    void setMainCameraByIndex(int index);
    void addCamera(Camera* camera);
    void removeCamera(Camera* camera);

private:
    static CameraManager* P_SHARED_INSTANCE;

private:
    CameraManager();
    CameraManager(const CameraManager&);
    CameraManager& operator = (const CameraManager&);

public:
    static CameraManager* getInstance();
    static void destroy();
};
