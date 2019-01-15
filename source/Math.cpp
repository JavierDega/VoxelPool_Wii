#include "Extra/Math.h"

namespace Math{
	//Vector
	guVector operator * (guVector v, float f){
		return guVector{ v.x*f, v.y*f, v.z*f };
	}

	guVector operator + (guVector v, guVector v2){
		return guVector{ v.x + v2.x, v.y + v2.y, v.z + v2.z};
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
		return v * (1.0f - frac) + v2 * frac;

	}

	guVector RotateVectorAroundAxis (float angle , guVector axis , guVector vector){
	
		//Rodriguez formula , make sure angle is in radians
		//N' being returned vector , N original vector , v being axis and 0 being angle
		//N' = Ncos0 + (N dot v)v(1-cos0) + (v X N)sin0
		guVector vXN;
		guVecCross( &axis, &vector, &vXN );
		guVector rv = vector*cos(angle) + guVecDotProduct(&vector, &axis)*axis*(1 - cos(angle)) + vXN*sin(angle);	 
		return rv;
	}

	//Quaternion
	guQuaternion operator*( guQuaternion q, guQuaternion q2){
		//RS = (SwRw – Sv· Rv, SwRv + RwSv + Rv X Sv)
		guQuaternion rquat;
		guVector qaxis = guVector{ q.x, q.y, q.z };
		guVector q2axis = guVector{ q2.x, q2.y, q2.z};

		//W
		rquat.w = q2.w*q.w - guVecDotProduct(&q2axis, &qaxis);

		guVector qaxisXq2axis;
		guVecCross(&qaxis, &q2axis, &qaxisXq2axis);
		guVector raxis = q2.w*qaxis + q.w*q2axis + qaxisXq2axis;

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
}