#include "Component/OrbitCameraComponent.h"
#include "Extra/Math.h"
#include "GameObject.h"

using namespace Math;

//@Time globalVar in main.cpp
//extern float globalTime;

OrbitCameraComponent::OrbitCameraComponent(guVector movementAxis, guVector rotAxis, float speed, float rotSpeed)
	: m_movementAxis(movementAxis), m_rotAxis(rotAxis), m_speed(speed), m_rotSpeed(rotSpeed)
{

};
OrbitCameraComponent::~OrbitCameraComponent(){

};
void OrbitCameraComponent::OnStart(){

}
void OrbitCameraComponent::ComputeLogic(float dt){
	//Orbit around camera
	//@Approach1
	//m_owner->m_transform.m_position.x = 100*cosf(globalTime);
	//m_owner->m_transform.m_position.z = 100*sinf(globalTime);
	m_owner->m_transform.m_position =  RotateVectorAroundAxis (m_speed*dt , m_movementAxis, m_owner->m_transform.m_position );
	
	//Create axis rotation from quaternion
	guQuaternion rotAxis = QuatFromAxisAngle( m_rotAxis, m_rotSpeed*dt);
	m_owner->m_transform.m_rotation = rotAxis * m_owner->m_transform.m_rotation;

}