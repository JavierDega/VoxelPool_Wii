#include "Component\RigidbodyComponent.h"
#include "Sphere.h"

RigidbodyComponent::RigidbodyComponent(float radius, float mass, bool isKinematic)
	: m_mass(mass), m_isKinematic(isKinematic)
{
	m_shape = new Sphere(radius);
	m_force = guVector{ 0, 0, 0 };
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