#include "RenderScreenBuffer/RenderScreenBuffer.hpp"

RenderScreenBuffer::RenderScreenBuffer(IDirect3DDevice9* device, RECT rect)
    : device_(device), render_texture_(nullptr), rect_(rect) {}

RenderScreenBuffer::~RenderScreenBuffer() { Invalidate(); }

void RenderScreenBuffer::Invalidate() {
  if (render_texture_) render_texture_->Release();
}

IDirect3DTexture9* RenderScreenBuffer::GetBuffer() {
  if (!device_) return nullptr;

  if (!render_texture_) {
    const auto width = rect_.right - rect_.left;
    const auto height = rect_.bottom - rect_.top;
    if (FAILED(device_->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET,
                                      D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
                                      &render_texture_, nullptr))) {
      render_texture_ = nullptr;
    }
  }

  IDirect3DSurface9* back_buffer;
  if (FAILED(
          device_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer)))
    return nullptr;

  IDirect3DSurface9* texture_surface = nullptr;
  if (SUCCEEDED(render_texture_->GetSurfaceLevel(0, &texture_surface))) {
    device_->StretchRect(back_buffer, &rect_, texture_surface, nullptr,
                         D3DTEXF_NONE);
    texture_surface->Release();
  }

  back_buffer->Release();

  return render_texture_;
}