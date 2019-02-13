#include "Component\RigidbodyComponent.h"
#include "BoundingBox.h"
#include "Sphere.h"

RigidbodyComponent::RigidbodyComponent(float radius, float mass, bool isKinematic, bool isTrigger)
	: m_mass(mass), m_isKinematic(isKinematic), m_isTrigger(isTrigger)
{
	m_shape = new Sphere(radius);
	m_force = guVector{ 0, 0, 0 };
	m_acceleration = guVector{ 0, 0, 0 };
	m_velocity = guVector{ 0, 0, 0 };
}
//AABB Constructor
RigidbodyComponent::RigidbodyComponent( guVector halfExtents, float mass, bool isKinematic, bool isTrigger)
	: m_mass(mass), m_isKinematic(isKinematic), m_isTrigger(isTrigger)
{
	m_shape = new BoundingBox(halfExtents);
	m_force = guVector { 0, 0, 0 };
	m_acceleration = guVector{ 0, 0, 0 };
	m_velocity = guVector{ 0, 0, 0 };
}

RigidbodyComponent::~RigidbodyComponent()
{
	//Destroy pointer
	delete m_shape;
	m_shape = nullptr;
}

bool RigidbodyComponent::Receive(ComponentMessage msg)
{
	return false;
}