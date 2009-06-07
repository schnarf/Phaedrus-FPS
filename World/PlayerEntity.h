#ifndef _WORLD_PLAYERENTITY_H_
#define _WORLD_PLAYERENTITY_H_

#include "common.h"
#include "World/Entity.h"

namespace World {

	class PlayerEntity : public Entity {
	public:
		//! Constructor
		PlayerEntity();
		
		//! Look vector accessor
		inline Math::Vector GetLookVector() const { return m_lookVec; }
		//! Set look vector
		inline void SetLookVector( const Math::Vector& lookVec ) { m_lookVec= lookVec; }
		
		//! Eye position accessor
		inline Math::Vector GetEyePosition() const { return m_eyeOffset + GetPosition(); }
	private:
		Math::Vector m_lookVec;
		Math::Vector m_eyeOffset;
	}; // end class PlayerEntity
	
}; // end namespace World

#endif
