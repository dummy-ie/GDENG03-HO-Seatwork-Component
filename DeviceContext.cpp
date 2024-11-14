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
#include "Texture.h"


using namespace graphics;

DeviceContext::DeviceContext(RenderSystem* system, ID3D11DeviceContext* deviceContext) : system(system), deviceContext(deviceContext)
{

}

DeviceContext::~DeviceContext()
{
	deviceContext->Release();
}

ID3D11DeviceContext* DeviceContext::getContext()
{
	return this->deviceContext;
}

void DeviceContext::clearRenderTargetColor(const RenderTexture* renderTexture, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha };
	deviceContext->ClearRenderTargetView(renderTexture->renderTargetView, clear_color);
	deviceContext->ClearDepthStencilView(renderTexture->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	deviceContext->OMSetRenderTargets(1, &renderTexture->renderTargetView, renderTexture->depthStencilView);
}

void DeviceContext::setRenderTarget(const RenderTexture* renderTexture)
{
	deviceContext->OMSetRenderTargets(1, &renderTexture->renderTargetView, renderTexture->depthStencilView);
}

void DeviceContext::setVertexBuffer(const VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_size_vertex;
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);
	deviceContext->IASetInputLayout(vertexBuffer->m_layout);
}

void DeviceContext::setIndexBuffer(const IndexBuffer* indexBuffer)
{
	deviceContext->IASetIndexBuffer(indexBuffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->DrawIndexed(indexCount, startIndexLocation, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawLineStrip(UINT vertexCount, UINT startVertexIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewport(const Viewport* vp)
{
	deviceContext->RSSetViewports(1, &vp->vp);
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

	deviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::setVertexShader(const VertexShader* vertexShader)
{
	deviceContext->VSSetShader(vertexShader->vertexShader, nullptr, 0);
}

void DeviceContext::setPixelShader(const PixelShader* pixelShader)
{
	deviceContext->PSSetShader(pixelShader->pixelShader, nullptr, 0);
}

void DeviceContext::setTexture(const Texture* texture, int index)
{
	deviceContext->VSSetShaderResources(index, 1, &texture->shaderResourceView);
	deviceContext->PSSetShaderResources(index, 1, &texture->shaderResourceView);
}

void ::DeviceContext::setConstantBuffer(const ConstantBuffer* buffer, int index)
{
	deviceContext->VSSetConstantBuffers(index, 1, &buffer->m_buffer);
	deviceContext->PSSetConstantBuffers(index, 1, &buffer->m_buffer);
}

void DeviceContext::setRasterizerState(const RasterizerState* rasterizerState)
{
	deviceContext->RSSetState(rasterizerState->m_rasterizer_state);
}