/* World/WorldUpdater.h
 *
 * Task which is responsible for updating the world state.
 * Responds to input, does physics, etc
 */

#ifndef _WORLD_WORLDUPDATER_H_
#define _WORLD_WORLDUPDATER_H_

#include "System/Task.h"
namespace System { class Kernel; }

namespace World {

	class WorldUpdater : public System::Task {
	public:
		//! Initialize the task
		WorldUpdater( System::Kernel* pKernel );
		
	protected:
		//! Called whenever the thread is started
		void init();
		//! Called when the thread is stopped
		void deinit();
		//! Our main loop
		void process();
		//! Our message processing function
		void processMessages();
		
	private:
		//! The timestep when we last updates
		uint64 m_uLastTimestep;
		
		//! Do physics
		void doPhysics();
	}; // end class WorldUpdater

}; // end namespace World

#endif
