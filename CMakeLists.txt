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

file(GLOB_RECURSE HEADER_SYSTEM "src/System/*.h")
file(GLOB_RECURSE SRC_SYSTEM "src/System/*.cpp")
source_group("GameEngine/System/Source Files" FILES ${SRC_SYSTEM})
source_group("GameEngine/System/Header Files" FILES ${HEADER_SYSTEM})

file(GLOB_RECURSE HEADER_PHYSICH "src/Physics/*.h")
file(GLOB_RECURSE SRC_PHYSICH "src/Physics/*.cpp")
source_group("GameEngine/Physics/Source Files" FILES ${SRC_RENDERER})
source_group("GameEngine/Physics/Header Files" FILES ${HEADER_RENDERER})

file(GLOB_RECURSE HEADER_RENDERER "src/Renderer/*.h")
file(GLOB_RECURSE SRC_RENDERER "src/Renderer/*.cpp")
source_group("GameEngine/Renderer/Source Files" FILES ${SRC_RENDERER})
source_group("GameEngine/Renderer/Header Files" FILES ${HEADER_RENDERER})

file(GLOB_RECURSE HEADER_GAME "src/Game/*.h")
file(GLOB_RECURSE SRC_GAME "src/Game/*.cpp")
source_group("GameEngine/Game/Source Files" FILES ${SRC_GAME})
source_group("GameEngine/Game/Header Files" FILES ${HEADER_GAME})

file(GLOB_RECURSE HEADER_TETRIS "src/Tetris/*.h")
file(GLOB_RECURSE SRC_TETRIS "src/Tetris/*.cpp")
source_group("Tetris/Source Files" FILES ${SRC_TETRIS})
source_group("Tetris/Header Files" FILES ${HEADER_TETRIS})

file(GLOB_RECURSE HEADER_CONTROLLER "src/Controller/*.h")
file(GLOB_RECURSE SRC_CONTROLLER "src/Controller/*.cpp")
source_group("GameEngine/Controller/Source Files" FILES ${SRC_CONTROLLER})
source_group("GameEngine/Controller/Header Files" FILES ${HEADER_CONTROLLER})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	
	${HEADER_SYSTEM}
	${HEADER_PHYSICH}
	${HEADER_RENDERER}
	${HEADER_GAME}
	${HEADER_CONTROLLER}
	
	${SRC_SYSTEM}
	${SRC_PHYSICH}
	${SRC_RENDERER}
	${SRC_GAME}
	${SRC_CONTROLLER}
	
	src/Resources/stb_image.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h	
	
	${HEADER_TETRIS}
	${SRC_TETRIS}
	
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