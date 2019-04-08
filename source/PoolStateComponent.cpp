#include "Component/PoolStateComponent.h"
#include "Component/OrbitCameraComponent.h"
#include "GameObject.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "System/PadSystem.h"
#include "Extra/Math.h"
//You are a wizard
using namespace std;

PoolStateComponent::PoolStateComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, u16 * wButtonsHeld, u16 *wButtonsDown, u16 * wButtonsUp, 
	float * swing, float * wPitch, float * deviation, float * wRoll )
	: ControllableComponent(buttonsHeld, buttonsDown, buttonsUp, wButtonsHeld, wButtonsDown, wButtonsUp, swing, wPitch, deviation, wRoll)
{
	m_activeState = STATE_LOOKING;
	m_playerTurn = false;//Player 1's turn
	//@Accel delta
	m_backMotion = 0;
	m_lateralMotion = 0;
};
PoolStateComponent::~PoolStateComponent(){
//You are a wizard
}
void PoolStateComponent::OnStart(){

	GraphicSystem * gs = GraphicSystem::GetInstance();
	//@Add a Pan camera component
	m_owner->AddComponent(new OrbitCameraComponent( Math::VecZero, &gs->m_cam, &gs->m_look, &gs->m_pitch, &gs->m_yaw,
	 m_buttonsHeld, m_buttonsDown, m_buttonsUp, m_wButtonsHeld, m_wButtonsDown, m_wButtonsUp, m_swing, m_wPitch, m_deviation, m_wRoll));
	m_owner->AddComponent(new FontComponent(L"Waiting for turn...", guVector{ -175, 200, 0}, GXColor{ 100, 250, 100, 200 }, 3, true, true));
	m_owner->AddComponent(new FontComponent(L"P1: Balls left", guVector{ -300, -200, 0}, GXColor{ 250, 100, 100, 250 }, 3, true, true));
	m_owner->AddComponent(new FontComponent(L"P2: Balls left", guVector{ 0, -200, 0}, GXColor{ 100, 100, 250, 250 }, 3, true, true));
	m_owner->AddComponent( new MeshComponent("poolstick"));
}
void PoolStateComponent::ComputeLogic(float dt){

	ObjectSystem * os = ObjectSystem::GetInstance();

	switch (m_activeState){
		case STATE_LOOKING:
		{
			//Look for all sleeping balls
			vector <RigidbodyComponent*> rigidbodies = os->GetRigidbodyComponentList();
			bool allSleeping = true;
			for(RigidbodyComponent * rigidbody : rigidbodies){
				if (rigidbody->m_isSleeping == false) 
				{
					allSleeping = false;
					break;
				}
			}

			if (allSleeping){
				m_playerTurn ^= 1;
				m_owner->Send(ComponentMessage::START_ALL_SLEEPING);
				m_activeState = PoolStates::STATE_ALL_SLEEPING;
			}
		}
		break;
		case STATE_ALL_SLEEPING:
		{
			//Here we listen for our own input, to go into the next state basically
			//@Button B to go back?
			if (*m_wButtonsDown & WPAD_BUTTON_A){
				m_owner->Send(ComponentMessage::START_AIMING);
				m_activeState = PoolStates::STATE_AIMING;
			}
		}
		break;
		case STATE_AIMING:
		{
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			*occ->m_pitch =0.3f;//Constrains pitch and zoom
			occ->m_zoom = 4.0f;
			if (*m_wButtonsDown & WPAD_BUTTON_A){
				m_owner->Send(ComponentMessage::START_LOCKED_DIRECTION);
				m_activeState = PoolStates::STATE_LOCKED_DIRECTION;
			}
		}
		break;
		case STATE_LOCKED_DIRECTION:
		{
			//We have a threshold to commit
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			*occ->m_pitch = 0.3f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 4.5f;

			if ((abs(*m_wPitch) < 45) && (abs(*m_wRoll) < 45)){
				m_owner->Send(ComponentMessage::WIIMOTE_BALANCED);
				if (*m_swing < -0.8f){
					//@We comitted to a shot
					m_owner->Send(ComponentMessage::START_COMMIT_CHARGING);
					m_activeState = PoolStates::STATE_COMMIT_CHARGING;
				}
			}
			else {
				//Send message to balance wiimote
				m_owner->Send(ComponentMessage::WIIMOTE_UNBALANCED);
			}
		}
		break;
		case STATE_COMMIT_CHARGING:
		{
			//@We keep on charging
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			*occ->m_pitch = 0.3f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 4.5f;

			//@Store highest delta
			if (*m_swing < m_backMotion){
				m_backMotion = *m_swing;//Store max delta to measure force
			}
			if (*m_swing >= 0 || abs(*m_wPitch >= 45) || abs(*m_wRoll >= 45)){
				//@Finish routine
				m_owner->Send(ComponentMessage::START_LOCKED_CHARGE);
				m_activeState = PoolStates::STATE_LOCKED_CHARGE;
			}
		}
		case STATE_LOCKED_CHARGE:
		{
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			*occ->m_pitch = 0.3f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 4.5f;

			if ((abs(*m_wPitch) < 45) && (abs(*m_wRoll) < 45)){
				m_owner->Send(ComponentMessage::WIIMOTE_BALANCED);
				if (*m_swing < -0.8f){
					//@We comitted to a shot
					m_owner->Send(ComponentMessage::START_COMMIT_CHARGING);
					m_activeState = PoolStates::STATE_COMMIT_CHARGING;
				}
			}
			else {
				//Send message to balance wiimote
				m_owner->Send(ComponentMessage::WIIMOTE_UNBALANCED);
			}
		}
		break;
		default:
		break;
	}
}
//You are a wizard
//Get state list for wizards
std::vector<LogicComponent *> PoolStateComponent::GetLogicComponents(){
	//Get list of logic components in GO
	std::vector<LogicComponent*> logicCompList;
	for(u16 i = 0; i < m_owner->m_components.size(); i++){
		LogicComponent * logicComp = dynamic_cast<LogicComponent *>(m_owner->m_components[i]);
		if (logicComp) 
			if (logicComp != (LogicComponent*)this)logicCompList.push_back(logicComp);
	}
	return logicCompList;
};

bool PoolStateComponent::Receive(ComponentMessage msg){
	bool returned = false;
	switch (msg){
		case ComponentMessage::START_LOCKED_DIRECTION:
		{
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			m_constrainedYaw = *(occ->m_yaw);//Could get it directly from graphic system
			m_backMotion = 0;
			m_lateralMotion = 0;
			returned = true;
		}
		break;
		case ComponentMessage::START_COMMIT_CHARGING:
		{
			m_backMotion = 0;
			m_lateralMotion = 0;
			returned = true;
		}
		default:
		break;
	}
	return returned;
}
//You are a wizard