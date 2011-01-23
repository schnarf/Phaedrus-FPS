# We require boost
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost 1.45 REQUIRED COMPONENTS Python)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

# We require OpenGL
FIND_PACKAGE(OpenGL REQUIRED)

# We require SDL
FIND_PACKAGE(SDL REQUIRED)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

# We require SDL_image
FIND_PACKAGE(SDL_image REQUIRED)
INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})

# We require zlib
FIND_PACKAGE(zlib)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

# We require PhysicsFS
FIND_PACKAGE(physfs REQUIRED)
INCLUDE_DIRECTORIES(${PHYSFS_INCLUDE_DIR})

# We require libpng
FIND_PACKAGE(PNG REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR})

# We require Python
FIND_PACKAGE(PythonInterp REQUIRED)
FIND_PACKAGE(PythonLibs REQUIRED)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIR})

# Include our own folder
INCLUDE_DIRECTORIES(.)

# Add all our cpp and h files to the list of sources
FILE(GLOB phaedrus_sources 
	*.cpp
	common.cpp
	common.h
	common_exception.h
	globals.cpp
	globals.h
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
#ADD_DEPENDENCIES(phaedrusfps luabind)


# Set common.h as a precompiled header
IF(MSVC)
	SET_TARGET_PROPERTIES(phaedrusfps PROPERTIES COMPILE_FLAGS "/Yucommon.h")
	SET_SOURCE_FILES_PROPERTIES(common.cpp PROPERTIES COMPILE_FLAGS "/Yccommon.h")
ENDIF(MSVC)

# Link against our libraries
TARGET_LINK_LIBRARIES(phaedrusfps ${PHYSFS_LIBRARY} ${ZLIB_LIBRARY} ${PNG_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${PYTHON_LIBRARIES})