#include "common.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "World/PhysicsBase.h"

//==================================================
//! Entity base class constructor, initialize with components
//==================================================
World::Entity::Entity( EntityID id, PhysicsBase* pPhysics ) :
	m_id(id),
	m_pPhysics(pPhysics) {
} // end Entity::Entity()


//! Virtual destructor for polymorphic deletion
World::Entity::~Entity() {
} // end Entity::~Entity()