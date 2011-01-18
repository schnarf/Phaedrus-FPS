/* World/WorldUpdater.h
 *
 * Task which is responsible for updating the world state.
 * Responds to input, does physics, etc
 */

#pragma once

namespace System { class Kernel; }

namespace World {

	class WorldUpdater {
	public:
		//! Initialize
		WorldUpdater( System::Kernel* pKernel );

		//! Update the world's state
		void Process();
		
	private:
		System::Kernel* m_pKernel;			//!< Pointer to our kernel

		//! The timestep when we last updated
		uint64 m_uLastTimestep;
		
		//! Do physics
		void doPhysics();
	}; // end class WorldUpdater

} // end namespace World
