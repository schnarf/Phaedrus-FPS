#ifndef _SYSTEM_KERNEL_H_
#define _SYSTEM_KERNEL_H_

#include "common.h"

namespace Render { class Render; }
namespace boost { class thread; }
namespace World { class WorldUpdater; }

namespace System {

	class Task; class Window; class Input;

	class Kernel {
		friend class Task;
	public:
		//! Public accessor function
		static Kernel* Get();
		
		//! Starts the kernel
		void Start();
		//! Stops the kernel
		void Stop();
		
		inline bool IsRunning() const { return m_bIsRunning; }
		
		inline Render::Render* GetTaskRender() const { return m_pRender.get(); }
		inline System::Input* GetTaskInput() const { return m_pInput.get(); }
		inline World::WorldUpdater* GetTaskWorldUpdater() const { return m_pWorldUpdater.get(); }
		
	private:
		//! Constructor, initializes the kernel if necessary
		Kernel();
		//! Destructor, deinitializes the kernel
		~Kernel();
	
		//! Adds a task to the kernel, called by the task's constructor
		void addTask( Task* pTask );
		
		//! Our kernel's main loop
		void run();
		
		//! Is our kernel running
		bool m_bIsRunning;
	
		//! The kernel singleton
		static Kernel* m_pKernel;
		//! The kernel's tasks
		vector<Task*> m_pTasks;
		
		//! Our input task
		auto_ptr<System::Input> m_pInput;
		
		//! Our rendering task
		auto_ptr<Render::Render> m_pRender;
		
		// ! Our world updater task
		auto_ptr<World::WorldUpdater> m_pWorldUpdater;
	};

};

#endif
