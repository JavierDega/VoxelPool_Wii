#include "Component/ShootControllerComponent.h"
#include "GameObject.h"
#include "System/ObjectSystem.h"

#include <ogc/pad.h>

//Constructor
ShootControllerComponent::ShootControllerComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, float offsetScale, bool rotate, bool isScreenSpace)
	: ControllableComponent(buttonsHeld, buttonsDown, buttonsUp)
{
	m_option = 0;
	m_isActive = false;//@Starts inactive
}
//Destructor
ShootControllerComponent::~ShootControllerComponent(){
	//@
}
//Start
void ShootControllerComponent::OnStart(){
	
}
//Update
void ShootControllerComponent::ComputeLogic(float dt){
	//Choose option
	ObjectSystem * os = ObjectSystem::GetInstance();
	u16 bdown = *(m_buttonsDown);
	u16 bheld = *(m_buttonsHeld);
	switch(step){
		case 0:
		{
			//@We're in far away view, all balls on rest, ready to start our next turn.
			if (bdown & (PAD_BUTTON_A)){
				//@Make the camera go closer (Send message to OrbitCameraComponent)
				//@Constrain the camera's pitch (Send message to OrbitCameraComponent)
				m_owner->Send(ComponentMessage::SHOOT_CLOSEUP);
				m_step++;
			}
		}
		break;
		case 1:
		{
			//@We're now in a close up view to the white ball (By manipulating OrbitCameraComponent)
			//With a constrained pitch, aiming what angle to shoot it from (Deduced from our cam->look vector)
			//The look being the white ball's centre.
		}
		break;

	}

	if (bdown & (PAD_BUTTON_LEFT | PAD_BUTTON_UP)){

	}
	if (bdown & (PAD_BUTTON_RIGHT | PAD_BUTTON_DOWN)){
		
	}
}
bool ShootControllerComponent::Receive(ComponentMessage msg){
	switch(msg){
		case ComponentMessage::ENABLE_SHOOT:
		{
			m_isActive = true;//@Enabled routine
			m_step = 0;//@Listening for first step of shooting routine
		}
		break;
		default:
		break;
	}
}