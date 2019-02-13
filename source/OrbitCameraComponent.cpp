#include "Component/OrbitCameraComponent.h"
#include "System/GraphicSystem.h"
#include "Extra/Math.h"

#include <ogc/pad.h>

OrbitCameraComponent::OrbitCameraComponent( guVector * cam, guVector* look, float * pitch, float * yaw, u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp)
	: CameraComponent( cam, look, pitch, yaw, buttonsHeld, buttonsDown, buttonsUp ), m_zoom(20.f)
{

};
OrbitCameraComponent::~OrbitCameraComponent(){
	
	*m_pitch = 0;
	*m_yaw = 0;
};

void OrbitCameraComponent::OnStart(){

	//Look goes to origin, pitch and yaw are zero,
	//We set camera
	*m_look = Math::VecZero;
	*m_pitch = 0;
	*m_yaw = 0;

	//@Euler to direction vector
	float y = sinf(*m_pitch);
	float r = cosf(*m_pitch);
	float z = r * cosf(*m_yaw);
	float x = r * sinf(*m_yaw);

	guVector camOffset = guVector{ x, y, z };
	guVecAdd(m_look, &camOffset, m_cam);
}
void OrbitCameraComponent::ComputeLogic(float dt){
	//Orbit camera around point (PoolTable?)
	//GraphicSystem * gs = GraphicSystem::GetInstance();
	//@React to input

	u16 bheld = *(m_buttonsHeld);

	if (bheld & PAD_BUTTON_LEFT ){
		
		*m_yaw -= 0.02f;

	}
	if (bheld & PAD_BUTTON_RIGHT ){
		
		*m_yaw +=0.02f;
	}

	if (bheld & PAD_BUTTON_DOWN ){
		
		*m_pitch -= 0.02f;

	}
	if (bheld & PAD_BUTTON_UP ){
		
		*m_pitch +=0.02f;
	}

	if (bheld & PAD_TRIGGER_L ){
		
		m_zoom -=0.3f;
	}
	if (bheld & PAD_TRIGGER_R ){
		
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
	guVecAdd(m_look, &camOffset, m_cam);

	std::string camLog = "Camera: " + std::to_string(m_cam->x) + " " + std::to_string(m_cam->y) + " " + std::to_string(m_cam->z);
	//Print camera and look
	//gs->AddLog(camLog);
	
	std::string lookLog = "Look: " + std::to_string(m_look->x) + " " + std::to_string(m_look->y) + " " + std::to_string(m_look->z);
	//Print camera and look
	//gs->AddLog(lookLog);
}