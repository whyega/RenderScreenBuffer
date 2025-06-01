cmake_minimum_required(VERSION 3.15)
project(RenderScreenBuffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME})

if(DEFINED ${PROJECT_NAME}_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${${PROJECT_NAME}_SHARED_LIBS})
endif()

include(GenerateExportHeader)
set(export_file_name "export_shared.hpp")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.hpp")
endif()

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME include/${PROJECT_NAME}/${export_file_name})

set(sources
    include/${PROJECT_NAME}/export.h)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

include(FetchContent)

FetchContent_Declare(
  plugintmplt
  GIT_REPOSITORY https://github.com/whyega/plugintmplt.git
  GIT_TAG v1.0.2
)

FetchContent_Declare(
	xbyak    
	GIT_REPOSITORY https://github.com/herumi/xbyak.git
	GIT_TAG ce083a0dcc306c1717685a81f577a4e050193919
)

FetchContent_Declare( 
	ktsignal
	GIT_REPOSITORY https://github.com/kin4stat/ktsignal.git
	GIT_TAG f08a19d9a00ad5284871bf44178d835da7b26ebf
) 

FetchContent_Declare(
  kthook
  GIT_REPOSITORY https://github.com/kin4stat/kthook.git
  GIT_TAG 21ca70481273d1efcc98ca49063178e46277009b
)

FetchContent_MakeAvailable(plugintmplt xbyak ktsignal kthook)

list(APPEND ${PROJECT_NAME}_SRC
  include/${PROJECT_NAME}/export.hpp
  include/${PROJECT_NAME}/RenderScreenBuffer.hpp

  src/dllmain.cpp
  src/plugin.hpp
  src/plugin.cpp
  src/RenderScreenBuffer.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

target_link_libraries(${PROJECT_NAME} PRIVATE
  plugintmplt
  kthook
)

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

target_compile_definitions(${PROJECT_NAME} PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${PROJECT_NAME}_STATIC_DEFINE>")

set_target_properties(${PROJECT_NAME} PROPERTIES
  SUFFIX .asi
)