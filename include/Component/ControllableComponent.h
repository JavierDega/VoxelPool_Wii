#ifndef CONTROLLABLECOMPONENT_H_
#define CONTROLLABLECOMPONENT_H_

#include "Component/LogicComponent.h"
#include <gccore.h>

//Controllable components interact with the padSystem
class ControllableComponent : public LogicComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	ControllableComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp);
	virtual ~ControllableComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );

	//Variables
	u16 * m_buttonsHeld;
	u16 * m_buttonsDown;
	u16 * m_buttonsUp;
};
#endif /*CONTROLLABLECOMPONENT_H_*/