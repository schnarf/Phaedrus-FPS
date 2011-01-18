/* System/Input.h
 *
 * Interface between input devices and the engine
 */

#pragma once

#include "System/Window.h"

namespace System {

	class Kernel;

	enum InputKeys {
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_UP,
		INPUT_DOWN,
		INPUT_W,
		INPUT_A,
		INPUT_S,
		INPUT_D,
		NUM_INPUT_KEYS
	}; // end enum InputKeys
	
	class Input {
		friend class System::Window;
	public:
		//! Initialize the task
		Input( Kernel* pKernel );
		//! Deinitialize the task
		~Input();

		//! Processes our events
		void Process();
		
		enum EventType {
			EVENT_KEY_DOWN,
			EVENT_KEY_UP,
			EVENT_QUIT,
			NUM_EVENTS
		};
		
		struct Event {
			EventType type;
			uint32 data;
		}; // end struct Event
		
		//! Get the state of a given key, true if down
		bool GetKeyState( InputKeys key );
		
	private:
		Kernel* m_pKernel;			//!< Pointer to our kernel

		//! Receive events from the window
		void postEvent( const SDL_Event* event );
		//! Our system event queue
		deque<SDL_Event> m_queueEvents;
		//! Our event queue mutex
		Mutex m_mutexEvents;
		
		//! The key states
		vector<bool> m_keyStates;
		//! The mutex for key states
		Mutex m_mutexKeyStates;
		
	}; // end class Input

} // end namespace System
