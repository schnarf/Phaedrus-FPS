#include "common.h"
#include "VM/VM.h"
#include "VM/Script.h"
#include "luabind/luabind.hpp"
#include "luabind/operator.hpp"
#include "World/World.h"
#include "World/Entity.h"
#include "World/PlayerEntity.h"
#include "System/Console.h"
#include <iostream>
#include "Math/Vector.h"

using namespace luabind;

namespace {

	int add_file_and_line( lua_State* L ) {
	   lua_Debug d;
	   lua_getstack( L, 1, &d );
	   lua_getinfo( L, "Sln", &d );
	   std::string err = lua_tostring( L, -1 );
	   lua_pop(L, 1);
	   std::stringstream msg;
	   msg << d.short_src << ":" << d.currentline;

	   if( d.name != 0 ) {
		  msg << "(" << d.namewhat << " " << d.name << ")";
	   }
	   msg << " " << err;
	   lua_pushstring( L, msg.str().c_str() );
	   return 1;
	}

}; // end anonymous namespace

//==================================================
//! Register a script, called by the Script constructor
//==================================================
void VM::VM::registerScript( Script* pScript ) {
	// Just blindly execute the script's contents
	
	try {
		Execute( pScript->GetCode() );
	} catch(luabind::error& e ) {
		std::cout << e.what() << std::endl;
		string strError= lua_tostring( e.state(), -1 );
		std::cout << strError << std::endl;
		throw;
	}
}


//==================================================
//! Load a script from disk
//==================================================
Error VM::VM::LoadScript( const string& strFilename ) {
	m_scripts.push_back( shared_ptr<Script>(new Script(strFilename, this)) );
	
	return ERROR_OK;
}


//==================================================
//! Initialize
//==================================================
VM::VM::VM() {
	// Initialize lua and luabind
	m_pLuaState= lua_open();
	open( m_pLuaState );
	
	// Set up error handling
	set_pcall_callback( add_file_and_line );
	
	// Bind System::Console functions
	module( m_pLuaState ) [
		def("Print", System::Console::Print),
		def("PrintError", System::Console::PrintError),
		def("PrintUint", System::Console::PrintUint),
		def("PrintFloat", System::Console::PrintFloat),
		def("PrintVector", System::Console::PrintVector)
	];


	// Bind Math::Vector
	module( m_pLuaState ) [
		class_<Math::Vector>("Vector")
			.def(constructor<float, float, float>())
			.def_readwrite("x", &Math::Vector::x)
			.def_readwrite("y", &Math::Vector::y)
			.def_readwrite("z", &Math::Vector::z)
			.def("Length", &Math::Vector::Length)
			.def("Normalize", &Math::Vector::Normalize)
			.def(const_self + const_self)
			.def(const_self * const_self)
			.def(const_self * float())
			.def(const_self / float())
	];
		
				
	// Bind World::World
	module( m_pLuaState ) [
		class_<World::World>("World")
			.def("SpawnEntity", &World::World::SpawnEntity)
			.def("GetLocalPlayerEntity", &World::World::GetLocalPlayerEntity)
			.def("GetEntity", &World::World::GetEntity)
	];
	
	// Bind Entity
	module( m_pLuaState ) [
		class_<World::Entity>("Entity")
			.def("GetID", &World::Entity::GetID)
			.def("GetType", &World::Entity::GetType)
			.property("Position", &World::Entity::GetPosition, &World::Entity::SetPosition)
			.property("Velocity", &World::Entity::GetVelocity, &World::Entity::SetVelocity)
			.property("Acceleration", &World::Entity::GetAcceleration, &World::Entity::SetAcceleration)
			.property("Rotation", &World::Entity::GetRotation, &World::Entity::SetRotation)
			.property("AngularVelocity", &World::Entity::GetAngularVelocity, &World::Entity::SetAngularVelocity)
			.property("AngularAcceleration", &World::Entity::GetAngularAcceleration, &World::Entity::SetAngularAcceleration)
			.def("IsFlag", &World::Entity::IsFlag)
			.def("SetFlag", &World::Entity::SetFlag)
			.def("ToPlayer", &World::Entity::ToPlayer)
			.enum_("EntityType") [
				value("ENTITY_STATIC", World::ENTITY_STATIC),
				value("ENTITY_PLAYER", World::ENTITY_STATIC)
			]
			.enum_("EntityFlag") [
				value("ENTITY_FLAG_VISIBLE", World::ENTITY_FLAG_VISIBLE),
				value("ENTITY_FLAG_COLLIDABLE", World::ENTITY_FLAG_COLLIDABLE),
				value("ENTITY_FLAG_PHYSICS", World::ENTITY_FLAG_PHYSICS)
			],
		class_<World::PlayerEntity, World::Entity>("PlayerEntity")
			.property("LookVector", &World::PlayerEntity::GetLookVector, &World::PlayerEntity::SetLookVector)
	];
	
}


//==================================================
//! Execute some raw code
//==================================================
void VM::VM::Execute( const string& code ) {
	try {
		luaL_dostring( m_pLuaState, code.c_str() );
	} catch(luabind::error& e ) {
		std::cout << e.what() << std::endl;
		string strError= lua_tostring( e.state(), -1 );
		std::cout << strError << std::endl;
		throw;
	}
}


//==================================================
//! Set the current world
//==================================================
void VM::VM::SetWorld( World::World* pWorld ) {
	globals( m_pLuaState )["World"]= pWorld;
}


//==================================================
//! Deinitialize
//==================================================
VM::VM::~VM() {
	// Deinitialize lua
	lua_close( m_pLuaState );
}