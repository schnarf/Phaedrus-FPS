#ifndef _SYSTEM_INPUT_H_
#define _SYSTEM_INPUT_H_

#include "common.h"
#include "System/Task.h"
#include "System/Window.h"
#include <SDL.h>

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
		NUM_INPUT_KEYS
	}; // end enum InputKeys
	
	class Input : public Task {
		friend class System::Window;
	public:
		//! Initialize the task
		Input();
		//! Deinitialize the task
		~Input();
		
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
		
		//! A task can be notified of an event
		void RegisterEvent( Task* pTask, EventType type, uint32 message );
		
		//! Get the state of a given key, true if down
		bool GetKeyState( InputKeys key );
		
	protected:
		//! Called whenever the thread is started
		void init();
		//! Called when the thread is stopped
		void deinit();
		//! Our main loop
		void process();
		//! Our message processing function
		void processMessages();
		
	private:
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

}; // end namespace System

#endif
