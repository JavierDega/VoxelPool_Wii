#include "Component/Component.h"
#include "GameObject.h"

//Constructor
Component::Component(GameObject * owner)
	: m_owner(owner) 
{

}
//Destructor
Component::~Component()
{
	m_owner = nullptr;
	delete m_owner;
}