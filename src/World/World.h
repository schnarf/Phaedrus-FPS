/* World/World.h
 *
 * Contains the entire game state
 */

#pragma once

#include "World/Entity.h"
#include "Math/Vector.h"
#include "World/WorldUpdater.h"

namespace World {
	
	class Texture; class PlayerEntity; class Level;
	
	class World {
		friend class WorldUpdater;
	public:
		//! Constructor
		World();
		//! Non-inline destructor
		~World();
		
		//! Accessor for the local player
		inline PlayerEntity* GetLocalPlayerEntity() const { return m_pLocalPlayer; }
		
		//! Is the world loaded?
		inline bool IsLoaded() const { return m_bIsLoaded; }
		
		//! Accessor for level
		Level* GetLevel() const { return m_pLevel.get(); }
		
		//! Spawn an entity at a given position
		EntityRef SpawnEntity( EntityType type, const Math::Vector& pos );
		
		//! Update positions, do physics, etc
		void Tick( uint64 tickCount );
		
		//! Get an entity POINTER by ID (not reference)
		Entity* GetEntity( EntityID id ) const;

	private:
		//! Whether the world is loaded
		bool m_bIsLoaded;
		
		//! Entities (they are all owned by this class)
		vector<EntityRef> m_entities;
		
		//! The currently loaded level
		shared_ptr<Level> m_pLevel;
		
		PlayerEntity* m_pLocalPlayer;
		
		uint64 m_oldTickCount;
		
	}; // end class World
	
} // end namespace World
