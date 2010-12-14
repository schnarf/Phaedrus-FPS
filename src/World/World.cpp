#include "World/World.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "World/Level.h"
#include "World/ResourceManager.h"
#include "Math/Vector.h"
#include "System/Timer.h"
#include "System/VFS.h"
#include "VM/VM.h"
#include <iostream>

using Math::Vector;


//==================================================
//! Constructor
//==================================================
World::World::World() {
	m_bIsLoaded= false;
	
	// Register with VM
	g_VM.SetWorld( this );
}


//==================================================
//! Non-inline destructor
//==================================================
World::World::~World() {
	if( IsLoaded() ) Unload();
}


//==================================================
//! Spawn an entity at a given position
//==================================================
World::EntityRef World::World::SpawnEntity( EntityType type, const Math::Vector& pos ) {
	EntityRef pRet;

	EntityID id= m_entities.size();
	
	switch( type ) {
	case ENTITY_PLAYER:
		m_entities.push_back( EntityRef(new PlayerEntity(id)) );
		pRet= m_entities.back();
	};
	
	// Set position
	pRet->SetPosition( pos );
	
	return pRet;
}

//==================================================
//! Get an entity pointer by ID
//==================================================
World::Entity* World::World::GetEntity( EntityID id ) const {
	if( id >= m_entities.size() ) return NULL;
	
	return m_entities[id].get();
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
	
	// Call the startup script;
	g_VM.LoadScript( "WorldStartup.lua" );
	g_VM.Call<void>("WorldStartup");
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