﻿#pragma once

#include <vector>

#include "Camera.h"
#include "SceneCamera.h"

class CameraManager
{
private:
    SceneCamera* sceneCamera;
    Camera* mainCamera;
    std::vector<Camera*> cameras;
    std::vector<SceneCamera*> sceneCameras;

public:
    Matrix4x4 getMainCameraViewMatrix();
    Matrix4x4 getMainCameraProjMatrix();
    Matrix4x4 getSceneCameraViewMatrix();
    Matrix4x4 getSceneCameraProjMatrix();
    SceneCamera* getSceneCamera();
    SceneCamera* getSceneCameraByIndex(int index);
    std::vector<SceneCamera*> getSceneCameras();
    void setMainCamera(Camera* camera);
    void setMainCameraByIndex(int index);
    void setSceneCameraProjection(int type);
    void updateSceneCamera(float deltaTime);
    void addCamera(Camera* camera);
    void addSceneCamera(SceneCamera* camera);
    void removeSceneCamera(SceneCamera* camera);
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
