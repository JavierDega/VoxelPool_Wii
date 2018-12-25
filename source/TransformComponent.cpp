#include "Component/TransformComponent.h"

//Constructor
TransformComponent::TransformComponent(GameObject * owner, guVector position) : 
	Component(owner), m_position(position) 
{

}
//Destructor
TransformComponent::~TransformComponent(){
	//Empty vars
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

}