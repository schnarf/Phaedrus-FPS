#include "common.h"
#include "Math/Vector.h"

//==================================================
//! Construct a vertex
//==================================================
Math::Vector::Vector() :
	x(0.0),
	y(0.0),
	z(0.0) {
}


//==================================================
//! Construct from coordinates
//==================================================
Math::Vector::Vector( float _x, float _y, float _z ) :
	x(_x),
	y(_y),
	z(_z) {
}


//==================================================
//! Vector addition
//==================================================
const Math::Vector Math::Vector::operator+( const Math::Vector& rhs ) const {
	Vector result= *this;
	result+= rhs;
	return result;
}
Math::Vector& Math::Vector::operator+=( const Math::Vector& rhs ) {
	x+= rhs.X();
	y+= rhs.Y();
	z+= rhs.Z();
	
	return *this;
}


//==================================================
//! Vector subtraction
//==================================================
const Math::Vector Math::Vector::operator-( const Math::Vector& rhs ) const {
	Vector result= *this;
	result-= rhs;
	return result;
}
Math::Vector& Math::Vector::operator-=( const Math::Vector& rhs ) {
	x-= rhs.X();
	y-= rhs.Y();
	z-= rhs.Z();
	
	return *this;
}


//==================================================
//! Dot Product
//==================================================
float Math::Vector::operator*( const Math::Vector& rhs ) const {
	return x*rhs.X() + y*rhs.Y() + z*rhs.Z();
}
float Math::Vector::Dot( const Math::Vector& rhs ) const {
	return *this * rhs;
}


//==================================================
//! Scalar multiplication
//==================================================
const Math::Vector Math::Vector::operator*( const float& rhs ) const {
	Vector result= *this;
	result*= rhs;
	return result;
}
Math::Vector& Math::Vector::operator*=( const float& rhs ) {
	x*= rhs;
	y*= rhs;
	z*= rhs;
	
	return *this;
}
Math::Vector& Math::Vector::Scale( const float& rhs ) {
	return *this*= rhs;
}


//==================================================
//! Scalar division
//==================================================
const Math::Vector Math::Vector::operator/( const float& rhs ) const {
	Vector result= *this;
	result/= rhs;
	return result;
}
Math::Vector& Math::Vector::operator/=( const float& rhs ) {
	x/= rhs;
	y/= rhs;
	z/= rhs;
	
	return *this;
}
		
//==================================================
//! Vector length
//==================================================
float Math::Vector::Length() const {
	return sqrtf(x*x + y*y + z*z);
}
		
//==================================================
//! Normalize the vector
//==================================================
void Math::Vector::Normalize() {
	*this/= Length();
}