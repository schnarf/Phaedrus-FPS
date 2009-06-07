/* World/World.h
 *
 * Contains the entire game state
 */

#ifndef _WORLD_WORLD_H_
#define _WORLD_WORLD_H_

#include "common.h"
#include "World/Entity.h"
#include "Math/Vector.h"
#include "World/WorldUpdater.h"
//#include "System/Timer.h"

namespace World {
	
	class Texture; class PlayerEntity; class Level;
	
	class World {
		friend class WorldUpdater;
	public:
		//! Load the world
		void Load();
		
		//! Deallocate
		void Unload();
		
		//! Singleton accessor
		static World* Get();
		
		//! Accessor for the local player
		inline PlayerEntity* GetLocalPlayer() const { return m_pLocalPlayer; }
		
		//! Is the world loaded?
		inline bool IsLoaded() const { return m_bIsLoaded; }
		
		//! Accessor for level
		Level* GetLevel() const { return m_pLevel; }
		
		//! Spawn an entity at a given position
		EntityRef SpawnEntity( EntityType type, const Math::Vector& pos );
		
		//! Update positions, do physics, etc
		void Tick( uint tickCount );
	private:
		//! Constructor
		World();
		//! Non-inline destructor
		~World();
		//! Singleton
		static World* m_pWorld;
		
		//! Whether the world is loaded
		bool m_bIsLoaded;
		
		//! Entities (they are all owned by this class)
		vector<EntityRef> m_entities;
		
		//! The currently loaded level
		Level* m_pLevel;
		
		PlayerEntity* m_pLocalPlayer;
		
		uint m_oldTickCount;
		
	}; // end class World
	
}; // end namespace World

#endif
