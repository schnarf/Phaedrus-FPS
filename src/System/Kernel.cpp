#include "common.h"
#include "System/Kernel.h"
#include "System/Task.h"
#include "System/Window.h"
#include "System/Input.h"
#include "Render/Render.h"
#include "World/ResourceManager.h"
#include "World/WorldUpdater.h"
#include "World/World.h"
#include "VM/VM.h"
#include "System/VFS.h"
#include <iostream>

//==================================================
//! Constructor, initializes the kernel if necessary
//==================================================
System::Kernel::Kernel() :
	m_kernelSentry(this),
	m_pVFS(new System::VFS),
	m_pVM(new VM::VM),
	m_pResourceManager(new World::ResourceManager),
	m_bRunning(false) {

	m_kernelSentry.Register();
	
	m_pRender.reset( new Render::Render(this) );
	m_pInput.reset( new System::Input(this) );
	m_pWorldUpdater.reset( new World::WorldUpdater(this) );

} // end Kernel::Kernel()


//==================================================
//! Destructor, deinitializes the kernel
//==================================================
System::Kernel::~Kernel() {
	// Stop running
	m_bRunning= false;
} // end Kernel::~Kernel()


//! Starts the kernel's main loop
void System::Kernel::Start() {
	assert( !m_bRunning );
	m_bRunning= true;
	run();
} // end Kernel::Start()


//! Stops the kernel's main loop
void System::Kernel::Stop() {
	m_bRunning= false;
} // end Kernel::Stop()


//==================================================
//! Our kernel's main loop
//==================================================
void System::Kernel::run() {
	// Start all tasks
	for( vector<Task*>::iterator it= m_pTasks.begin(); it != m_pTasks.end(); ++it ) {
		(*it)->Start();
	}
	
	// Load the world
	m_pWorld.reset( new World::World );
	if( !m_pWorld->IsLoaded() ) die( "Could not load the world!" );
	
	while( m_bRunning ) {
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
} // end Kernel::run()


//==================================================
//! Adds a task to the kernel, called by the task's constructor
//==================================================
void System::Kernel::addTask( System::Task* pTask ) {
	m_pTasks.push_back( pTask );
}


//! Stops our kernel with a fatal error
void System::Kernel::die( const string& strError ) {
	g_pVM->Call<void>( "PrintError", (string("Kernel::die():") + strError).c_str() );
	Stop();
} // end Kernel::die()


//! Initialize with kernel
System::Kernel::KernelSentry::KernelSentry( Kernel* pKernel ) : m_pKernel(pKernel) {}

//! Register the kernel's globals
void System::Kernel::KernelSentry::Register() {
	assert( g_pVFS == NULL );
	g_pVFS= m_pKernel->GetVFS();
	assert( g_pResourceManager == NULL );
	g_pResourceManager= m_pKernel->GetResourceManager();
	assert( g_pVM == NULL );
	g_pVM= m_pKernel->GetVM();
} // end KernelSentry::Register()

//! Unregister the kernel's globals
System::Kernel::KernelSentry::~KernelSentry() {
	assert( g_pVM == m_pKernel->GetVM() );
	g_pVM= NULL;
	assert( g_pResourceManager == m_pKernel->GetResourceManager() );
	g_pResourceManager= NULL;
	assert( g_pVFS == m_pKernel->GetVFS() );
	g_pVFS= NULL;
} // end KernelSentry::~KernelSentry()