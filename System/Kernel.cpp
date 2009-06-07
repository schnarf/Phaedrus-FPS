#include "System/Kernel.h"
#include "System/Task.h"
#include "System/Window.h"
#include "System/Input.h"
#include "Render/Render.h"
#include "World/WorldUpdater.h"
#include "World/World.h"

// The kernel singleton
System::Kernel* System::Kernel::m_pKernel= NULL;

//==================================================
//! Constructor, initializes the kernel if necessary
//==================================================
System::Kernel::Kernel() {
	
}

//==================================================
//! Destructor, deinitializes the kernel
//==================================================
System::Kernel::~Kernel() {

}

//==================================================
//! Starts the kernel
//==================================================
void System::Kernel::Start() {
	
	// Create the rendering task
	m_pRender.reset( new Render::Render() );
	
	// Create the input task
	m_pInput.reset( new System::Input() );
	
	// Create the world update task
	m_pWorldUpdater.reset( new World::WorldUpdater() );
	
	
	
	// Start our main loop
	m_bIsRunning= true;
	
	run();
}

//==================================================
//! Stops the kernel
//==================================================
void System::Kernel::Stop() {
	// Stop running
	m_bIsRunning= false;
	
	// Unload the world
	World::World::Get()->Unload();
}

//==================================================
//! Our kernel's main loop
//==================================================
void System::Kernel::run() {
	// Start all tasks
	for( vector<Task*>::iterator it= m_pTasks.begin(); it != m_pTasks.end(); ++it ) {
		(*it)->Start();
	}
	
	// Load the world
	World::World::Get()->Load();

	while( m_bIsRunning ) {
		// Run all tasks
		// TODO: Run separate threads first so we don't wait?
		//       Really need to work out an order
		for( vector<Task*>::iterator it= m_pTasks.begin(); it != m_pTasks.end(); ++it ) {
			(*it)->Run();
		}
	};
	
	// Stop all tasks
	for( vector<Task*>::iterator it= m_pTasks.begin(); it != m_pTasks.end(); ++it ) {
		(*it)->Stop();
	}
}

//==================================================
//! Adds a task to the kernel, called by the task's constructor
//==================================================
void System::Kernel::addTask( System::Task* pTask ) {
	m_pTasks.push_back( pTask );
}


//==================================================
//! Public accessor function
//==================================================
System::Kernel* System::Kernel::Get() {
	// If we have no instance, create one
	if( m_pKernel == NULL ) {
		m_pKernel= new Kernel();
	}
	
	return m_pKernel;
}
