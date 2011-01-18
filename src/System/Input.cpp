#include "common.h"
#include "System/Input.h"
#include "System/Kernel.h"


//==================================================
//! Initialize the task
//==================================================
System::Input::Input( Kernel* pKernel ) :
	m_pKernel(pKernel),
	m_keyStates(NUM_INPUT_KEYS, false) {
} // end Input::Input()


//==================================================
//! Deinitialize the task
//==================================================
System::Input::~Input() {
} // end Input::~Input()

//==================================================
//! Processes our events
//==================================================
void System::Input::Process() {
	// Poll for all available events
	SDL_Event event;
	while( !m_queueEvents.empty() ) {
		// Grab our event and process it
		event= m_queueEvents.front();
		m_queueEvents.pop_front();
	
		switch( event.type ) {
		case SDL_KEYDOWN:
		break;
		
		case SDL_KEYUP:
		break;
		
		case SDL_QUIT: {
			// Tell the kernel to quit
			m_pKernel->Stop();
			break;
		} // end case quit
		
		default:
		break;
		} // end switch event type
	}; // end polling for events
	
	// Get the state of all keys
	byte* keystate= SDL_GetKeyState( NULL );
	m_keyStates[INPUT_LEFT]= keystate[SDLK_LEFT];
	m_keyStates[INPUT_RIGHT]= keystate[SDLK_RIGHT];
	m_keyStates[INPUT_UP]= keystate[SDLK_UP];
	m_keyStates[INPUT_DOWN]= keystate[SDLK_DOWN];
	m_keyStates[INPUT_W]= keystate[SDLK_w];
	m_keyStates[INPUT_A]= keystate[SDLK_a];
	m_keyStates[INPUT_S]= keystate[SDLK_s];
	m_keyStates[INPUT_D]= keystate[SDLK_d];
} // end Input::Process()


//==================================================
//! Get the state of a given key, true if down
//==================================================
bool System::Input::GetKeyState( InputKeys key ) {
	assert( key < NUM_INPUT_KEYS );
	return m_keyStates[key];
} // end Input::GetKeyState()


//==================================================
//! Receive events from the window
//==================================================
void System::Input::postEvent( const SDL_Event* event ) {
	m_queueEvents.push_back( *event );
} // end Input::postEvent()