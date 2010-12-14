# We require boost
FIND_PACKAGE(Boost 1.45 REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_INCLUDE_DIRS}/stage/lib)
set(Boost_USE_STATIC_LIBS OFF)

# We require OpenGL
FIND_PACKAGE(OpenGL REQUIRED)

# We require SDL
FIND_PACKAGE(SDL REQUIRED)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

# Include our own folder
INCLUDE_DIRECTORIES(.)
# Include each of the libraries' headers
INCLUDE_DIRECTORIES(../lib/lua/src)
INCLUDE_DIRECTORIES(../lib/luabind)
INCLUDE_DIRECTORIES(../lib/PhysicsFS)
INCLUDE_DIRECTORIES(../lib/SDL_image)

# Add all our cpp and h files to the list of sources
FILE(GLOB phaedrus_sources 
	*.cpp
	common.cpp
	common.h
	Math/*.cpp
	Math/*.h
	Render/*.cpp
	Render/*.h
	System/*.cpp
	System/*.h
	VM/*.cpp
	VM/*.h
	World/*.cpp
	World/*.h
)

# If we're on mac, we need to add the SDLMain files
IF(MACOSX)
	FILE(GLOB phaedrus_sources ${phaedrus_sources} SDLMain.m SDLMain.h)
ENDIF(MACOSX)

# Create folders
SOURCE_GROUP(Math Math/*)
SOURCE_GROUP(Render Render/*)
SOURCE_GROUP(System System/*)
SOURCE_GROUP(Util Util/*)
SOURCE_GROUP(VM VM/*)
SOURCE_GROUP(World World/*)

ADD_EXECUTABLE(phaedrusfps ${phaedrus_sources})
ADD_DEPENDENCIES(phaedrusfps lua luabind physfs-static sdl_image)


# Set common.h as a precompiled header
IF(MSVC)
	SET_TARGET_PROPERTIES(phaedrusfps PROPERTIES COMPILE_FLAGS "/Yucommon.h")
	SET_SOURCE_FILES_PROPERTIES(common.cpp PROPERTIES COMPILE_FLAGS "/Yccommon.h")
ENDIF(MSVC)

# Link against our libraries
TARGET_LINK_LIBRARIES(phaedrusfps lua luabind physfs-static sdl_image ${SDL_LIBRARY} ${OPENGL_LIBRARIES})