# Set CMake minimum version and CMake policy required by UrhoCommon module
cmake_minimum_required (VERSION 3.2.3)
if (COMMAND cmake_policy)
    # Libraries linked via full path no longer produce linker search paths
    cmake_policy (SET CMP0003 NEW)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy (SET CMP0022 NEW)
    # Disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy (SET CMP0042 NEW)
endif ()

#make sure append this to debug
set(CMAKE_DEBUG_POSTFIX "_d")

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

# Include Urho3D Cmake common module
include (UrhoCommon)

#include third party stuff
include_directories("../ThirdParty")
include_directories("../ThirdParty/Libigl")
include_directories("../ThirdParty/Eigen")
include_directories("../ThirdParty/TetGen")

# Define target name
set (TARGET_NAME Geometry)

#c11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#define includes
include_directories("./")
include_directories("../ThirdParty/Assimp/include")

# Define source files
define_source_files ()

list(APPEND SOURCE_FILES 
    "../ThirdParty/TetGen/tetgen.cxx"
    "../ThirdParty/TetGen/predicates.cxx")

file(GLOB SHAPEOP_SRC
    "../ThirdParty/ShapeOp/ShapeOp_*")

list(APPEND SOURCE_FILES ${SHAPEOP_SRC})

#get rid of resource copying
set(RESOURCE_DIRS "")

# Setup target with resource copying
setup_library ()

set_target_properties(Geometry PROPERTIES LINKER_LANGUAGE CXX)

#### RELEAE COPYING ######
install(TARGETS Geometry DESTINATION ${CMAKE_SOURCE_DIR}/SDK/lib )
