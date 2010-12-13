# SDL image requires SDL
FIND_PACKAGE(SDL REQUIRED)

FILE(GLOB sdl_image_sources SDL_image/*.c SDL_image*.h)

INCLUDE_DIRECTORIES(SDL_image ${SDL_INCLUDE_DIR})

ADD_LIBRARY(sdl_image STATIC ${sdl_image_sources})