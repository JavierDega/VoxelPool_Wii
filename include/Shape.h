#ifndef SHAPE_H_
#define SHAPE_H_
#include <ogc/gu.h>

//@To avoid convoluted shape downcasts
enum ShapeType {
	SPHERE,
	AABB
};
//@Finds the common ground between all collider types, including those used for broad phase.
class Shape
{
public:
	Shape(ShapeType type);
	virtual ~Shape();
	//Funcs

	//Variables
	ShapeType m_type;
};
#endif /*SHAPE_H_*/
