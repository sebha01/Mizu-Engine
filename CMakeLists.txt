# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Mizu Engine Version 1.0.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)
add_subdirectory(dependencies/glfw)

add_executable(cmake_test
	"Mizu Engine/main.cpp"
	"dependencies/glad/src/glad.c"
	"Mizu Engine/Window/MizuEngineWindow.h" 
	"Mizu Engine/Window/MizuEngineWindow.cpp" 
	"Mizu Engine/Renderer/Renderer.h" 
	"Mizu Engine/Renderer/Renderer.cpp"  
	"Mizu Engine/Renderer/Colours.h" 
	"Mizu Engine/Renderer/ShaderClass/ShaderClass.h" 
	"Mizu Engine/Renderer/ShaderClass/ShaderClass.cpp" 
	"Mizu Engine/Renderer/VBO/VBO.h" 
	"Mizu Engine/Renderer/VBO/VBO.cpp" 
	"Mizu Engine/Renderer/EBO/EBO.h" 
	"Mizu Engine/Renderer/EBO/EBO.cpp" 
	"Mizu Engine/Renderer/VAO/VAO.h" 
	"Mizu Engine/Renderer/VAO/VAO.cpp" 
	"Mizu Engine/stb.cpp"
 "Mizu Engine/Renderer/Texture/Texture.h" "Mizu Engine/Renderer/Texture/Texture.cpp" "Mizu Engine/Renderer/Camera/Camera.h" "Mizu Engine/Renderer/Camera/Camera.cpp")

target_include_directories(cmake_test PRIVATE 
	"Mizu Engine"
	"dependencies/glad/include"
	"dependencies/glfw/include"
	"dependencies/glm"
	"dependencies/stb"
)

target_link_libraries(cmake_test
	glfw
	OpenGL::GL
)