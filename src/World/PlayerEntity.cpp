#include "common.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "World/PhysicsBase.h"
#include "Math/Vector.h"
#include "boost/python.hpp"

//==================================================
//! Private constructor because PlayerEntity is created by the VM
//==================================================
World::PlayerEntity::PlayerEntity( EntityID id ) :
	Entity(id, new PhysicsBase) {
} // end PlayerEntity::PlayerEntity()


//! Create a player with the given ID
World::EntityRef World::PlayerEntity::Create( EntityID id ) {
	using namespace boost::python;
	try {
		object main_module = import("__main__");
		object main_namespace = main_module.attr("__dict__");
		object player_class= main_namespace["PlayerEntity"];
		object newPlayer= call<object>( player_class.ptr(), id );

		EntityRef ret(newPlayer);
		ret->Think(0);

		return ret;
	} catch( const error_already_set& e ) {
		PyErr_Print();
		return EntityRef();
	}
} // end PlayerEntity::Create()


//! Returns our eye position, which is the eye offset plus our center
Math::Vector World::PlayerEntity::GetEyePosition() const {
	return m_eyeOffset + GetPhysics()->GetPosition();
} // end PlayerEntity::GetEyePosition()


//! Virtual destructor for polymorphic deletion
World::PlayerEntity::~PlayerEntity() {
} // end PlayerEntity::~PlayerEntity()


//! Updates our state, called once per frame
void World::PlayerEntityWrapper::Think( float fFrameMillis ) {
	try {
		this->get_override("think")( fFrameMillis );
	} catch( const boost::python::error_already_set& e ) {
		PyErr_Print();
	}
} // end PlayerEntityWrapper::Think()