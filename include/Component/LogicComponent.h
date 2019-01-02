#ifndef LOGICCOMPONENT_H_
#define LOGICCOMPONENT_H_

#include "Component/Component.h"
#include <gccore.h>

//Logic components holds extra events for more control
class LogicComponent : public Component{
public:
	//Constructor
	//@Point to instances in PadSystem
	LogicComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp);
	virtual ~LogicComponent();
	virtual void OnStart() = 0;
	virtual void ComputeLogic() = 0;
	//void OnDestroy()?
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );

	//Variables
	u16 * m_buttonsHeld;
	u16 * m_buttonsDown;
	u16 * m_buttonsUp;
};
#endif /*LOGICCOMPONENT_H_*/