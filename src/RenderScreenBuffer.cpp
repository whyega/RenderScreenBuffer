#include "RenderScreenBuffer/RenderScreenBuffer.hpp"

RenderScreenBuffer::RenderScreenBuffer() {}

RenderScreenBuffer::~RenderScreenBuffer() {
  if (back_buffer_) back_buffer_->Release();
  if (system_surface_) system_surface_->Release();
  if (render_texture_) render_texture_->Release();
}

IDirect3DTexture9* RenderScreenBuffer::GetBuffer() {
  if (FAILED(
          device_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer_)))
    return nullptr;

  // Копируем в системную память
  if (FAILED(device_->GetRenderTargetData(back_buffer_, system_surface_))) {
    back_buffer_->Release();
    return nullptr;
  }

  // Получаем поверхность текстуры
  IDirect3DSurface9* texture_surface = nullptr;
  if (SUCCEEDED(render_texture_->GetSurfaceLevel(0, &texture_surface))) {
    // Копируем данные в текстуру
    device_->UpdateSurface(system_surface_, nullptr, texture_surface, nullptr);
    texture_surface->Release();
  }

  back_buffer_->Release();

  return render_texture_;
}

#ifndef RENDER_SCREEN_BUFFER_STATIC_DEFINE
RenderScreenBuffer* core = nullptr;

void* RenderScreenBufferInitialize() {
  core = new RenderScreenBuffer();
  return core;
}

void RenderScreenBufferRelease() {
  delete core;
  core = nullptr;
}

IDirect3DTexture9* RenderScreenBufferGetBuffer() {
  if (!core) return nullptr;
  return core->GetBuffer();
}
#endif