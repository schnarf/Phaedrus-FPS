/* System/Window.h
 *
 * Creates a window with a rendering context
 */

#pragma once

namespace Render { class Render; }

namespace System {

	class Input;

	class Window {
	public:
		enum {
			WINDOW_OPENGL= 1 << 0,
			WINDOW_FULLSCREEN= 1 << 1,
			NUM_WINDOW_FLAGS
		};
		
		//! Instantiate the window
		Window( string strTitle, uint uWidth, uint uHeight, uint eFlags, Render::Render* pRender, System::Input* pInput );
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
		
		//! SDL surface
		SDL_Surface* m_pSDLSurface;
		
		//! Rendering task
		Render::Render* m_pRender;
		
		//! The input task all windows report to
		static Input* m_pInput;
	}; // end class Window

} // end namespace System
