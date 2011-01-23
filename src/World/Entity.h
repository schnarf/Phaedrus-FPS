/* World/Entity.h
 *
 * Base class for all things
 */
#pragma once

#include "Math/Vector.h"
#include "World/Mesh.h"
#include "VM/VM.h"

namespace World {

	typedef unsigned int EntityID;
	
	enum EntityMessage {
		ENTITY_MSG_SPAWN,
		NUM_ENTITY_MESSAGES
	}; // end enum EntityMessage

	enum EntityType {
		ENTITY_PLAYER,
		NUM_ENTITY_TYPES
	}; // end enum EntityType
	
	class PhysicsBase;

	class Entity {

	public:
		//! Entity base class constructor, initialize with components
		Entity( EntityID id, PhysicsBase* pPhysics= NULL );
		//! Virtual destructor for polymorphic deletion
		virtual ~Entity();

		//! Updates our state, called once per frame
		virtual void Think( float fFrameMillis )= 0;

		//! Gets our unique ID
		EntityID GetID() const { return m_id; }

		//! Gets our physics implementation, can be NULL
		PhysicsBase* GetPhysics() { return m_pPhysics.get(); }
		//! Gets our physics implementation, can be NULL
		const PhysicsBase* GetPhysics() const { return m_pPhysics.get(); }
	protected:				
		//! The id assigned by World
		EntityID m_id;

		//! Our physics implementation, can be NULL
		scoped_ptr<PhysicsBase> m_pPhysics;
		
		//! The model for this entity, NULL if no model
		MeshRef m_pMesh;
	}; // end class Entity
	
	typedef VM::VMRef<Entity> EntityRef;

} // end namespace World
