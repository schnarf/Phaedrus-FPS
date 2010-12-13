/* World/Entity.h
 *
 * Base class for all things
 */

#ifndef _WORLD_ENTITY_H_
#define _WORLD_ENTITY_H_

#include "common.h"
#include "Math/Vector.h"
#include "World/Mesh.h"
#include <iostream>
namespace World {

	typedef unsigned int EntityID;

	enum EntityType {
		ENTITY_STATIC,
		ENTITY_PLAYER,
		NUM_ENTITY_TYPES
	}; // end enum EntityType
	
	enum EntityFlag {
		ENTITY_FLAG_VISIBLE= 1<<0,			// Do we render the entity
		ENTITY_FLAG_COLLIDABLE= 1<<1,		// Does the entity collide with other entities
		ENTITY_FLAG_PHYSICS= 1<<2			// Do we calculate physics for this entity
	}; // end enum EntityFlags
	
	enum EntityMessage {
		ENTITY_MSG_SPAWN,
		NUM_ENTITY_MESSAGES
	}; // end enum EntityMessage
	
	class PlayerEntity;

	class Entity {

	public:
		//! Entity constructor
		Entity( EntityType type, EntityID id );
	
		//! Position accessor
		Math::Vector GetPosition() const;
		//! Velocity accessor
		Math::Vector GetVelocity() const;
		//! Acceleration accessor
		Math::Vector GetAcceleration() const;
				
		//! Set position
		void SetPosition( const Math::Vector& pos );
		//! Set velocity
		void SetVelocity( const Math::Vector& vel );
		//! Set acceleration
		void SetAcceleration( const Math::Vector& acc );
		
		//! Rotation accessor
		Math::Vector GetRotation() const;
		//! Angular velocity accessor
		Math::Vector GetAngularVelocity() const;
		//! Angular acceleration accessor
		Math::Vector GetAngularAcceleration() const;
		
		//! Set rotation
		void SetRotation( const Math::Vector& rot );
		//! Set angular velocity
		void SetAngularVelocity( const Math::Vector& angvel );
		//! Set angular acceleration
		void SetAngularAcceleration( const Math::Vector& angacc );
		
		//! Get entity type
		EntityType GetType() const;
		
		//! Check if a flag is set
		bool IsFlag( EntityFlag flag ) const;
		//! Set a flag
		void SetFlag( EntityFlag flag );
		
		//! Inherited class cast to player
		PlayerEntity* ToPlayer();
		
		EntityID GetID() const { return m_id; }
	protected:
		//! Position, velocity, acceleration
		Math::Vector m_pos, m_vel, m_acc;
		
		//! Rotation, angular velocity, angular acceleration
		Math::Vector m_rot, m_angvel, m_angacc;
		
		//! The type of entity
		EntityType m_type;
		
		//! The id assigned by World
		EntityID m_id;
		
		//! Our flags
		uint m_flags;
		
		//! The model for this entity, NULL if no model
		MeshRef m_pMesh;
	}; // end class Entity
	
	typedef shared_ptr<Entity> EntityRef;
	
}; // end namespace World


//! Position accessor
inline Math::Vector World::Entity::GetPosition() const { return m_pos; }
//! Velocity accessor
inline Math::Vector World::Entity::GetVelocity() const { return m_vel; }
//! Acceleration accessor
inline Math::Vector World::Entity::GetAcceleration() const { return m_acc; }

//! Set position
inline void World::Entity::SetPosition( const Math::Vector& pos ) { m_pos= pos; }
//! Set velocity
inline void World::Entity::SetVelocity( const Math::Vector& vel ) { m_vel= vel; }
//! Set acceleration
inline void World::Entity::SetAcceleration( const Math::Vector& acc ) { m_acc= acc; }

//! Rotation accessor
inline Math::Vector World::Entity::GetRotation() const { return m_rot; }
//! Angular velocity accessor
inline Math::Vector World::Entity::GetAngularVelocity() const { return m_angvel; }
//! Angular acceleration accessor
inline Math::Vector World::Entity::GetAngularAcceleration() const { return m_angacc; }

//! Set rotation
inline void World::Entity::SetRotation( const Math::Vector& rot ) { m_rot= rot; }
//! Set angular velocity
inline void World::Entity::SetAngularVelocity( const Math::Vector& angvel ) { m_angvel= angvel; }
//! Set angular acceleration
inline void World::Entity::SetAngularAcceleration( const Math::Vector& angacc ) { m_angacc= angacc; }

//! Get entity type
inline World::EntityType World::Entity::GetType() const { return m_type; }

//! Check if a flag is set
inline bool World::Entity::IsFlag( EntityFlag flag ) const { return m_flags & flag; }
//! Set a flag
inline void World::Entity::SetFlag( EntityFlag flag ) { m_flags|= flag; }
#endif
