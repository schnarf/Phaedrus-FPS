#ifndef _SYSTEM_TIMER_H_
#define _SYSTEM_TIMER_H_

#include "common.h"

namespace System {
	
	typedef uint64 Ticks;
	
	uint64 GetTickCountMillis();

}; // end namespace System

#endif
