#include "Component/TransformComponent.h"
//Constructor
TransformComponent::TransformComponent(guVector position, guQuaternion rotation, guVector scale)
	: m_position(position) , m_rotation(rotation) , m_scale(scale)
{

}

//Destructor
TransformComponent::~TransformComponent(){
	//Empty vars
	
}