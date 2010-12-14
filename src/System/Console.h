/* System/Console.h
 *
 * Interface for printing text to the screen
 */

#pragma once

namespace Math { class Vector; }

namespace System {
	
	namespace Console {
	
		void Print( const char* str );
		void PrintError( const char* str );
		void PrintUint( uint val );
		void PrintVector( const Math::Vector& vec );
		void PrintFloat( float val );
	
	} // end namespace Console
	
} // end namespace System
