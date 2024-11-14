#pragma once

#include <string>
#include <unordered_map>

#include "Prerequisites.h"

namespace graphics
{
	class ShaderNames
	{
	public:
		const std::wstring BASE_VERTEX_SHADER_NAME = L"BaseVertexShader.hlsl";
		const std::wstring TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";

		const std::wstring BASE_PIXEL_SHADER_NAME = L"BasePixelShader.hlsl";
		const std::wstring TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
	};

	class ShaderLibrary
	{
	private:
		std::unordered_map<std::wstring, VertexShader*> activeVertexShaders;
		std::unordered_map<std::wstring, PixelShader*> activePixelShaders;

	public:
		class ShaderData
		{
		public:
			void* shaderByteCode = NULL;
			size_t sizeShader = 0;
		};

		void requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader);
		VertexShader* getVertexShader(std::wstring vertexShaderName);
		PixelShader* getPixelShader(std::wstring pixelShaderName);

	private:
		static ShaderLibrary* P_SHARED_INSTANCE;

	private:
		ShaderLibrary();
		~ShaderLibrary();
		ShaderLibrary(ShaderLibrary const&);
		ShaderLibrary& operator = (ShaderLibrary const&);

	public:
		static ShaderLibrary* getInstance();
		static void initialize();
		static void destroy();

	};
}