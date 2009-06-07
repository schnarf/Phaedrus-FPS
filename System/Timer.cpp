#include "System/Timer.h"

#include <SDL.h>

System::Ticks System::GetTickCountMillis() {
	return SDL_GetTicks();
}