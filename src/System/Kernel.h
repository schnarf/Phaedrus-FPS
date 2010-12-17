/* System/Kernel.h
 *
 * Manages all the tasks in the engine
 */

#pragma once

namespace Render { class Render; }
namespace boost { class thread; }
namespace World { class ResourceManager; class World; class WorldUpdater; }
namespace VM { class VM; }

namespace System {

	class Task; class Window; class Input; class VFS;

	class Kernel {
		friend class Task;
	public:
		//! Constructor, initializes the kernel if necessary
		Kernel();
		//! Destructor, deinitializes the kernel
		~Kernel();

		//! Starts the kernel's main loop
		void Start();
		//! Stops the kernel's main loop
		void Stop();
		
		inline bool IsRunning() const { return m_bRunning; }

		System::VFS* GetVFS() { return m_pVFS.get(); }
		VM::VM* GetVM() { return m_pVM.get(); }
		World::ResourceManager* GetResourceManager() { return m_pResourceManager.get(); }
		
		Render::Render* GetTaskRender() const { return m_pRender.get(); }
		System::Input* GetTaskInput() const { return m_pInput.get(); }
		World::WorldUpdater* GetTaskWorldUpdater() const { return m_pWorldUpdater.get(); }
		World::World* GetWorld() const { return m_pWorld.get(); }
		
	private:
		//! Adds a task to the kernel, called by the task's constructor
		void addTask( Task* pTask );
		
		//! Our kernel's main loop
		void run();
		
		//! Is our kernel running
		bool m_bRunning;

		//! Handles registering and unregistering our globals
		class KernelSentry {
		public:
			//! Initialize with kernel
			KernelSentry( Kernel* pKernel );
			//! Register the kernel's globals
			void Register();
			//! Unregister the kernel's globals
			~KernelSentry();
		private:
			Kernel* m_pKernel;
		}; // end class KernelSentry

		KernelSentry m_kernelSentry;			//!< Our kernel sentry, to register and unregister our globals
		
		//! The virtual filesystem
		shared_ptr<System::VFS> m_pVFS;
		//! The resource manager
		shared_ptr<World::ResourceManager> m_pResourceManager;
		//! The virtual machine
		shared_ptr<VM::VM> m_pVM;

		//! Our rendering task
		shared_ptr<Render::Render> m_pRender;
		
		//! Our input task
		shared_ptr<System::Input> m_pInput;
		
		//! Our world updater task
		shared_ptr<World::WorldUpdater> m_pWorldUpdater;
		
		//! Our world
		shared_ptr<World::World> m_pWorld;
		
		//! The kernel's tasks
		vector<Task*> m_pTasks;

		//! Stops our kernel with a fatal error
		void die( const string& strError );

	}; // end class Kernel

} // end namespace System
