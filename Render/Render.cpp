#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <SDL.h>

#include "common.h"

#include "System/Kernel.h"
#include "System/Window.h"
#include "System/Timer.h"
#include "Render/Render.h"

#include "World/ResourceManager.h"
#include "World/Texture.h"

#include "World/ParticleSystem.h"

#include "World/Level.h"

#include "World/World.h"
#include "World/PlayerEntity.h"

// Threading: Anything SDL-related must be called in this thread.


//==================================================
//! Initialize the task
//==================================================
Render::Render::Render() : System::Task("Render", false) {
}


//==================================================
//! Deinitialize the task
//==================================================
Render::Render::~Render() {
}

//==================================================
//! Called whenever the thread is started
//==================================================
void Render::Render::init() {
	// Initialize timeslice to zero
	m_uLastTimeslice= 0;

	SDL_Init( SDL_INIT_VIDEO );
	
	uint uWidth= 1152;
	uint uHeight= 864;

	// Get our rendering window
	m_pWindow= new System::Window( "Test", uWidth, uHeight, System::Window::WINDOW_OPENGL );
	
	// Set up OpenGL
	glEnable( GL_TEXTURE_2D );
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth( 1.0f );
	
	// Depth testing
/*	glEnable( GL_DEPTH_TEST );
	glDepthMask( GL_TRUE );
	glDepthFunc( GL_LESS );
	*/
	// Backface culling
	//glEnable( GL_CULL_FACE );
	//glCullFace( GL_BACK );
	
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	
	glViewport( 0.0f, 0.0f, (float)uWidth, (float)uHeight );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, (float)uWidth/(float)uHeight, 1.0f, 1024.0f );
}


//==================================================
//! Called when the thread is stopped
//==================================================
void Render::Render::deinit() {
	delete m_pWindow;
	
	// Shut down SDL
	SDL_Quit();
}


//==================================================
//! Our main loop
//==================================================
void Render::Render::process() {
	if( !System::Kernel::Get()->IsRunning() ) return;
	
	// Begin our timeslice
	uint uStartTicks= System::GetTickCountMillis();

	// Clear
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClearDepth( 0.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// Orient the camera
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, 1.3333333333f, 1.0f, 1024.0f );
	Math::Vector eyepos, lookvec;
	eyepos= World::World::Get()->GetLocalPlayer()->GetEyePosition();
	lookvec= World::World::Get()->GetLocalPlayer()->GetLookVector() + eyepos;
	gluLookAt( eyepos.X(), eyepos.Y(), eyepos.Z(), lookvec.X(), lookvec.Y(), lookvec.Z(), 0.0, 1.0, 0.0 );
	
	// Draw the level
	World::World::Get()->GetLevel()->Render();
	
	// Draw entities
	
	m_pWindow->SwapBuffers();
	
	assert( glGetError() == GL_NO_ERROR );
	
	// End our timeslice
	uint uEndTicks= System::GetTickCountMillis();
	m_uLastTimeslice= uEndTicks - uStartTicks;
}


//==================================================
//! Our message processing function
//==================================================
void Render::Render::processMessages() {
	m_pWindow->PollEvents();
}

