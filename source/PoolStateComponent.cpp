#include "Component/PoolStateComponent.h"
#include "Component/OrbitCameraComponent.h"
#include "Component/ShootControllerComponent.h"
#include "GameObject.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "System/PadSystem.h"

using namespace std;

PoolStateComponent::PoolStateComponent()
{
	m_activeState = STATE_LOOKING;
	m_playerTurn = false;
};
PoolStateComponent::~PoolStateComponent(){

}
void PoolStateComponent::OnStart(){

	GraphicSystem * gs = GraphicSystem::GetInstance();
	PadSystem * ps = PadSystem::GetInstance();
	//@Add a Pan camera component
	m_owner->AddComponent(new OrbitCameraComponent( &gs->m_cam, &gs->m_look, &gs->m_pitch, &gs->m_yaw, &ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp ));
	m_owner->AddComponent(new FontComponent(L"Waiting for turn...", guVector{ -175, 200, 0}, GXColor{ 100, 250, 100, 200 }, 1, true, true));
	m_owner->AddComponent(new FontComponent(L"P1: Balls left", guVector{ -300, -200, 0}, GXColor{ 250, 100, 100, 250 }, 1, true, true));
	m_owner->AddComponent(new FontComponent(L"P2: Balls left", guVector{ 0, -200, 0}, GXColor{ 100, 100, 250, 250 }, 1, true, true));
	//@Starts disabled
	m_owner->AddComponent(new ShootControllerComponent( &ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));
}
void PoolStateComponent::ComputeLogic(float dt){

	switch (m_activeState){
		case STATE_LOOKING:
		{
			ObjectSystem * os = ObjectSystem::GetInstance();
			vector <RigidbodyComponent*> rigidbodies = os->GetRigidbodyComponentList();
			bool allSleeping = true;
			for(RigidbodyComponent * rigidbody : rigidbodies){
				if (rigidbody->m_isSleeping == false) allSleeping = false;
			}
			if (allSleeping){
				m_playerTurn ^= 1;
				(m_playerTurn) ? (m_owner->Send(ComponentMessage::PLAYER2_TURN)) : (m_owner->Send(ComponentMessage::PLAYER1_TURN));
				m_owner->Send(ComponentMessage::ENABLE_SHOOT)
				m_activeState = PoolStates::STATE_NEXT_TURN;
			}
		}
		break;
		case STATE_NEXT_TURN:
		{

		}
		break;
		default:
		break;
	}
}
void PoolStateComponent::ChangeState(PoolStates newState){

}
//Get state list
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