#ifndef ORBITCAMERACOMPONENT_H_
#define ORBITCAMERACOMPONENT_H_

#include "Component/LogicComponent.h"
#include <gccore.h>

//@Quaternions, rotate around its center , and orbit circularly around the camera
class OrbitCameraComponent : public LogicComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	OrbitCameraComponent(guVector movementAxis = guVector { 0, 1, 0 }, guVector rotAxis = guVector { 0, 0, 1 }, float speed = 1,
	 float rotSpeed = 1 );
	virtual ~OrbitCameraComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	//void OnDestroy()?
	//Messaging
	virtual bool Receive( ComponentMessage msg ) { return false;};

	//Variables
	guVector m_movementAxis;
	guVector m_rotAxis;
	float m_speed;
	float m_rotSpeed;
};
#endif /*ORBITCAMERACOMPONENT_H_*/