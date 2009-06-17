#include "World/World.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "World/Level.h"
#include "Math/Vector.h"
#include "System/Timer.h"
#include "VM/VM.h"
#include <iostream>

using Math::Vector;


//==================================================
//! Constructor
//==================================================
World::World::World( VM::VM* pVM ) :
	m_pVM( pVM ) {
	m_bIsLoaded= false;
	
	// Register with VM
	m_pVM->SetWorld( this );
	/*pVM->Register( "GetLocalPlayerEntity", GetLocalPlayerEntity_VM );
	pVM->Register( "GetLocalPlayerID", GetLocalPlayerID );
	pVM->Register( "GetEntity", GetEntity );
	pVM->Register( "SpawnEntity", SpawnEntity_VM );*/
	
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
	//m_pVM->LoadScript( "WorldStartup.lua" );
	
	m_pVM->Execute( "function WorldStartup()\n"
	"Print( \"World started up!\" );\n"
	"localplayer= World:GetLocalPlayerEntity();\n"
	"localplayer.LookVector= Vector(0.0, 0.0, -1.0);\n"
	"localplayer.Velocity= Vector(0.0, 0.0, -0.001);\n"
	"return 1;\n"
	"end\n" );
	m_pVM->Call<void>("WorldStartup");
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