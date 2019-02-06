#ifndef AABB_H_
#define AABB_H_
#include "Shape.h"

class AABB :
	public Shape
{
public:
	AABB(guVector halfExtents = guVector{ 0.5f, 0.5f, 0.5f });
	~AABB();
	//virtual AABB ComputeAABB();
	//Variables
	guVector m_halfExtents;
};
#endif /*AABB_H_*/