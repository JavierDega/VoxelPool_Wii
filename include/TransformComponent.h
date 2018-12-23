#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_
#include "gu.h"
#include "Component.h"

class TransformComponent: public Component {
public:
	//Functions
	TransformComponent(GameObject * owner, guVector position) : 
		Component(owner), m_position(position) {}
	//Messaging
	//virtual bool Receive( ComponentMessage * msg);
	//Variables
	//Vector3 position
	guVector m_position;



}
#endif /*TRANSFORMCOMPONENT_H_*/