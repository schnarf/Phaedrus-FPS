#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "Math/Vector.h"

//==================================================
//! Constructor
//==================================================
World::PlayerEntity::PlayerEntity() : Entity(ENTITY_PLAYER) {
	m_lookVec= Math::Vector( 0.0f, 0.0f, -1.0f );
	SetVelocity( Math::Vector(0.0f, 0.0f, -0.001f) );
}