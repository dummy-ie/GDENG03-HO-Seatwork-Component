#pragma once

#include "GameObject.h"
#include "InputListener.h"
#include "Vector2D.h"

enum ECameraMode
{
	ORTHO,
	PERSPECTIVE,
	ORTHO_TOP,
};

class Camera : public GameObject
{
	private:
		ConstantBuffer* constantBuffer;

	protected:
		int type = 1;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;

	public:
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

		__declspec(align(16))
			struct CBCameraData
		{
			Matrix4x4 viewMatrix;
			Matrix4x4 projMatrix;
		};
};

