cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# set(OPENAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/openal/include)
# set(OPENAL_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/external/openal/build/Debug)
# set(OPENAL_LIBRARY ${OPENAL_LIBRARY_DIR}/OpenAL32)

# include_directories(${OPENAL_INCLUDE_DIR})
# include_directories(${CMAKE_SOURCE_DIR}/external/openal)
# include_directories(${OPENAL_LIBRARY_DIR})

# include_directories(${CMAKE_SOURCE_DIR}/external/irrKlang/include)
# include_directories(${CMAKE_SOURCE_DIR}/external/irrKlang/bin/winx64-visualStudio)

# find_package(openal REQUIRED)

set(SYSTEM_ENGINE src/System)

file(GLOB_RECURSE ENGINE_SYSTEM "src/System/*.h" "src/System/*.cpp" "src/System/*.cpp")
source_group("GameEngine/System" FILES ${ENGINE_SYSTEM})

file(GLOB_RECURSE ENGINE_PHYSICS "src/Physics/*.h" "src/Physics/*.cpp")
source_group("GameEngine/Physics" FILES ${ENGINE_PHYSICS})

file(GLOB_RECURSE ENGINE_RENDERER "src/Renderer/*.h" "src/Renderer/*.cpp")
source_group("GameEngine/Renderer" FILES ${ENGINE_RENDERER})

file(GLOB_RECURSE TEST_GAME "src/Game/*.h" "src/Game/*.cpp")
source_group("GameEngine/Game" FILES ${TEST_GAME})

file(GLOB_RECURSE TETRIS "src/Tetris/*.h" "src/Tetris/*.cpp")
source_group("Tetris" FILES ${TETRIS})

file(GLOB_RECURSE ENGINE_CONTROLLER "src/Controller/*.h" "src/Controller/*.cpp")
source_group("GameEngine/Controller" FILES ${ENGINE_CONTROLLER})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	
	${ENGINE_SYSTEM}
	${ENGINE_PHYSICS}
	${ENGINE_RENDERER}
	${ENGINE_CONTROLLER}
		
	src/Resources/stb_image.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h	

	${TEST_GAME}
	${TETRIS}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# include_directories(external/SDL)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

target_link_libraries(${PROJECT_NAME} glfw glad glm)

# target_link_libraries(${PROJECT_NAME} ${OPENAL_LIBRARY_DIR})

# target_link_libraries(${PROJECT_NAME} ${OPENAL_LIBRARY})

# message("-------OPENAL-------")
# message(${OPENAL_FOUND})
# message(${OPENAL_INCLUDE_DIR})
# message(${OPENAL_LIBRARY})
# message("--------------------")

# include_directories(external/openal/include)

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)