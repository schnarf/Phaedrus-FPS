/* Math/Vector.h
 *
 * A vector in 3d space
 */

#pragma once

namespace Math {

	class Vector {
	public:
		//! Construct a vertex
		Vector();
		
		//! Construct from coordinates
		Vector( float _x, float _y, float _z );
		
		//! Inline accessors
		inline float X() const { return x; }
		inline float Y() const { return y; }
		inline float Z() const { return z; }
		
		//! Inline set functions
		inline void X( float _x ) { x= _x; }
		inline void Y( float _y ) { y= _y; }
		inline void Z( float _z ) { z= _z; }
		
		//! Vector addition
		const Vector operator+( const Vector& rhs ) const;
		Vector& operator+=( const Vector& rhs );
		
		//! Vector subtraction
		const Vector operator-( const Vector& rhs ) const;
		Vector& operator-=( const Vector& rhs );
		
		//! Dot Product
		float Dot( const Vector& rhs ) const;
		float operator*( const Vector& rhs ) const;
		
		//! Scalar multiplication
		Vector& Scale( const float& rhs );
		const Vector operator*( const float& rhs ) const;
		Vector& operator*=( const float& rhs );
		
		//! Scalar division
		const Vector operator/( const float& rhs ) const;
		Vector& operator/=( const float& rhs );
		
		//! Vector length
		float Length() const;
		
		//! Normalize the vector
		Math::Vector& Normalize();
		
		//! Public members
		float x, y, z;
	}; // end class Vector
	
} // end namespace Math
