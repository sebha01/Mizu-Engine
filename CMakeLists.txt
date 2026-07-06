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

if (POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)
add_subdirectory(dependencies/glfw)

add_executable(cmake_test
	"Mizu Engine/main.cpp"
	"dependencies/glad/src/glad.c"
)

target_include_directories(cmake_test PRIVATE 
	"Mizu Engine"
	"dependencies/glad/include"
	"dependencies/glfw/include"
	"dependencies/glm"
)

target_link_libraries(cmake_test
	glfw
	OpenGL::GL
)