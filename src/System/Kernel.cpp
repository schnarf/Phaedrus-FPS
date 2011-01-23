#include "common.h"
#include "System/Kernel.h"
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
	m_pResourceManager(new World::ResourceManager),
	m_pInput(new System::Input),
	m_pVM(new VM::VM),
	m_bRunning(false) {

	m_kernelSentry.Register();
	
	m_pRender.reset( new Render::Render(this) );
	m_pWorldUpdater.reset( new World::WorldUpdater(this) );

} // end Kernel::Kernel()

//! Starts the kernel running
void System::Kernel::Start() {
	run();
} // end Kernel::Start()


//! Stops the kernel from running
void System::Kernel::Stop() {
	m_bRunning= false;
} // end Kernel::Stop()


//==================================================
//! Our kernel's main loop
//==================================================
void System::Kernel::run() {	
	assert( !m_bRunning );
	// Load the world
	m_pWorld.reset( new World::World );
	if( !m_pWorld->IsLoaded() ) die( "Could not load the world!" );

	m_bRunning= true;
	
	while( m_bRunning ) {
		// Run all tasks
		GetRender()->GetWindow()->PollEvents();
		GetInput()->Process();
		GetWorldUpdater()->Process();
		GetRender()->Process();

		// Check for the quit signal
		if( GetInput()->IsQuit() ) Stop();
	}; // end while running
	
} // end Kernel::run()


//! Stops our kernel with a fatal error
void System::Kernel::die( const string& strError ) {
//	g_pVM->Call<void>( "PrintError", (string("Kernel::die():") + strError).c_str() );
	Stop();
} // end Kernel::die()


//! Destructor, deinitializes the kernel
System::Kernel::~Kernel() {
} // end Kernel::~Kernel()


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
	assert( g_pInput == NULL );
	g_pInput= m_pKernel->GetInput();

	g_pVM->RegisterGlobals();
} // end KernelSentry::Register()

//! Unregister the kernel's globals
System::Kernel::KernelSentry::~KernelSentry() {
	assert( g_pVM == m_pKernel->GetVM() );
	g_pVM= NULL;
	assert( g_pResourceManager == m_pKernel->GetResourceManager() );
	g_pResourceManager= NULL;
	assert( g_pVFS == m_pKernel->GetVFS() );
	g_pVFS= NULL;
	assert( g_pInput == m_pKernel->GetInput() );
	g_pInput= NULL;
} // end KernelSentry::~KernelSentry()