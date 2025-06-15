#include "RenderScreenBuffer/RenderScreenBuffer.hpp"
#include "RenderScreenBuffer/export.hpp"

#ifndef RENDERSCREENBUFFER_STATIC_DEFINE
extern "C" {
RENDERSCREENBUFFER_API RenderScreenBuffer* RenderScreenBufferInitialize(
    IDirect3DDevice9* device, RECT rect) {
  return new RenderScreenBuffer(device, rect);
}

RENDERSCREENBUFFER_API void RenderScreenBufferShutdown(
    RenderScreenBuffer* core) {
  delete core;
  core = nullptr;
}

RENDERSCREENBUFFER_API void RenderScreenBufferInvalidate(
    RenderScreenBuffer* core) {
  if (!core) return;
  core->Invalidate();
}

RENDERSCREENBUFFER_API IDirect3DTexture9* RenderScreenBufferGetBuffer(
    RenderScreenBuffer* core) {
  if (!core) return nullptr;
  return core->GetBuffer();
}
}
#endif