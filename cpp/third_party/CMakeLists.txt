set(third_party_folder "ThirdParty")

find_package(Vulkan REQUIRED)

if(NOT TARGET vma)
    add_library(vma INTERFACE)
    target_include_directories(vma INTERFACE vma)
endif()

if(NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
endif()

if(NOT TARGET glm)
    add_library(glm INTERFACE)
    target_include_directories(glm INTERFACE glm)
endif()


