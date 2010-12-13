#include <cmath>
#include "Math/Plane.h"
#include "Math/Vector.h"

float Math::Plane::Distance( const Vector& testPoint ) const {
	return fabs(testPoint * normal + distance);
}

Math::PlaneSide Math::Plane::ClassifySide( const Vector& testPoint ) const {
	float dist= normal * testPoint;
	
	if( dist == distance )
		return COPLANAR;
	else if( dist < distance )
		return BACK;
	
	return FRONT;
}

bool Math::Plane::IsInFront( const Vector& testPoint ) const {
	return (normal * testPoint) > distance;
}

// TODO: Check validity/this can be simplified probably
Math::Vector Math::Plane::IntersectLine( const Vector& p1, const Vector& p2 ) const {
	//assert(IsInFront(p1) != IsInFront(p2));

	float t = -1.0f * (normal * p1 + distance) / (normal * (p2 - p1));
	return (p2 - p1)*t + p1;
}