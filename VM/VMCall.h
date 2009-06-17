#include <boost/preprocessor.hpp>

#ifndef BOOST_PP_IS_ITERATING
#	ifndef _VM_VMCALL_H_
#		define _VM_VMCALL_H_
 
#		define BOOST_PP_ITERATION_LIMITS (0, 8)
 
#		define BOOST_PP_FILENAME_1 "VM/VMCall.h"
#		include BOOST_PP_ITERATE()
#	endif // _VM_VMCALL_H_
#else
#	define n BOOST_PP_ITERATION()

template <typename Ret BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>
inline Ret Call( const string& name BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, a) ) {
	
	return (Ret)luabind::call_function<Ret>( m_pLuaState, name.c_str() BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, a) );
}

#	undef n

#endif // BOOST_PP_IS_ITERATING