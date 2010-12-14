/* Render/Render.h
 *
 * The rendering task
 */

#pragma once

#include "System/Task.h"

namespace System { class Window; class Kernel; }

namespace Render {

	class Render : public System::Task {
		friend class System::Kernel;
	public:
		//! Initialize the task
		Render( System::Kernel* pKernel );
		//! Deinitialize the task
		~Render();
		
		//! Get the last time slice in milliseconds
		uint64 GetLastTimeslice() const;
		
	protected:
		//! Called whenever the thread is started
		void init();
		//! Called when the thread is stopped
		void deinit();
		//! Our main loop
		void process();
		//! Our message processing function
		void processMessages();
	
		//! Our rendering window
		System::Window* m_pWindow;
		
		//! The last time slice, in milliseconds
		uint64 m_uLastTimeslice;
	}; // end class Render

} // end namespace Render

//! Get the last time slice in milliseconds
inline uint64 Render::Render::GetLastTimeslice() const { return m_uLastTimeslice; }
