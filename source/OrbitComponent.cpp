#include "Component/OrbitComponent.h"
#include "Extra/Math.h"
#include "GameObject.h"

using namespace Math;

//@Time globalVar in main.cpp
//extern float globalTime;

OrbitComponent::OrbitComponent(guVector origin, guVector movementAxis, guVector rotAxis, float speed, float rotSpeed)
	: m_origin(origin), m_movementAxis(movementAxis), m_rotAxis(rotAxis), m_speed(speed), m_rotSpeed(rotSpeed)
{
//@Normalize axes?
};
OrbitComponent::~OrbitComponent(){

};
void OrbitComponent::OnStart(){

}
void OrbitComponent::ComputeLogic(float dt){
	//Orbit around camera
	//@Approach1
	//m_owner->m_transform.m_position.x = 100*cosf(globalTime);
	//m_owner->m_transform.m_position.z = 100*sinf(globalTime);
	m_owner->m_transform.m_position =  RotateVectorAroundAxis (m_speed*dt , m_movementAxis, m_owner->m_transform.m_position );
	
	//Create axis rotation from quaternion
	guQuaternion rotAxis = QuatFromAxisAngle( m_rotAxis, m_rotSpeed*dt);
	m_owner->m_transform.m_rotation = rotAxis * m_owner->m_transform.m_rotation;

}