/* World/ParticleSystem.h
 *
 * Emits particles with physics
 */

#pragma once

#include "Math/Vector.h"

namespace World {

	class ParticleSystem {
	public:
		//! Initialize the particles
		ParticleSystem();
		
		//! De-allocate
		~ParticleSystem();
		
		//! Update the physics
		void PhysicsTick( uint uTimestep );
		
		//! Render the particle system (rendering thread)
		void Render();
	private:
		struct ParticleInfo {
			Math::Vector pos;
			Math::Vector vel;
			float r, g, b, life;
		}; // end struct ParticleInfo
		
		//! The particles
		vector<ParticleInfo> m_particles;
	}; // end class ParticleSystem

} // end namespace World
