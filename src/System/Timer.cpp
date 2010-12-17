#include "common.h"
#include "System/Timer.h"

uint64 System::GetTickCountMillis() {
	static uint64 uLastTick= 0;
	uint64 uTick= (uint64)SDL_GetTicks();
	
	// TODO: Compensate for tick counter wraparound
	uLastTick= uTick;

	return uTick;
}