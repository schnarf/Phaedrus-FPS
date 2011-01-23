/* System/Input.h
 *
 * Interface between input devices and the engine
 */

#pragma once

#include "System/Window.h"

namespace System {

	enum InputKeys {
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_UP,
		INPUT_DOWN,
		INPUT_W,
		INPUT_A,
		INPUT_S,
		INPUT_D,
		INPUT_SHIFT,
		INPUT_CTRL,
		NUM_INPUT_KEYS
	}; // end enum InputKeys
	
	class Input {
		friend class System::Window;
	public:
		//! Initialize the task
		Input();
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
		bool IsKeyDown( InputKeys key ) const;
		//! Gets whether we have received a quit signal
		bool IsQuit() const { return m_bQuit; }
	private:
		//! Receive events from the window
		void postEvent( const SDL_Event* event );
		//! Our system event queue
		deque<SDL_Event> m_queueEvents;
		
		//! The key states
		vector<bool> m_keyStates;

		//! Set to true when we receive the signal to quit
		bool m_bQuit;
		
	}; // end class Input

} // end namespace System
