/* VM/VM.H
 *
 * The engine's virtual machine. Has only one instance.
 */

#pragma once

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
		//#include "VMCall.h"
		
		//! Register a function
		template <class F>
		void Register( const string& name, F f );
		
		//! Execute some raw code
		void Execute( const string& code );
		
		//! Load a script from disk
		Error LoadScript( const string& strFilename );
		
		//! Set the current world
		void SetWorld( World::World* pWorld );
		//! Registers engine globals in the VM
		void RegisterGlobals();
		
	private:
		//! Register a script, called by the Script constructor
		void registerScript( Script* pScript );
		
		//! The lua state
//		lua_State* m_pLuaState;

		//! Our opaque VM context
		struct VMContext;
		scoped_ptr<VMContext> m_pContext;
		
		vector<shared_ptr<Script> > m_scripts;
	}; // end class VM

	//! Smart pointer-like object for holding a handle to a VM object
	//! This allows us to have an object that's reference-counted and destroyed
	//! by the VM, that we can pass around and use like a smart pointer in C++
	template <typename T>
	class VMRef {
	public:
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;

		//! Default construct
		VMRef() :
			m_object(), m_pPointer(NULL) {}
		//! Construct from a VM object
		VMRef( boost::python::object object ) :
			m_object(object),
			m_pPointer(boost::python::extract<pointer>(object.ptr())) {}
		
		//! Copy constructor
		VMRef( const VMRef<T>& rhs ) :
			m_object(rhs.m_object),
			m_pPointer(rhs.m_pPointer) {
		} // end VMRef()

		//! Assignment operator
		VMRef<T>& operator=( const VMRef<T>& rhs ) {
			if( this != &rhs ) {
				m_object= rhs.m_object;
				m_pPointer= rhs.m_pPointer;
			} // end if not self assignment
			return *this;
		} // end operator=()

		//! Gets our pointer
		pointer get() { return m_pPointer; }
		//! Gets our const pointer
		const_pointer get() const { return m_pPointer; }

		//! Conversion to a pointer
		operator pointer() { return m_pPointer; }
		//! Conversion to a const pointer
		operator const_pointer() const { return m_pPointer; }

		//! Pointer operator
		reference operator*() { return *m_pPointer; }
		//! Const pointer operator
		const_reference operator*() const { return *m_pPointer; }

		//! Member operator
		pointer operator->() { return m_pPointer; }
		//! Const member operator
		const_pointer operator->() const { return m_pPointer; }
	private:
		boost::python::object m_object;		//!< Our VM object
		pointer m_pPointer;					//!< Our pointer to the cast object
	}; // end struct VMRef

} // end namespace VM

