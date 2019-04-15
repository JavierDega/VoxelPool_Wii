#include "Component/OrbitCameraComponent.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "Extra/Math.h"
#include "GameObject.h"
#include <ogc/pad.h>

OrbitCameraComponent::OrbitCameraComponent( guVector orbitOrigin, guVector * cam, guVector* look, float * pitch, float * yaw,
 u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp, float * swing, float * wPitch
 	, float * deviation, float * wRoll )
	: CameraComponent( cam, look, pitch, yaw, buttonsHeld, buttonsDown, buttonsUp, wButtonsHeld, wButtonsDown, wButtonsUp, swing, wPitch, deviation,
		 wRoll ),
	 m_orbitOrigin(orbitOrigin), m_zoom(20.f)
{

};
OrbitCameraComponent::~OrbitCameraComponent(){
	
	*m_pitch = 0;
	*m_yaw = 0;
};

void OrbitCameraComponent::OnStart(){
	//Look goes to origin, pitch and yaw are zero,
	//We set camera
	*m_look = m_orbitOrigin;
	*m_pitch = 0;
	*m_yaw = 0;
}
void OrbitCameraComponent::ComputeLogic(float dt){
	//Orbit camera around point (PoolTable?)
	GraphicSystem * gs = GraphicSystem::GetInstance();
	//@React to input

	u16 bheld = *(m_wButtonsHeld);

	u16 bdown = *(m_wButtonsDown);

	if (bheld & WPAD_BUTTON_LEFT ){
		
		*m_yaw -= 0.02f;
	}
	if (bheld & WPAD_BUTTON_RIGHT ){
		
		*m_yaw +=0.02f;
	}
	if (bheld & WPAD_BUTTON_DOWN ){

		*m_pitch -= 0.02f;
	}
	if (bheld & WPAD_BUTTON_UP ){
		
		*m_pitch +=0.02f;
	}
	if (bheld & WPAD_BUTTON_MINUS ){
		
		m_zoom -=0.3f;
	}
	if (bheld & WPAD_BUTTON_PLUS ){
		
		m_zoom +=0.3f;
	}

	m_zoom = MAX( 0.1f, m_zoom);
	m_zoom = MIN( 30.f, m_zoom);

	// limit pitch to straight up or straight down
	// with a little fudge-factor to avoid gimbal lock
	float limit = Math::PI / 2.0f - 0.01f;
	*m_pitch = MAX(0, *m_pitch);
	*m_pitch = MIN(limit, *m_pitch);
	// keep longitude in sane range by wrapping
	if (*m_yaw > Math::PI)
	{
		*m_yaw -= Math::PI * 2.0f;
	}
	else if (*m_yaw < -Math::PI)
	{
		*m_yaw += Math::PI * 2.0f;
	}

	//@Euler to direction vector
	float y = sinf(*m_pitch);
	float r = cosf(*m_pitch);
	float z = r * cosf(*m_yaw);
	float x = r * sinf(*m_yaw);

	guVector camOffset = guVector{ m_zoom*x, m_zoom*y, m_zoom*z };
	*m_look = m_orbitOrigin;//Circle around transform
	guVecAdd(m_look, &camOffset, m_cam);

	//std::string camLog = "Camera: " + std::to_string(m_cam->x) + " " + std::to_string(m_cam->y) + " " + std::to_string(m_cam->z);
	//Print camera and look
	//gs->AddLog(camLog);
	
	//std::string lookLog = "Look: " + std::to_string(m_look->x) + " " + std::to_string(m_look->y) + " " + std::to_string(m_look->z);
	//Print camera and look
	//gs->AddLog(lookLog);
}
bool OrbitCameraComponent::Receive(ComponentMessage msg){

	switch (msg){
		case ComponentMessage::START_AIMING:
		{
			//@We set the right m_orbitOrigin with a findbyName query
			guVector whiteBallT = ObjectSystem::GetInstance()->FindObjectByName("White_Ball")->m_transform.m_position;
			m_orbitOrigin = guVector { whiteBallT.x, whiteBallT.y + 1, whiteBallT.z };
		}
		break;
		case ComponentMessage::START_LOOKING:
		{
			//@Set origin
			m_orbitOrigin = Math::VecZero;
			*m_pitch = Math::PI / 2.0f - 0.01f;
			m_zoom = 30.f;
		}
		break;
		default:
		break;
	}
	return false;
}