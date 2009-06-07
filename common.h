#ifndef _COMMON_H_
#define _COMMON_H_

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
typedef unsigned char byte;

enum Error {
	ERROR_OK,
	ERROR_FILE_DOES_NOT_EXIST,
	NUM_ERRORS
};

#include "common_checked_type.h"

#endif
