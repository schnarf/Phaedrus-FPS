#include "common.h"
#include "World/WorldUpdater.h"
#include "World/World.h"
#include "System/Timer.h"
#include "Math/Vector.h"
#include "System/Kernel.h"
#include "Render/Render.h"

using Math::Vector;

//==================================================
//! Initialize
//==================================================
World::WorldUpdater::WorldUpdater( System::Kernel* pKernel ) :
	m_pKernel(pKernel),
	m_uLastTimestep(System::GetTickCountMillis()) {
} // end WorldUpdater::WorldUpdater()


//==================================================
//! Update the world's state
//==================================================
void World::WorldUpdater::Process() {
	World* pWorld= m_pKernel->GetWorld();

	// If the world is not loaded, do nothing
	if( !pWorld->IsLoaded() ) return;
	
	// Calculate timestep
	uint64 uDt= m_pKernel->GetRender()->GetLastTimeslice();
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
//! Do physics
//==================================================
void World::WorldUpdater::doPhysics() {
}