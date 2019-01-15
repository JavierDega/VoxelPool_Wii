#include "Component/OrbitCameraComponent.h"
#include "Extra/Math.h"
#include "GameObject.h"

using namespace Math;

//@Time globalVar in main.cpp
//extern float globalTime;

OrbitCameraComponent::OrbitCameraComponent()
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
	m_owner->m_transform.m_position =  RotateVectorAroundAxis (0.1*dt , guVector { 1, 1, 0 } , m_owner->m_transform.m_position);
	
	

}