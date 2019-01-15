#ifndef ORBITCAMERACOMPONENT_H_
#define ORBITCAMERACOMPONENT_H_

#include "Component/LogicComponent.h"
#include <gccore.h>

//@Quaternions, rotate around its center , and orbit circularly around the camera
class OrbitCameraComponent : public LogicComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	OrbitCameraComponent();
	virtual ~OrbitCameraComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	//void OnDestroy()?
	//Messaging
	virtual bool Receive( ComponentMessage msg ) { return false;};

	//Variables
};
#endif /*ORBITCAMERACOMPONENT_H_*/