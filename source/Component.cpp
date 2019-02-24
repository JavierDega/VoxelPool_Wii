#include "Component/Component.h"
#include "GameObject.h"

//Constructor
Component::Component()
	: m_owner(nullptr) 
{
	m_isActive = true;
}
//Destructor
Component::~Component()
{
	m_owner = nullptr;
	delete m_owner;
}