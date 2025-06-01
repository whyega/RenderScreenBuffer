#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "export.hpp"


class RenderScreenBuffer {
 private:
  IDirect3DDevice9* device_;
  IDirect3DSurface9* back_buffer_;
  IDirect3DSurface9* system_surface_;
  IDirect3DTexture9* render_texture_;

 public:
  RenderScreenBuffer();
  ~RenderScreenBuffer();

  IDirect3DTexture9* GetBuffer();
};

#ifndef RENDER_SCREEN_BUFFER_STATIC_DEFINE
RENDER_SCREEN_RENDER_EXPORT void* RenderScreenBufferInitialize();
RENDER_SCREEN_RENDER_EXPORT void RenderScreenBufferRelease();
RENDER_SCREEN_RENDER_EXPORT IDirect3DTexture9* RenderScreenBufferGetBuffer();
#endif