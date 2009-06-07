#ifndef _SYSTEM_WINDOW_H_
#define _SYSTEM_WINDOW_H_

#include "common.h"
#include <SDL.h>

namespace System {

	class Window {
	public:
		enum {
			WINDOW_OPENGL= 1,
			WINDOW_FULLSCREEN= 2,
			NUM_WINDOW_FLAGS
		};
		
		//! Instantiate the window
		Window( string strTitle, uint uWidth, uint uHeight, uint eFlags );
		//! De-initialize the window
		~Window();
		
		//! Set the window's title
		void SetTitle( const string& strTitle );
		
		//! Swap the buffers for an OpenGL window
		void SwapBuffers() const;
		
		//! Poll for events and pass them to the input system
		static void PollEvents();
	private:	
		uint m_uWidth, m_uHeight;
		string m_strTitle;
		uint m_eFlags;
		
		// SDL surface
		SDL_Surface* m_pSDLSurface;
	}; // end class Window

}; // end namespace System

#endif
