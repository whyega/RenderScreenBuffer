#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class RenderScreenBuffer {
 private:
  IDirect3DDevice9* device_;
  IDirect3DTexture9* render_texture_;
  RECT rect_;

 public:
  RenderScreenBuffer(IDirect3DDevice9* device, RECT rect);
  ~RenderScreenBuffer();

  void Invalidate();
  IDirect3DTexture9* GetBuffer();

 private:
  void CreateTexture();
};