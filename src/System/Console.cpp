#include "common.h"
#include "Math/Vector.h"
#include "System/Console.h"
#include <iostream>

void System::Console::Print( const char* str ) {
	std::cout << str << std::endl;
}


void System::Console::PrintError( const char* str ) {
	std::cout << "ERROR: " << str << std::endl;
}

void System::Console::PrintUint( uint val ) {
	std::cout << "Uint: " << val << std::endl;
}

void System::Console::PrintVector( const Math::Vector& vec ) {
	std::cout << "Vector: (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}

void System::Console::PrintFloat( float val ) {
	std::cout << "Float: " << val << std::endl;
}