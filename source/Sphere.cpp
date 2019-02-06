#include "Sphere.h"

Sphere::Sphere(float radius)
	: m_radius(radius)
{

}


Sphere::~Sphere()
{
}


//@AABB Culling
/*AABB Sphere::ComputeAABB()
{	
	//@Update AABB extents and return it (In case of Spheres, extents never change)
	//minExtent: (-radius, -radius, -radius )
	//maxExtent: ( radius, radius, radius )
	m_AABB = AABB{
		guVector{-m_radius, -m_radius, -m_radius},
		guVector{m_radius, m_radius, m_radius}
	};
	return m_AABB;
}*/
