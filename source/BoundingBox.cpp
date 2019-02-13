#include "BoundingBox.h"


BoundingBox::BoundingBox( guVector halfExtents )
	: Shape(ShapeType::AABB), m_halfExtents(halfExtents)
{

}

BoundingBox::~BoundingBox(){

}