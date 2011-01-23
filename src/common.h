/* common.h
 *
 * Our precompiled header, must be included at the top of every
 * .cpp file, and cannot be included elsewhere
 */

#ifndef _COMMON_H_INCLUDED_
#define _COMMON_H_INCLUDED_

#include <string>
#include <deque>
#include <vector>
#include <map>
#include <memory>
// Import the whole std namespace. Good idea?
using namespace std;

// TODO: Don't need boost shared_ptr if we have tr1 or c++0x
//#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
using boost::scoped_ptr;
#include <cassert>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/python.hpp>

typedef boost::mutex Mutex;
typedef boost::mutex::scoped_lock ScopedLock;
typedef boost::thread::id ThreadID;
typedef boost::condition_variable ConditionVariable;
typedef boost::thread Thread;

typedef unsigned int uint;
typedef unsigned int uint32;
typedef unsigned long long int uint64;
typedef unsigned char byte;

#include <SDL.h>

enum Error {
	ERROR_OK,
	ERROR_FILE_DOES_NOT_EXIST,
	NUM_ERRORS
};

#include "common_checked_type.h"
#include "common_exception.h"

#ifdef _DEBUG
	#include <iostream>
	
	#define DebugPrint( strError ) \
		std::cerr << __FILE__ << ", Line " << __LINE__ << ": " << strError << std::endl;
#else
	#define DebugPrint( strError )
#endif

// Include the engine globals
#include "globals.h"

#else

// Prevent other inclusions
#error "common.h cannot be included from anywhere but the top of a .cpp file."

#endif