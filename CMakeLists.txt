cmake_minimum_required(VERSION 3.16)
project(nictophobia)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")

add_executable(nictophobia Nictophobia.cpp)

# module miocpp
target_sources(nictophobia PRIVATE
	miocpp/iopath.cpp
	miocpp/IODevice.cpp
	miocpp/DirDevice.cpp
	miocpp/FileReader.cpp
	miocpp/PhysicalFileReader.cpp
	miocpp/mio.cpp)
	

# module necore
target_sources(nictophobia PRIVATE
	necore/Window.cpp
	necore/Texture.cpp
	necore/Shader.cpp
	necore/Mesh.cpp
	necore/Font.cpp
	necore/FreeTypeFont.cpp
	necore/Batch2D.cpp
	necore/Camera.cpp
	necore/RasterImage.cpp
	necore/NeContext.cpp
	necore/Necore.cpp
	necore/NeAssets.cpp
	necore/debug/FreeCamera.cpp
	necore/formats/png_format.cpp
	necore/formats/obj_format.cpp
	necore/input/InputProcessor.cpp
	necore/input/InputBinding.cpp
	necore/assets/Assets.cpp
	necore/assets/AssetsLoader.cpp
	necore/stage/Stage.cpp
	necore/stage/Object.cpp
	necore/g2d/Sprite.cpp
	necore/g2d/LMPacker.cpp
	necore/gl/GLWindow.cpp
	necore/gl/GLTexture.cpp
	necore/gl/GLShader.cpp
	necore/gl/GLMesh.cpp)

find_package(Freetype REQUIRED)
target_link_libraries(nictophobia ${FREETYPE_LIBRARIES})
target_link_libraries(nictophobia png GL GLEW glfw)
target_include_directories(nictophobia PRIVATE ${FREETYPE_INCLUDE_DIRS})
