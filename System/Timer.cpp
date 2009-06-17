#include "System/Timer.h"

#include <SDL.h>

System::Ticks System::GetTickCountMillis() {
	static uint64 uLastTick= 0;
	uint64 uTick= (uint64)SDL_GetTicks();
	
	// Compensate for tick counter wraparound
	uLastTick= uTick;

	return uTick;
}