/* World/PhysicsBase.h
 *
 * Base class for handling position and motion
 */
#pragma once

#include "Math/Vector.h"

namespace World {
	
	class PhysicsBase {
	public:
		//! Initialize
		PhysicsBase();
		//! Virtual destructor for polymorphic deletion
		virtual ~PhysicsBase();

		//! Updates our state, for one timeslice
		virtual void Update( float fTimesliceMillis );

		//! Sets our position
		void SetPosition( const Math::Vector& pos ) { m_pos= pos; }
		//! Gets our position
		const Math::Vector& GetPosition() const { return m_pos; }

		//! Sets our velocity
		void SetVelocity( const Math::Vector& vel ) { m_vel= vel; }
		//! Gets our velocity
		const Math::Vector& GetVelocity() const { return m_vel; }

		//! Sets our acceleration
		void SetAcceleration( const Math::Vector& acc ) { m_acc= acc; }
		//! Gets our acceleration
		const Math::Vector& GetAcceleration() const { return m_acc; }

		//! Sets our rotation
		void SetRotation( const Math::Vector& rot ) { m_rot= rot; }
		//! Gets our rotation
		const Math::Vector& GetRotation() const { return m_rot; }

		//! Sets our angular velocity
		void SetAngularVelocity( const Math::Vector& angvel ) { m_angvel= angvel; }
		//! Gets our angular velocity
		const Math::Vector& GetAngularVelocity() const { return m_angvel; }

		//! Sets our angular acceleration
		void SetAngularAcceleration( const Math::Vector& angacc ) { m_angacc= angacc; }
		//! Gets our angular acceleration
		const Math::Vector& GetAngularAcceleration() const { return m_angacc; }
	private:
		Math::Vector m_pos,		//!< Position
		             m_vel,		//!< Velocity
					 m_acc,		//!< Acceleration
					 m_rot,		//!< Rotation vector
					 m_angvel,	//!< Angular velocity
					 m_angacc;	//!< Angular acceleration
	}; // end class PhysicsBase

} // end namespace World