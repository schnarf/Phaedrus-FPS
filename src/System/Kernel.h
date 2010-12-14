#pragma once

namespace Render { class Render; }
namespace boost { class thread; }
namespace World { class World; class WorldUpdater; }
namespace VM { class VM; }

namespace System {

	class Task; class Window; class Input;

	class Kernel {
		friend class Task;
	public:
		//! Constructor, initializes the kernel if necessary
		Kernel();
		//! Destructor, deinitializes the kernel
		~Kernel();
	
		//! Starts the kernel
		void Start();
		//! Stops the kernel
		void Stop();
		
		inline bool IsRunning() const { return m_bIsRunning; }
		
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
		bool m_bIsRunning;
		
		//! The kernel's tasks
		vector<Task*> m_pTasks;
		
		//! Our input task
		shared_ptr<System::Input> m_pInput;
		
		//! Our rendering task
		shared_ptr<Render::Render> m_pRender;
		
		//! Our world updater task
		shared_ptr<World::WorldUpdater> m_pWorldUpdater;
		
		//! Our world
		shared_ptr<World::World> m_pWorld;
	};

};
