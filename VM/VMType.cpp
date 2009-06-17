#include "common.h"
#include "VM/VMType.h"

VM::VMType::VMType( int val ) {
	m_type= VMTYPE_INT;
	*(reinterpret_cast<int*>(m_Data))= val;
}

VM::VMType::VMType( uint val ) {
	m_type= VMTYPE_UINT;
}

VM::VMType::VMType( float val ) {
	m_type= VMTYPE_FLOAT;
}

VM::VMType::VMType( string val ) {
	m_type= VMTYPE_STRING;
}

int VM::VMType::ToInt() const {
	switch( m_type ) {
	case VMTYPE_INT:
	case VMTYPE_UINT:
		// Just return the integer -- do we want to check range?
		return *(reinterpret_cast<const int*>(m_Data));

	case VMTYPE_FLOAT:
		// Round the float to an integer
		return (0.5f + static_cast<float>(*(reinterpret_cast<const int*>(m_Data))));
	
	default:
		throw VMTypeCastException();
		return 0;
	};
}

uint VM::VMType::ToUint() const {
	switch( m_type ) {
	case VMTYPE_INT:
	case VMTYPE_UINT:
		// Just return the integer  -- do we want to check range?
		return *(reinterpret_cast<const int*>(m_Data));

	case VMTYPE_FLOAT:
		// Round the float to an integer
		return (0.5f + static_cast<float>(*(reinterpret_cast<const int*>(m_Data))));
	
	default:
		throw VMTypeCastException();
		return 0;
	};
}

float VM::VMType::ToFloat() const {
	switch( m_type ) {
	case VMTYPE_INT:
		// Convert the integer to a float
		return static_cast<float>(*(reinterpret_cast<const int*>(m_Data)));
	case VMTYPE_UINT:
		// Convert the integer to a float
		return static_cast<float>(*(reinterpret_cast<const float*>(m_Data)));
	case VMTYPE_FLOAT:
		// Just return the float
		return *(reinterpret_cast<const float*>(m_Data));
	
	default:
		throw VMTypeCastException();
		return 0;
	};
}

string VM::VMType::ToString() const {
	// Unsupported for  now
	throw VMTypeCastException();
	return string("");
}