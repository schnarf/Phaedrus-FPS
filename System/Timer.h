#ifndef _SYSTEM_TIMER_H_
#define _SYSTEM_TIMER_H_

#include "common.h"

namespace System {

	typedef uint Ticks;
	
	Ticks GetTickCountMillis();

}; // end namespace System

#endif
