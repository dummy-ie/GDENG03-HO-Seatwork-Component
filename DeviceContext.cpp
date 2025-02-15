#include "DeviceContext.h"

#include <exception>

#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RasterizerState.h"
#include "Viewport.h"
#include "RenderTexture.h"


using namespace graphics;

DeviceContext::DeviceContext(RenderSystem* system, ID3D11DeviceContext* device_context) : system(system), m_device_context(device_context)
{

}

DeviceContext::~DeviceContext()
{
	m_device_context->Release();
}

ID3D11DeviceContext* DeviceContext::getContext()
{
	return this->m_device_context;
}

void DeviceContext::clearRenderTargetColor(RenderTexture* renderTexture, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha };
	m_device_context->ClearRenderTargetView(renderTexture->renderTargetView, clear_color);
	m_device_context->ClearDepthStencilView(renderTexture->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_device_context->OMSetRenderTargets(1, &renderTexture->renderTargetView, renderTexture->depthStencilView);
}

void DeviceContext::setRenderTarget(RenderTexture* renderTexture)
{
	m_device_context->OMSetRenderTargets(1, &renderTexture->renderTargetView, renderTexture->depthStencilView);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;

	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::setIndexBuffer(IndexBuffer* index_buffer)
{
	m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawLineStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::setViewport(Viewport* vp)
{
	m_device_context->RSSetViewports(1, &vp->vp);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_device_context->RSSetViewports(1, &vp);
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->vertexShader, nullptr, 0);
}

void DeviceContext::setPixelShader(PixelShader* pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->pixelShader, nullptr, 0);
}

void DeviceContext::setConstantBuffer(ConstantBuffer* buffer, int index)
{
	m_device_context->VSSetConstantBuffers(index, 1, &buffer->m_buffer);
	m_device_context->PSSetConstantBuffers(index, 1, &buffer->m_buffer);
}

void DeviceContext::setRasterizerState(RasterizerState* rasterizer_state)
{
	m_device_context->RSSetState(rasterizer_state->m_rasterizer_state);
}