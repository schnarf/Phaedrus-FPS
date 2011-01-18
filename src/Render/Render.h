/* Render/Render.h
 *
 * The rendering task
 */

#pragma once

namespace System { class Window; class Kernel; }

namespace Render {

	class Render {
		friend class System::Kernel;
	public:
		//! Initialize
		Render( System::Kernel* pKernel );
		//! Deinitialize the task
		~Render();

		//! Renders our timeslice
		void Process();
		
		//! Gets our window
		System::Window* GetWindow() { return m_pWindow.get(); }
		
		//! Get the last time slice in milliseconds
		inline uint64 GetLastTimeslice() const { return m_uLastTimeslice; }
		
	private:
		System::Kernel* m_pKernel;			//!< Pointer to our kernel
	
		//! Our rendering window
		scoped_ptr<System::Window> m_pWindow;
		
		//! The last time slice, in milliseconds
		uint64 m_uLastTimeslice;
	}; // end class Render

} // end namespace Render
