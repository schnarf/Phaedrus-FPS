/* common_exception.h
 *
 * Common exception classes
 */

#pragma once

#include <boost/exception/all.hpp>

#define THROW_EXCEPTION BOOST_THROW_EXCEPTION

//! Our exception base class, that takes file and line number
struct ExceptionBase : virtual std::exception, virtual boost::exception {};

/* =================== File I/O Exceptions =================== */
//! Any file input/output exception
struct FileIOException : virtual ExceptionBase {};
//! FileIOExceptions can have a filename attached to them
typedef boost::error_info<struct tag_FileIOExceptionFilename, string> FileIOExceptionFilename;

//! An error reading from a file
struct FileReadException : virtual FileIOException {};

//! An error parsing a file
struct FileParseException : virtual FileIOException {};
//! A file parse exception can specify why it failed
typedef boost::error_info<struct tag_FileParseExceptionCause, string> FileParseExceptionCause;