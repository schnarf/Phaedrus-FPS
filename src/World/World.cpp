#include "common.h"
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
World::World::World() :
	m_bIsLoaded(false) {

	// Load the level, this can throw
	try {
		m_pLevel.reset( new Level("test.map") );
	} catch( const FileIOException& e ) {
		// If we failed to load the level, log the error and exit
		g_pVM->Call<void>( "PrintError", "Encountered a file IO error trying to load the level." );
		return;
	}
	// Spawn things
	m_pLocalPlayer= SpawnEntity( ENTITY_PLAYER, Math::Vector(0.0f, 0.0f, 0.0f) )->ToPlayer();
	
	// Set timing
	m_oldTickCount= System::GetTickCountMillis();

	m_bIsLoaded= true;
	
	// Register with VM
	g_pVM->SetWorld( this );
	
	// Load and call the startup script, this can throw
	try {
		g_pVM->LoadScript( "WorldStartup.lua" );
	} catch( const FileIOException& e ) {
		// If we failed to load the world startup script, just print a message
		g_pVM->Call<void>( "PrintError", "Encountered a file IO error trying to load the world startup script" );
		return;
	}
	
	g_pVM->Call<void>( "WorldStartup" );
}


//==================================================
//! Non-inline destructor
//==================================================
World::World::~World() {
	if( !IsLoaded() ) return;
	
	g_pVM->SetWorld( NULL );

	m_bIsLoaded= false;
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
//! Update positions, do physics, etc
//==================================================
void World::World::Tick( uint64 tickCount ) {
	// float dt= tickCount - m_oldTickCount;
	m_oldTickCount= tickCount;
}