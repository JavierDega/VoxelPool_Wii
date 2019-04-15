#ifndef BACKTOMENUCOMPONENT_H_
#define BACKTOMENUCOMPONENT_H_

#include "Component/ControllableComponent.h"
#include <gccore.h>

//Game reset option
class BackToMenuComponent : public ControllableComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	BackToMenuComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp, 
		float * swing, float * pitch, float * deviation, float * roll);
	virtual ~BackToMenuComponent();
	virtual void OnStart();
	virtual void ComputeLogic( float dt );
	//Messaging
	virtual bool Receive( ComponentMessage msg );

	//Variables
};
#endif /*BACKTOMENUCOMPONENT_H_*/