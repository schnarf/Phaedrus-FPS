#include "common.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"

namespace {
	const uint DEFAULT_FLAGS= World::ENTITY_FLAG_VISIBLE
						   | World::ENTITY_FLAG_COLLIDABLE
						   | World::ENTITY_FLAG_PHYSICS;
}; // end anonymous namespace

//==================================================
//! Entity constructor
//==================================================
World::Entity::Entity( World::EntityType type, EntityID id ) :
	m_type(type),
	m_id(id),
	m_flags(DEFAULT_FLAGS) {
}

//==================================================
//! Inherited class cast to player
//==================================================
World::PlayerEntity* World::Entity::ToPlayer() {
	assert( m_type == ENTITY_PLAYER );
	if( m_type != ENTITY_PLAYER ) return NULL;
	
	return reinterpret_cast<World::PlayerEntity*>(this);
}
