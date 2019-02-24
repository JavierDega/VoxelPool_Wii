#ifndef SHOOTCONTROLLERCOMPONENT_H_
#define SHOOTCONTROLLERCOMPONENT_H_

#include "Component/ControllableComponent.h"
#include <vector>
#include <gccore.h>

//@Controls shooting routine
class ShootControllerComponent : public ControllableComponent{
public:
	//Constructor
	ShootControllerComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, float offsetScale = 1.0f, bool rotate = false, bool isScreenSpace = false);
	virtual ~ShootControllerComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	//Messaging
	virtual bool Receive( ComponentMessage msg );

	//Variables
	u16 m_step;
};
#endif /*MENUSELECTOR_H_*/