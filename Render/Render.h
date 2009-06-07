#ifndef _RENDER_RENDER_H_
#define _RENDER_RENDER_H_

#include "common.h"
#include "System/Task.h"

namespace System { class Window; }

namespace Render {

	class Render : public System::Task {
		friend class System::Kernel;
	public:
		//! Initialize the task
		Render();
		//! Deinitialize the task
		~Render();
		
		//! Get the last time slice in milliseconds
		uint GetLastTimeslice() const;
		
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
		uint m_uLastTimeslice;
	}; // end class Render

}; // end namespace Render

//! Get the last time slice in milliseconds
inline uint Render::Render::GetLastTimeslice() const { return m_uLastTimeslice; }

#endif
