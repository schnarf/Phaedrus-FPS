#include "common.h"
#include "System/Task.h"
#include "System/Kernel.h"

System::Task::Task( string strName, bool bOwnThread ) :
	m_bOwnThread( bOwnThread ),
	m_strName( strName ),
	m_pThread( NULL ),
	m_bRunning( false ) {
	// Register our task
	System::Kernel::Get()->addTask( this );
}


System::Task::~Task() {
}


//==================================================
//! Start the task
//==================================================
void System::Task::Start() {
	m_bRunning= true;
	
	if( m_bOwnThread ) {
		m_pThread= new boost::thread( boost::bind(&System::Task::mainLoop, this) );
		m_idThread= m_pThread->get_id();
	} else {
		m_pThread= NULL;
		m_idThread= boost::this_thread::get_id();
		init();
	}
}


//==================================================
//! Stop the task
//==================================================
void System::Task::Stop() {
	m_bRunning= false;
	
	if( m_bOwnThread )
		delete m_pThread;
	else
		deinit();
}


//==================================================
//! Run the task (process messages and process)
//==================================================
void System::Task::Run() {
	if( m_bOwnThread ) {
		processMessages();
		
		m_pThread= new boost::thread( boost::bind(&System::Task::process, this) );
		m_idThread= m_pThread->get_id();

	} else {
		processMessages();
		process();
	}
}


//==================================================
//! Post a message to the task
//==================================================
void System::Task::PostMessage( uint eMsg ) {
	m_msgQueue.push_back( eMsg );
}


//==================================================
//! Our wrapper main loop
//==================================================
void System::Task::mainLoop() {
	init();

	while( m_bRunning ) {
		processMessages();
		process();
	};
	
	deinit();
}