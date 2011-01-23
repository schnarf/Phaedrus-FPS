#include "common.h"
#include "World/PhysicsBase.h"

//! Initialize
World::PhysicsBase::PhysicsBase() {
} // end PhysicsBase::PhysicsBase()


//! Updates our state, for one timeslice
void World::PhysicsBase::Update( float fTimesliceMillis ) {
	// Integrate position	
	SetVelocity( GetVelocity() + GetAcceleration()*fTimesliceMillis );
	SetPosition( GetPosition() + GetVelocity()*fTimesliceMillis );
		
	// Integrate rotation
	SetAngularVelocity( GetAngularVelocity() + GetAngularAcceleration()*fTimesliceMillis );
	SetRotation( GetRotation() + GetAngularVelocity()*fTimesliceMillis );
} // end PhysicsBase::Update()


//! Virtual destructor for polymorphic deletion
World::PhysicsBase::~PhysicsBase() {
} // end PhysicsBase::~PhysicsBase()