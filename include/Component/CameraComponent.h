#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_

#include "Component/ControllableComponent.h"
#include <gccore.h>

//Controllable components interact with the padSystem
class CameraComponent : public ControllableComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	CameraComponent( guVector * cam, guVector* look, float * pitch, float * yaw, u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp,
	u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp, float * swing, float * wPitch, float * deviation, float * wRoll);
	virtual ~CameraComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );

	//Variables
	guVector * m_cam;
	guVector * m_look;
	float * m_pitch;
	float * m_yaw;
};
#endif /*CAMERACOMPONENT_H_*/