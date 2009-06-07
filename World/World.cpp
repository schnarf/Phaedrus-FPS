#include "World/World.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "World/Level.h"
#include "Math/Vector.h"
#include "System/Timer.h"

using Math::Vector;

World::World* World::World::m_pWorld= NULL;

//==================================================
//! Constructor
//==================================================
World::World::World() {
	m_bIsLoaded= false;
}


//==================================================
//! Non-inline destructor
//==================================================
World::World::~World() {
	if( IsLoaded() ) Unload();
}


//==================================================
//! Singleton accessor
//==================================================
World::World* World::World::Get() {
	if( m_pWorld == NULL )
		m_pWorld= new World();
	
	return m_pWorld;
}

//==================================================
//! Spawn an entity at a given position
//==================================================
World::EntityRef World::World::SpawnEntity( EntityType type, const Math::Vector& pos ) {
	EntityRef pRet;

	switch( type ) {
	case ENTITY_PLAYER:
		m_entities.push_back( EntityRef(new PlayerEntity()) );
		pRet= m_entities.back();
	};
	
	// Set position
	pRet->SetPosition( pos );
	
	return pRet;
}


//==================================================
//! Load the world
//==================================================
void World::World::Load() {
	// If we are loaded, then unload
	if( IsLoaded() ) Unload();

	// Load the level
	m_pLevel= new Level("test.map");
	m_bIsLoaded= true;
	
	// Spawn things
	m_pLocalPlayer= SpawnEntity( ENTITY_PLAYER, Math::Vector(0.0f, 0.0f, 0.0f) )->ToPlayer();
	
	// Set timing
	m_oldTickCount= System::GetTickCountMillis();
}
		
		
//==================================================
//! Deallocate
//==================================================
void World::World::Unload() {
	if( !IsLoaded() ) return;
	
	delete m_pLevel;
	m_bIsLoaded= false;
}


//==================================================
//! Update positions, do physics, etc
//==================================================
void World::World::Tick( System::Ticks tickCount ) {
	// float dt= tickCount - m_oldTickCount;
	m_oldTickCount= tickCount;
}