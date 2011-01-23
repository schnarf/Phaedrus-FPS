#include "common.h"
#include "World/WorldUpdater.h"
#include "World/World.h"
#include "System/Timer.h"
#include "Math/Vector.h"
#include "System/Kernel.h"
#include "Render/Render.h"
#include "World/PhysicsBase.h"

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
	
	float fTimesliceMillis= (float)uDt;
	
	// For each entity, update velocity and position
	for( vector<EntityRef>::iterator it= pWorld->m_entities.begin(); it != pWorld->m_entities.end(); ++it ) {
		Entity* pEntity= (*it).get();

		// Update physics if applicable
		PhysicsBase* pPhysics= pEntity->GetPhysics();
		if( pPhysics ) pPhysics->Update( fTimesliceMillis );

		// Update the entity's state
		pEntity->Think( fTimesliceMillis );
	} // end for entity
}


//==================================================
//! Do physics
//==================================================
void World::WorldUpdater::doPhysics() {
}