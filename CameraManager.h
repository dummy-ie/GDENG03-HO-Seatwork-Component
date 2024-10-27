#pragma once

#include <vector>

#include "Camera.h"
#include "SceneCamera.h"

class CameraManager
{
private:
    SceneCamera* sceneCamera;
    Camera* mainCamera;
    std::vector<Camera*> cameras;

public:
    Matrix4x4 getMainCameraViewMatrix();
    Matrix4x4 getSceneCameraViewMatrix();
    void setMainCamera(Camera* camera);
    void setMainCameraByIndex(int index);
    void updateSceneCamera(float deltaTime);
    void addCamera(Camera* camera);
    void removeCamera(Camera* camera);

private:
    static CameraManager* P_SHARED_INSTANCE;

private:
    CameraManager();
    ~CameraManager();
    CameraManager(const CameraManager&);
    CameraManager& operator = (const CameraManager&);

public:
    static CameraManager* getInstance();
    static void initialize();
    static void destroy();
};
