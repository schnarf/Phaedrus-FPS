/* World/PlayerEntity.h
 *
 * Implementation of a player in the world
 */
#pragma once

#include "World/Entity.h"
#include "boost/python.hpp"

namespace World {

	class PlayerEntity : public Entity {
	public:
		//! Create a player with the given ID
		static EntityRef Create( EntityID id );

		//! Virtual destructor for polymorphic deletion
		virtual ~PlayerEntity();

		//! Updates our state, called once per frame
		virtual void Think( float fFrameMillis )= 0;

		//! Look vector accessor
		inline const Math::Vector& GetLookVector() const { return m_lookVec; }
		//! Set look vector
		inline void SetLookVector( const Math::Vector& lookVec ) { m_lookVec= lookVec; }
		
		//! Get our eye offset from our center
		inline const Math::Vector& GetEyeOffset() const { return m_eyeOffset; }
		//! Set our eye offset from our center
		inline void SetEyeOffset( const Math::Vector& eyeOffset ) { m_eyeOffset= eyeOffset; }
		//! Returns our eye position, which is the eye offset plus our center
		Math::Vector GetEyePosition() const;
	protected:
		//! Private constructor because PlayerEntity is created by the VM
		PlayerEntity( EntityID id );
	private:
		Math::Vector m_lookVec;
		Math::Vector m_eyeOffset;
	}; // end class PlayerEntity

	//! VM wrapper for PlayerEntity
	class PlayerEntityWrapper : public PlayerEntity, public boost::python::wrapper<PlayerEntity> {
	public:
		//! Construct with our ID
		PlayerEntityWrapper( EntityID id ) : PlayerEntity(id) {}
		//! Virtual destructor for polymorphic deletion
		virtual ~PlayerEntityWrapper() {}
		
		//! Updates our state, called once per frame
		virtual void Think( float fFrameMillis );
	}; // end class PlayerEntityWrapper
		
} // end namespace World
