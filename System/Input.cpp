#include "common.h"
#include "System/Input.h"
#include "System/Kernel.h"
#include <SDL.h>


//==================================================
//! Initialize the task
//==================================================
System::Input::Input() : System::Task("Input") {
}


//==================================================
//! Deinitialize the task
//==================================================
System::Input::~Input() {
}


//==================================================
//! Called whenever the thread is started
//==================================================
void System::Input::init() {
	// All keys are up
	m_keyStates.resize( NUM_INPUT_KEYS, false );
}


//==================================================
//! Called when the thread is stopped
//==================================================
void System::Input::deinit() {
}


//==================================================
//! Our main loop
//==================================================
void System::Input::process() {
	// Poll for all available events
	SDL_Event event;
	while( !m_queueEvents.empty() ) {
		event= m_queueEvents.front();
		{
			ScopedLock lock( m_mutexEvents );
			m_queueEvents.pop_front();
		}
	
		switch( event.type ) {
		case SDL_KEYDOWN:
			
		break;
		
		case SDL_KEYUP:
		break;
		
		case SDL_QUIT:
			// Tell the kernel to quit
			Kernel::Get()->Stop();
		break;
		
		default:
		break;
		};
	}; // end polling for events
	
	// Get the state of all keys
	byte* keystate= SDL_GetKeyState( NULL );
	{
		ScopedLock lock( m_mutexKeyStates );
		m_keyStates[INPUT_LEFT]= keystate[SDLK_LEFT];
		m_keyStates[INPUT_RIGHT]= keystate[SDLK_RIGHT];
		m_keyStates[INPUT_UP]= keystate[SDLK_UP];
		m_keyStates[INPUT_DOWN]= keystate[SDLK_DOWN];
		m_keyStates[INPUT_W]= keystate[SDLK_w];
		m_keyStates[INPUT_A]= keystate[SDLK_a];
		m_keyStates[INPUT_S]= keystate[SDLK_s];
		m_keyStates[INPUT_D]= keystate[SDLK_d];
	}
}


//==================================================
//! Get the state of a given key, true if down
//==================================================
bool System::Input::GetKeyState( InputKeys key ) {
	assert( key < NUM_INPUT_KEYS );
	ScopedLock lock( m_mutexKeyStates );
	return m_keyStates[key];
}


//==================================================
//! A task can be notified of an event
//==================================================
void System::Input::RegisterEvent( Task* pTask, EventType type, uint32 message ) {
}


//==================================================
//! Receive events from the window
//==================================================
void System::Input::postEvent( const SDL_Event* event ) {
	ScopedLock lock( m_mutexEvents );
	m_queueEvents.push_back( *event );
}


//==================================================
//! Our message processing function
//==================================================
void System::Input::processMessages() {
}