#include <iostream>
#include "System/Kernel.h"
#include <SDL.h>

using namespace std;

int main (int argc, char * argv[]) {
    // Start the kernel
	System::Kernel::Get()->Start();
	
    return 0;
}
