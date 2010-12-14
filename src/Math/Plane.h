/* Math/Plane.h
 *
 * A plane in 3d space, defined by a point and normal
 */

#include "Math/Vector.h"

namespace Math {

	// Coplanar means it's in the plane, both means it has points on both sides (only makes sense for polygons)
	enum PlaneSide {
		BACK, FRONT, COPLANAR, BOTH
	};

	class Plane {
	public:
		float Distance( const Vector& testPoint ) const;
		PlaneSide ClassifySide( const Vector& testPoint ) const;
		bool IsInFront( const Vector& testPoint ) const;
		Vector IntersectLine( const Vector& p1, const Vector& p2 ) const;
	protected:
		// Coefficients in plane equation ax + by + cz + d = 0
		Vector normal;		// <a, b, c>
		float distance;		// d
	}; // end class Plane

} // end namespace Math
