#include "common.h"
#include "World/WorldUpdater.h"
#include "World/World.h"
#include "System/Timer.h"
#include "Math/Vector.h"
#include "System/Kernel.h"
#include "Render/Render.h"

using Math::Vector;

//==================================================
//! Initialize the task
//==================================================
World::WorldUpdater::WorldUpdater( System::Kernel* pKernel ) : System::Task( "World Updater", pKernel, false ) {
}


//==================================================
//! Called whenever the thread is started
//==================================================
void World::WorldUpdater::init() {
	// Initialize the timestep
	m_uLastTimestep= System::GetTickCountMillis();
}

//==================================================
//! Called when the thread is stopped
//==================================================
void World::WorldUpdater::deinit() {
}


//==================================================
//! Our main loop
//==================================================
void World::WorldUpdater::process() {
	World* pWorld= GetKernel()->GetWorld();

	// If the world is not loaded, do nothing
	if( !pWorld->IsLoaded() ) return;
	
	// Calculate timestep
	uint uDt= GetKernel()->GetTaskRender()->GetLastTimeslice();
	// If our timestep is zero, we do nothing for now
	if( uDt == 0 ) return;
	
	float dt= (float)uDt;
	
	// For each entity, update velocity and position
	for( vector<EntityRef>::iterator it= pWorld->m_entities.begin(); it != pWorld->m_entities.end(); ++it ) {
		// Check whether we do physics
		if( !(*it)->IsFlag(ENTITY_FLAG_PHYSICS) ) continue;
	
		// Integrate position
		Vector acc= (*it)->GetAcceleration();
		Vector vel= (*it)->GetVelocity();
		Vector pos= (*it)->GetPosition();
		
		vel+= acc * dt;
		pos+= vel * dt;
		(*it)->SetVelocity( vel );
		(*it)->SetPosition( pos );
		
		// Integrate rotation
		Vector rot= (*it)->GetRotation();
		Vector angvel= (*it)->GetAngularVelocity();
		Vector angacc= (*it)->GetAngularAcceleration();
		
		angvel+= angacc * dt;
		rot+= angvel * dt;
		(*it)->SetAngularVelocity( angvel );
		(*it)->SetRotation( rot );
	}
}


//==================================================
//! Our message processing function
//==================================================
void World::WorldUpdater::processMessages() {
}


//==================================================
//! Do physics
//==================================================
void World::WorldUpdater::doPhysics() {
}