#ifndef LOGICCOMPONENT_H_
#define LOGICCOMPONENT_H_

#include "Component/Component.h"
#include <gccore.h>

//Logic components holds extra events for more control
class LogicComponent : public Component{
public:
	//Constructor
	//@Point to instances in PadSystem
	LogicComponent();
	virtual ~LogicComponent();
	virtual void OnStart() = 0;
	virtual void ComputeLogic(float dt) = 0;
	//void OnDestroy()?
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );

	//Variables
};
#endif /*LOGICCOMPONENT_H_*/