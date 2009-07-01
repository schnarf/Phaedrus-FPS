#include "System/Kernel.h"
#include "System/Task.h"
#include "System/Window.h"
#include "System/Input.h"
#include "Render/Render.h"
#include "World/WorldUpdater.h"
#include "World/World.h"
#include "VM/VM.h"
#include "System/VFS.h"
#include <iostream>

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
	m_pRender.reset( new Render::Render(this) );
	
	// Create the input task
	m_pInput.reset( new System::Input(this) );
	
	// Create the world update task
	m_pWorldUpdater.reset( new World::WorldUpdater(this) );
	
	
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
	m_pWorld->Unload();
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
	m_pWorld.reset( new World::World() );
	m_pWorld->Load();
	
	// A test
	//VM::VM::Get()->Execute( "PrintUint(GetEntity(GetLocalPlayerID()):GetID())" );
	//VM::VM::Get()->Execute( "vec = Vector(2.0, 3.0, 4.0);\n PrintFloat(vec:Length());\n PrintVector(vec:Normalize());\n" );
	
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

