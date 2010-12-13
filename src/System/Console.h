#ifndef _SYSTEM_CONSOLE_H_
#define _SYSTEM_CONSOLE_H_

namespace Math { class Vector; }

namespace System {
	
	namespace Console {
	
		void Print( const char* str );
		void PrintError( const char* str );
		void PrintUint( uint val );
		void PrintVector( const Math::Vector& vec );
		void PrintFloat( float val );
	
	};
	
}; // end namespace System

#endif
