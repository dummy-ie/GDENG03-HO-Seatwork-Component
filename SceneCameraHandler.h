#pragma once

#include "SceneCamera.h"

class SceneCameraHandler
{
public:
    Matrix4x4 getSceneCameraViewMatrix();

private:
    SceneCamera* sceneCamera;

private:
    static SceneCameraHandler* P_SHARED_INSTANCE;

private:
    SceneCameraHandler();
    SceneCameraHandler(const SceneCameraHandler&);
    SceneCameraHandler& operator = (const SceneCameraHandler&);

public:
    static SceneCameraHandler* getInstance();
    static void initialize();
    static void destroy();
};

