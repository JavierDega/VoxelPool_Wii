#include "Extra/Math.h"

namespace Math{

	float Length( guVector v ){
		return sqrtf( v.x*v.x + v.y*v.y + v.z*v.z);
	}

	float LengthSq( guVector v ){
		return ( v.x*v.x + v.y*v.y + v.z*v.z);
	}

	float DistSq(guVector v, guVector v2){
		guVector r;
		guVecSub( &v, &v2, &r);
		return ( r.x*r.x + r.y*r.y + r.z*r.z);
	}

	guVector EulerToDirection (guVector eulerAngle){

		float z = cos(eulerAngle.y)*cos(eulerAngle.x);
		float y = sin(eulerAngle.x);
		float x = cos(eulerAngle.x)*sin(eulerAngle.y);
		guVector rv = guVector{ x, y, z };

		return rv;
	}

	guVector VectorLerp (guVector v , guVector v2 , float frac){

		//@frac = clamp (frac, 0.0f, 1.0f);
		guVector r;
		guVecScale( &v, &r, 1.0f - frac );
		guVector v2Frac;
		guVecScale( &v2, &v2Frac, frac);
		guVecAdd( &r, &v2Frac, &r );
		return r;
		//return v * (1.0f - frac) + v2 * frac;

	}

	guVector RotateVectorAroundAxis (float angle , guVector axis , guVector vector){
	
		//Rodriguez formula , make sure angle is in radians
		//N' being returned vector , N original vector , v being axis and 0 being angle
		//N' = Ncos0 + (N dot v)v(1-cos0) + (v X N)sin0
		guVector r;

		guVector vecCosA;
		guVecScale( &vector, &vecCosA, cos(angle));

		guVector dpVAxisCosA;
		guVecScale( &axis, &dpVAxisCosA, guVecDotProduct( &vector, &axis )*( 1 - cos(angle) ) );

		guVector vXNSinA;
		guVecCross( &axis, &vector, &vXNSinA );
		guVecScale( &vXNSinA, &vXNSinA, sin(angle));

		guVecAdd( &vecCosA, &dpVAxisCosA, &r);
		guVecAdd( &r, &vXNSinA, &r);

		//guVector r = vector*cos(angle) + guVecDotProduct(&vector, &axis)*axis*(1 - cos(angle)) + vXNSinA; 
		return r;
	}

	//Quaternion
	//@Duplicated
	guQuaternion operator*( guQuaternion q, guQuaternion q2){
		//RS = (SwRw – Sv· Rv, SwRv + RwSv + Rv X Sv)
		guQuaternion rquat;
		guVector qaxis = guVector{ q.x, q.y, q.z };
		guVector q2axis = guVector{ q2.x, q2.y, q2.z};

		//W
		rquat.w = q2.w*q.w - guVecDotProduct(&q2axis, &qaxis);

		guVector qaxisXq2axis;
		guVecCross(&qaxis, &q2axis, &qaxisXq2axis);

		guVector q2wqaxis;
		guVecScale( &qaxis, &q2wqaxis, q2.w);
		guVector qwq2axis;
		guVecScale( &q2axis, &qwq2axis, q.w);

		guVector raxis;//= q2.w*qaxis + q.w*q2axis + qaxisXq2axis;
		guVecAdd( &qaxisXq2axis, &q2wqaxis, &raxis);
		guVecAdd( &raxis, &qwq2axis, &raxis);

		//V
		rquat.x = raxis.x;
		rquat.y = raxis.y;
		rquat.z = raxis.z;

		return rquat;
	}
	
	guQuaternion QuatFromAxisAngle( guVector axis, float angle){
		guQuaternion quat;
		float halfAngle = angle/2;
		quat.w = cos(halfAngle);
		quat.x = axis.x*sin(halfAngle);
		quat.y = axis.y*sin(halfAngle);
		quat.z = axis.z*sin(halfAngle);
		return quat;
	}

	//Inverse unit quaternion
	//@Duplicated
	guQuaternion QuatInverse( guQuaternion q){
		return guQuaternion { -q.x, -q.y, -q.z, q.w };
	}	
}