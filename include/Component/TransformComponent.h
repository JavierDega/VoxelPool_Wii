#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "Component/Component.h"
#include <gccore.h>

class TransformComponent: public Component {
public:
	//Functions
	TransformComponent(guVector position);
	~TransformComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg);
	//Variables
	guVector m_position;
};
#endif /*TRANSFORMCOMPONENT_H_*/