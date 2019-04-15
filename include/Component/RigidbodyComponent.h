#ifndef RIGIDBODYCOMPONENT_H_
#define RIGIDBODYCOMPONENT_H_

#include "Component/Component.h"
#include "Shape.h"
#include "Extra/Math.h"

#include <ogc/gu.h>

enum BallType{
	BALL_NONE,//@AABB RIGIDBODIES / WHITE_BALL
	BALL_RED,
	BALL_BLUE
};

//@Handles physics
class RigidbodyComponent :
	public Component
{
public:
	//Funcs
	//Sphere constructor
	RigidbodyComponent(float radius = 0.5f, float mass = 1.f, bool isKinematic = false, bool isTrigger = false, BallType type = BallType::BALL_RED );
	//@AABB constructor
	RigidbodyComponent( guVector halfExtents = Math::VecOne, float mass = 1.0f, bool isKinematic = false, bool isTrigger = false,
	 BallType type = BallType::BALL_NONE );
	virtual ~RigidbodyComponent();
	//Messaging
	virtual bool Receive(ComponentMessage msg);

	//Variables
	Shape * m_shape;
	float m_mass;
	bool m_isKinematic;
	bool m_isTrigger;
	bool m_isSleeping;
	BallType m_ballType;
	//Semi euler
	guVector m_force, m_acceleration, m_velocity;
};
#endif /*RIGIDBODYCOMPONENT_H_*/