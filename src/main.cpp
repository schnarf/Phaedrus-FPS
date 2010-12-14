#include "common.h"
#include <iostream>
#include "System/Kernel.h"

using namespace std;

int main (int argc, char * argv[]) {
    // Start the kernel
	System::Kernel* pKernel= new System::Kernel();
	pKernel->Start();
	
    return 0;
}
