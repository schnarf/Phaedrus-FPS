# Luabind depends on boost
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

FILE(GLOB luabind_sources
	src/*.cpp
	luabind/*.h
)

# Include the luabind headers as well as lua headers
INCLUDE_DIRECTORIES(. ../lua/src)

ADD_LIBRARY(luabind STATIC ${luabind_sources})