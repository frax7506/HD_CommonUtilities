#include "HD_AngleUtils.h"

f32 HD_AngleUtils::SignedAngleBetweenVectors(const HD_Vector2_f32& aVector1, const HD_Vector2_f32& aVector2)
{
	// Returns the smallest angle that rotates aVector2 to aVector1.
		// Clockwise rotation returns a negative angle, counter clockwise rotation returns a positive angle.
		// Source: https://wumbo.net/formulas/angle-between-two-vectors-2d/

	const f32 angle = HD_ArcTan2(aVector2.myX * aVector1.myY - aVector2.myY * aVector1.myX, aVector2.myX * aVector1.myX + aVector2.myY * aVector1.myY);
	return angle;
}

f32 HD_AngleUtils::AngleBetweenVectors(const HD_Vector2_f32& aVector1, const HD_Vector2_f32& aVector2)
{
	const f32 signedAngle = SignedAngleBetweenVectors(aVector1, aVector2);
	const f32 unsignedAngle = signedAngle * HD_Sign(signedAngle);
	return unsignedAngle;
}
