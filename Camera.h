#pragma once

#include "GameObject.h"
#include "InputListener.h"
#include "Vector2D.h"

class Camera : public GameObject
{
	public:
		int type = 1;
		Matrix4x4 projMat;

		Camera(std::string name);
		~Camera();

	public:
		void onCreate() override;
		virtual void update(float deltaTime) override;
		void updateViewMatrix();
		virtual void updateProjectionMatrix();
		void onDestroy() override;

		Matrix4x4 getViewMatrix();
		Matrix4x4 getProjMatrix();
		void setProjectionType(int type);
};

