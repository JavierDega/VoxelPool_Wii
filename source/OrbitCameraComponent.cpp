#include "Component/OrbitCameraComponent.h"
#include "Extra/Math.h"
#include "GameObject.h"

//@Time globalVar in main.cpp
extern float globalTime;

OrbitCameraComponent::OrbitCameraComponent()
{

};
OrbitCameraComponent::~OrbitCameraComponent(){

};
void OrbitCameraComponent::OnStart(){

}
void OrbitCameraComponent::ComputeLogic(float dt){
	//Orbit around camera
	m_owner->m_transform.m_position.x = 10*cosf(globalTime);
	m_owner->m_transform.m_position.y = 10*sinf(globalTime);
	

}