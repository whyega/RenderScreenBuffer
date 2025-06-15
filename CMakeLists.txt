cmake_minimum_required(VERSION 3.15)
project(RenderScreenBuffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(${PROJECT_NAME})

if(DEFINED ${PROJECT_NAME}_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${${PROJECT_NAME}_SHARED_LIBS})
endif()

include(GenerateExportHeader)
set(EXPORT_FILE_NAME "export_shared.hpp")

if(NOT BUILD_SHARED_LIBS)
    set(EXPORT_FILE_NAME "export_static.hpp")
endif()

generate_export_header(${PROJECT_NAME}
    BASE_NAME RENDERSCREENBUFFER
    EXPORT_MACRO_NAME RENDERSCREENBUFFER_API
    EXPORT_FILE_NAME "include/${PROJECT_NAME}/${EXPORT_FILE_NAME}"
    STATIC_DEFINE MYLIBRARY_STATIC_DEFINE
)

list(APPEND ${PROJECT_NAME}_SRC
  include/${PROJECT_NAME}/export.hpp
  include/${PROJECT_NAME}/RenderScreenBuffer.hpp

  src/dllmain.cpp
  src/RenderScreenBuffer.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set(DXSDK_PATH "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)" CACHE PATH "Path to DirectX SDK")
if(EXISTS ${DXSDK_PATH})
  target_include_directories(${PROJECT_NAME} PRIVATE 
    ${DXSDK_PATH}/Include
  )
  target_link_directories(${PROJECT_NAME} PRIVATE
    ${DXSDK_PATH}/Lib/x86
  ) 
  target_link_libraries(${PROJECT_NAME} PRIVATE 
    d3d9 d3dx9
  )
else()
  message(WARNING "DirectX SDK not found. D3DX9 will be unavailable.")
endif()

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RENDERSCREENBUFFER_STATIC_DEFINE)
endif()