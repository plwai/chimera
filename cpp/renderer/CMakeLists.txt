cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME ChimeraRenderer)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

file(GLOB EDITOR_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EDITOR_HEADERS} ${EDITOR_SOURCES})

add_executable(${TARGET_NAME} ${EDITOR_HEADERS} ${EDITOR_SOURCES})

target_include_directories(
  ${TARGET_NAME} 
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../shared_utils/include
  )

target_link_libraries(${TARGET_NAME} vma glm glfw Vulkan::Vulkan ChimeraUtils)
add_dependencies(ChimeraRenderer Shaders)

