#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "Math/Vector.h"

//==================================================
//! Constructor
//==================================================
World::PlayerEntity::PlayerEntity( EntityID id ) : Entity(ENTITY_PLAYER, id) {
}