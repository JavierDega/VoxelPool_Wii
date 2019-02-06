#ifndef SHAPE_H_
#define SHAPE_H_

#include "ogc/gu.h"

/*struct AABB {
	guVector m_minExtent;
	guVector m_maxExtent;
};*/

//@Finds the common ground between all collider types, including those used for broad phase.
class Shape
{
public:
	Shape();
	virtual ~Shape();
	//Funcs
	//virtual AABB ComputeAABB() = 0;

	//Variables
};
#endif /*SHAPE_H_*/
