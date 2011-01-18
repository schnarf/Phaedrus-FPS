#include "common.h"
#include "System/Window.h"
#include "System/Kernel.h"
#include "System/Input.h"
#include "Render/Render.h"
#include <iostream>

System::Input* System::Window::m_pInput= NULL;

//==================================================
//! Instantiate the window
//==================================================
System::Window::Window( string strTitle, uint uWidth, uint uHeight, uint eFlags, Render::Render* pRender, System::Input* pInput ) :
	m_uWidth(uWidth),
	m_uHeight(uHeight),
	m_eFlags(eFlags),
	m_pRender(pRender)  {
	
	m_eFlags= WINDOW_OPENGL;
	
	// We only handle OpenGL windows for now
	assert( m_eFlags & WINDOW_OPENGL );
	
	// Create an OpenGL window
	if( m_eFlags & WINDOW_OPENGL ) {
		// Configure OpenGL ettings
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		
		// SDL window flags
		int iFlags= SDL_OPENGL;
		if( eFlags & WINDOW_FULLSCREEN ) iFlags|= SDL_FULLSCREEN;
		
		// Attempt to create the window
		m_pSDLSurface= SDL_SetVideoMode( m_uWidth, m_uHeight, 32, iFlags );
		assert( m_pSDLSurface != NULL );
		
		// Enable Unicode translation
		SDL_EnableUNICODE( 1 );
		
		// Set the title
		SetTitle( strTitle );
	} // end if opengl

	m_pInput= pInput;

} // end Window::Window()


//==================================================
//! Set the window's title
//==================================================
void System::Window::SetTitle( const string& strTitle ) {
	char* c_title;
	char* c_icon;
	
	// Get the title and icon, we only care about the icon
	SDL_WM_GetCaption( &c_title, &c_icon );
	
	// Now set the new title and old icon
	m_strTitle= strTitle;
	SDL_WM_SetCaption( m_strTitle.c_str(), c_icon );
} // end WIndow::SetTItle()


//==================================================
//! Swap the buffers for an OpenGL window
//==================================================
void System::Window::SwapBuffers() const {	
	SDL_GL_SwapBuffers();
	SDL_Flip( m_pSDLSurface );
} // end Window::FlipBuffers()


//==================================================
//! Poll for events and pass them to the input system
//==================================================
void System::Window::PollEvents() {
	SDL_Event event;

	while( SDL_PollEvent(&event) ) {
		m_pInput->postEvent( &event );
	}
} // end Window::PollEvents()

//==================================================
//! De-initialize the window
//==================================================
System::Window::~Window() {
	
} // end Window::~Window()