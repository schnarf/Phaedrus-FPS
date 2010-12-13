#ifndef _COMMON_H_
#define _COMMON_H_

#define __DEBUG_BUILD__ 1

#include <string>
using std::string;

#include <deque>
using std::deque;

#include <vector>
using std::vector;

#include <map>
using std::map; using std::multimap;

#include <memory>
using std::auto_ptr;

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include <assert.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
typedef boost::mutex Mutex;
typedef boost::mutex::scoped_lock ScopedLock;
typedef boost::thread::id ThreadID;

typedef unsigned int uint;
typedef unsigned int uint32;
typedef unsigned long long int uint64;
typedef unsigned char byte;

enum Error {
	ERROR_OK,
	ERROR_FILE_DOES_NOT_EXIST,
	NUM_ERRORS
};

#include "common_checked_type.h"

#if __DEBUG_BUILD__
	#include <iostream>
	
	#define DebugPrint( strError ) \
		std::cerr << __FILE__ << ", Line " << __LINE__ << ": " << strError << std::endl;
#else
	#define DebugPrint( strError )
#endif

// Include the engine globals
#include "globals.h"

#endif
