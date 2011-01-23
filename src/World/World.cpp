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
#include "World/PhysicsBase.h"

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
		//g_pVM->Call<void>( "PrintError", "Encountered a file IO error trying to load the level." );
		return;
	}

	// Load and call the startup script, this can throw
	try {
		g_pVM->LoadScript( "WorldStartup.py" );
	} catch( const FileIOException& e ) {
		// If we failed to load the world startup script, just print a message
		//g_pVM->Call<void>( "PrintError", "Encountered a file IO error trying to load the world startup script" );
		g_pVM->Execute( "PrintError( 'Encountered a file IO error trying to load the world startup script' )\n" );
		return;
	}

	// Spawn things
	m_pLocalPlayer= static_cast<PlayerEntity*>(SpawnEntity(ENTITY_PLAYER).get());
	m_pLocalPlayer->GetPhysics()->SetPosition( Math::Vector(0, 0, 0) );
	
	// Set timing
	m_oldTickCount= System::GetTickCountMillis();

	m_bIsLoaded= true;
	
	// Register with VM
	g_pVM->SetWorld( this );

	g_pVM->Execute( "WorldStartup()\n" );

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
//! Spawn an entity
//==================================================
World::EntityRef World::World::SpawnEntity( EntityType type ) {
	EntityRef pRet;

	EntityID id= m_entities.size();
	
	switch( type ) {
	case ENTITY_PLAYER: {
		m_entities.push_back( PlayerEntity::Create(id) );
		pRet= m_entities.back();
		break;
	} // end case player

	default: assert(false);
	} // end switch type
	
	return pRet;
} // end World::GetEntity()

//==================================================
//! Get an entity pointer by ID
//==================================================
World::Entity* World::World::GetEntity( EntityID id ) {
	if( id >= m_entities.size() ) return NULL;
	
	return m_entities[id].get();
} // end World::GetEntity()


//==================================================
//! Update positions, do physics, etc
//==================================================
void World::World::Tick( uint64 tickCount ) {
	// float dt= tickCount - m_oldTickCount;
	m_oldTickCount= tickCount;
}