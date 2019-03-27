#include "Component/CameraComponent.h"

CameraComponent::CameraComponent( guVector * cam, guVector* look, float * pitch, float * yaw, u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp,
	u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp )
	: ControllableComponent( buttonsHeld, buttonsDown, buttonsUp, wButtonsHeld, wButtonsDown, wButtonsUp ), m_cam(cam), m_look(look), m_pitch(pitch), m_yaw(yaw)
{

};
CameraComponent::~CameraComponent(){
	//@The actual values are held inside the graphic system
	m_cam = nullptr;
	m_look = nullptr;
	m_pitch = nullptr;
	m_yaw = nullptr;
	//@Prob not good to delete at null
	//delete m_cam;
	//delete m_look;

};