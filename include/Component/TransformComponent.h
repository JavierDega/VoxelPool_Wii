#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "Component/Component.h"
#include "Extra/Math.h"
#include <gccore.h>

class TransformComponent: public Component {
public:
	//Functions
	TransformComponent(guVector position = guVector{ 0, 0, 0 }, guQuaternion rotation = Math::QuatIdentity, guVector scale = guVector{ 1, 1, 1 });
	virtual ~TransformComponent();
	//Messaging
	virtual bool Receive( ComponentMessage msg){ return false;};
	//Variables
	guVector m_position;
	guQuaternion m_rotation;
	guVector m_scale;
};
#endif /*TRANSFORMCOMPONENT_H_*/