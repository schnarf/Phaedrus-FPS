#include "common.h"
#include "VM/VM.h"
#include "VM/Script.h"
#include "World/World.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "System/Console.h"
#include <iostream>
#include "Math/Vector.h"
#include "World/PhysicsBase.h"
#include "System/Input.h"
#include "boost/python.hpp"

using namespace boost::python;

//! Opaque VM context
struct VM::VM::VMContext {
	object mainModule,
	       mainNamespace,
		   vmModule;
	//! Initialize with main module, namespace, and our module
	VMContext( const object& mainModule_, const object& mainNamespace_, const object& vmModule_ ) :
	mainModule(mainModule_), mainNamespace(mainNamespace_), vmModule(vmModule_) {}
}; // end struct VMContext

//==================================================
//! Register a script, called by the Script constructor
//==================================================
void VM::VM::registerScript( Script* pScript ) {
	// Just blindly execute the script's contents
	Execute( pScript->GetCode() );
}


//==================================================
//! Load a script from disk
//==================================================
Error VM::VM::LoadScript( const string& strFilename ) {
	m_scripts.push_back( shared_ptr<Script>(new Script(strFilename, this)) );
	
	return ERROR_OK;
}

BOOST_PYTHON_MODULE(phaedrus) {
	def("print", System::Console::Print);
	def("print_error", System::Console::PrintError);
	def("print_uint", System::Console::PrintUint);
	def("print_float", System::Console::PrintFloat);
	def("print_vector", System::Console::PrintVector);

	class_<Math::Vector>("Vector")
		.def(init<float, float, float>())
		.def_readwrite("x", &Math::Vector::x)
		.def_readwrite("y", &Math::Vector::y)
		.def_readwrite("z", &Math::Vector::z)
		.def("length", &Math::Vector::Length)
		.def("normalize", &Math::Vector::Normalize)
		.def(self + self)
		.def(self * self)
		.def(self * float())
		.def(self / float());

	class_<System::Input>("Input", no_init)
		.def("is_key_down", &System::Input::IsKeyDown)
		.def("is_quit", &System::Input::IsQuit)
	;
	enum_<System::InputKeys>("InputKeys")
		.value("INPUT_LEFT", System::INPUT_LEFT)
		.value("INPUT_RIGHT", System::INPUT_RIGHT)
		.value("INPUT_UP", System::INPUT_UP)
		.value("INPUT_DOWN", System::INPUT_DOWN)
		.value("INPUT_W", System::INPUT_W)
		.value("INPUT_A", System::INPUT_A)
		.value("INPUT_S", System::INPUT_S)
		.value("INPUT_D", System::INPUT_D)
		.value("INPUT_SHIFT", System::INPUT_SHIFT)
		.value("INPUT_CTRL", System::INPUT_CTRL)
		.value("NUM_INPUT_KEYS", System::NUM_INPUT_KEYS)
	;

	class_<World::World>("World")
		.def("spawn_entity", &World::World::SpawnEntity)
		.def("get_local_player_entity", &World::World::GetLocalPlayerEntity, return_value_policy<reference_existing_object>())
		.def("get_entity", &World::World::GetEntity, return_value_policy<reference_existing_object>());

	class_<World::PhysicsBase>("PhysicsBase")
		.add_property("position", make_function(&World::PhysicsBase::GetPosition, return_value_policy<reference_existing_object>()), &World::PhysicsBase::SetPosition)
		.add_property("velocity", make_function(&World::PhysicsBase::GetVelocity, return_value_policy<reference_existing_object>()), &World::PhysicsBase::SetVelocity)
		.add_property("acceleration", make_function(&World::PhysicsBase::GetAcceleration, return_value_policy<reference_existing_object>()), &World::PhysicsBase::SetAcceleration)
		.add_property("rotation", make_function(&World::PhysicsBase::GetRotation, return_value_policy<reference_existing_object>()), &World::PhysicsBase::SetRotation)
		.add_property("angular_velocity", make_function(&World::PhysicsBase::GetAngularVelocity, return_value_policy<reference_existing_object>()), &World::PhysicsBase::SetAngularVelocity)
		.add_property("angular_acceleration", make_function(&World::PhysicsBase::GetAngularAcceleration, return_value_policy<reference_existing_object>()), &World::PhysicsBase::SetAngularAcceleration)
	;

	class_<World::Entity, boost::noncopyable>("Entity", no_init)
		.def("think", pure_virtual(&World::Entity::Think))
		.def("get_id", &World::Entity::GetID)
		.add_property("physics", make_function((World::PhysicsBase*(World::Entity::*)(void))&World::Entity::GetPhysics, return_value_policy<reference_existing_object>()))
		;
	enum_<World::EntityType>("EntityType")
		.value("ENTITY_PLAYER", World::ENTITY_PLAYER)
	;
	class_<World::PlayerEntityWrapper, bases<World::Entity>, boost::noncopyable >("PlayerEntityBase", init<World::EntityID>())
		.def("create", &World::PlayerEntity::Create)
		.add_property("look_vector", make_function(&World::PlayerEntity::GetLookVector, return_value_policy<reference_existing_object>()), &World::PlayerEntity::SetLookVector)
		.add_property("eye_offset", make_function(&World::PlayerEntity::GetEyeOffset, return_value_policy<reference_existing_object>()), &World::PlayerEntity::SetEyeOffset)
		.add_property("eye_position", &World::PlayerEntity::GetEyePosition)
	;

}

//==================================================
//! Initialize
//==================================================
VM::VM::VM() {
	// Initialize Python
	try {
		PyImport_AppendInittab( "phaedrus", &initphaedrus );
		Py_Initialize();

		object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object main_namespace= main_module.attr("__dict__");
		object phaedrus_module((handle<>(PyImport_ImportModule("phaedrus"))));
		main_namespace["phaedrus"]= phaedrus_module;

		m_pContext.reset( new VMContext(main_module, main_namespace, phaedrus_module) );
	} catch( const error_already_set& e ) {
		PyErr_Print();
	}
	
}


//==================================================
//! Execute some raw code
//==================================================
void VM::VM::Execute( const string& code ) {

	try {
		handle<> ignored( PyRun_String(code.c_str(), Py_file_input, m_pContext->mainNamespace.ptr(), m_pContext->mainNamespace.ptr()) );
	} catch( const error_already_set& e ) {
		PyErr_Print();
	}

}


//==================================================
//! Set the current world
//==================================================
void VM::VM::SetWorld( World::World* pWorld ) {
	m_pContext->mainNamespace["g_world"]= ptr( pWorld );
}


//! Registers engine globals in the VM
void VM::VM::RegisterGlobals() {
	assert( g_pInput );
	m_pContext->mainNamespace["g_input"]= ptr( g_pInput );
} // end VM::RegisterGlobals()

//==================================================
//! Deinitialize
//==================================================
VM::VM::~VM() {
	// Deinitialize lua
	//lua_close( m_pLuaState );

	// Don't deinitialize Python -- the boost Python docs say not to do this
	//Py_Finalize();

}