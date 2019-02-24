#ifndef ORBITCAMERACOMPONENT_H_
#define ORBITCAMERACOMPONENT_H_

#include "Component/CameraComponent.h"
#include <gccore.h>

//@Makes camera orbit lookPoint, depending on input
class OrbitCameraComponent : public CameraComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	OrbitCameraComponent( guVector * cam, guVector* look, float * pitch, float * yaw, u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp );
	virtual ~OrbitCameraComponent();
	virtual void OnStart();
	virtual void ComputeLogic (float dt);
	//Messaging
	virtual bool Receive( ComponentMessage msg );

	//Variables
	float m_zoom;
	bool m_pitchConstrained;//@For shooting routine
};
#endif /*ORBITCAMERACOMPONENT_H_*/