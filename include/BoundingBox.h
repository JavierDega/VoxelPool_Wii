#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include "Shape.h"

class BoundingBox :
	public Shape
{
public:
	BoundingBox(guVector halfExtents);
	virtual ~BoundingBox();

	//Variables
	guVector m_halfExtents;
};
#endif /*BOUNDINGBOX_H_*/