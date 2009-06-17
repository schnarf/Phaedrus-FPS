/* VM/VMType.h
 *
 * Generic VM data type, can be cast, and will object
 * to invalid casts.
 */
 
#ifndef _VM_VMTYPE_H_
#define _VM_VMTYPE_H_

#include <exception>

namespace VM {

	class VMTypeCastException : public std::exception {
		virtual const char* what() const throw() {
			return "Invalid cast from a VMType.";
		}
	}; // end class VMTypeException


	//! The number of bytes a VMType uses internally
	const uint VMTYPE_BYTES= 12;

	enum VMTypeCode {
		VMTYPE_INT,
		VMTYPE_UINT,
		VMTYPE_FLOAT,
		VMTYPE_STRING,
		VMTYPE_VECTOR,
		NUM_VMTYPES
	}; // end enum VMTypeCode
	
	class VMType {
	public:
		VMType( int val );
		VMType( uint val );
		VMType( float val );
		VMType( string val );
		
		int ToInt() const;
		uint ToUint() const;
		float ToFloat() const;
		string ToString() const;
		
		VMTypeCode GetType() const;
	private:
		//! Our stored data
		byte m_Data[VMTYPE_BYTES];
	
		//! The type that this data represents
		VMTypeCode m_type;
	}; // end class VMType
	
	
	inline VMTypeCode VMType::GetType() const { return m_type; }
	
}; // end namespace VM

#endif
