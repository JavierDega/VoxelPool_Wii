#ifndef MATH_H_
#define MATH_H_
#include <math.h>
#include "ogc/gu.h"

//@Math function extensions for the engine. Mainly matrices, vectors, quaternion functions.

namespace Math{

	//Defines
	const float PI = 3.1416f;
	//Vector @@CREATE OWN CLASSES INSTEAD
	const guVector VecZero { 0, 0, 0 };
	const guVector VecOne { 1, 1, 1 }; 
	float Length( guVector v );
	float LengthSq( guVector v );
	float DistSq(guVector v, guVector v2);
	guVector EulerToDirection (guVector eulerAngle);
	guVector VectorLerp (guVector v , guVector v2 , float frac);
	guVector RotateVectorAroundAxis (float angle , guVector axis , guVector vector);

	//Quaternion
	const guQuaternion QuatIdentity { 0, 0, 0, 1 };

	guQuaternion operator*( guQuaternion lhs, guQuaternion rhs);

	guQuaternion QuatFromAxisAngle(guVector axis, float angle);
}

#endif /*MATH_H_*/