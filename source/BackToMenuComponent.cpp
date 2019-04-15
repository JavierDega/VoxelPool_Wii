#include "Component/BackToMenuComponent.h"
#include "System/ObjectSystem.h"


BackToMenuComponent::BackToMenuComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp,
 u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp, float * swing, float * pitch, float * deviation, float * roll)
	: ControllableComponent(buttonsHeld, buttonsDown, buttonsUp, wButtonsHeld, wButtonsDown, wButtonsUp, swing, pitch, deviation, roll)
{

};
BackToMenuComponent::~BackToMenuComponent(){
	//@The actual values are held inside the PadSystem
};
void BackToMenuComponent::OnStart(){
	//@What do here?
}
void BackToMenuComponent::ComputeLogic( float dt ){

	ObjectSystem * os = ObjectSystem::GetInstance();

	u16 bdown = *(m_wButtonsDown);

	if (bdown & ( WPAD_BUTTON_A )){
		//Start option
		os->LoadScene(0);
	}
}
bool BackToMenuComponent::Receive( ComponentMessage msg){
	bool returnedVal = false;

	switch(msg){
		default:
		break;
	}

	return returnedVal;
}