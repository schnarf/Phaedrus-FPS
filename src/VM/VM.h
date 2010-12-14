/* VM/VM.H
 *
 * The engine's virtual machine. Has only one instance.
 */

#pragma once

#include "luabind/luabind.hpp"

namespace World { class World; }

namespace VM {

	class Script;
	
	struct Function {
		string Name;
		uint uNumParams;
	}; // end struct Function
	
	class VM {
		friend class Script;
	public:
		VM();
		~VM();
	
		//! Call a function
		// template <typename Ret, typename T0, typename T1, ...>
		// Ret Call( const string& name, T0 a0, T1 a1, ... );
		#include "VMCall.h"
		
		//! Register a function
		template <class F>
		void Register( const string& name, F f );
		
		//! Execute some raw code
		void Execute( const string& code );
		
		//! Load a script from disk
		Error LoadScript( const string& strFilename );
		
		//! Set the current world
		void SetWorld( World::World* pWorld );
		
	private:
		//! Register a script, called by the Script constructor
		void registerScript( Script* pScript );
		
		//! The lua state
		lua_State* m_pLuaState;
		
		vector<shared_ptr<Script> > m_scripts;
	}; // end class VM
	
	//! Register a function
	template <class F>
	inline void VM::Register( const string& name, F f ) {
		luabind::module( m_pLuaState ) [
			luabind::def( name.c_str(), f )
		];
	}
	
} // end namespace VM

