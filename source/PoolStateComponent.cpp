#include "Component/PoolStateComponent.h"
#include "Component/OrbitCameraComponent.h"
#include "Component/BackToMenuComponent.h"
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
	m_redExtraTurn = false;
	m_blueExtraTurn = false;
	//@Accel delta
	m_backMotion = 0;
	m_lateralMotion = 0;
	m_lerpDelta = 0;
	m_lerpStart = Math::VecZero;
	m_lerpEnd = Math::VecZero;
	m_redBalls = 5;
	m_blueBalls = 5;
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
	m_owner->AddComponent(new FontComponent(L"P1: Balls left: " + to_wstring(m_redBalls), guVector{ -300, -200, 0}, GXColor{ 250, 100, 100, 250 }, 3, true, true));
	m_owner->AddComponent(new FontComponent(L"P2: Balls left: " + to_wstring(m_blueBalls), guVector{ 0, -200, 0}, GXColor{ 100, 100, 250, 250 }, 3, true, true));
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
			*occ->m_pitch = 0.35f;//Constrains pitch and zoom
			occ->m_zoom = 6.0f;

			guVector lookToCam;
			guVecSub( occ->m_cam, occ->m_look, &lookToCam);
			guVecScale( &lookToCam, &lookToCam, 1.2f);
			lookToCam.y = -0.75;

			guVecAdd( &occ->m_orbitOrigin, &lookToCam, &m_owner->m_transform.m_position);
			m_owner->m_transform.m_rotation = Math::QuatFromAxisAngle( guVector{ 0, -1, 0 }, *occ->m_yaw + 1.57);

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
			*occ->m_pitch = 0.35f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 6.5f;

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
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			*occ->m_pitch = 0.35f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 6.5f;	
			//@Lerp
			m_lerpDelta += dt;
			m_lerpDelta = min(m_lerpDelta, 1.f);
			m_owner->m_transform.m_position = Math::VectorLerp( m_lerpStart, m_lerpEnd, m_lerpDelta);

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
			*occ->m_pitch = 0.35f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 6.5f;

			if ((abs(*m_wPitch) < 45) && (abs(*m_wRoll) < 45)){
				m_owner->Send(ComponentMessage::WIIMOTE_BALANCED);
				if (*m_swing > 0.8f){
					//@We comitted to a shot
					m_owner->Send(ComponentMessage::START_COMMIT_SHOOTING);
					m_activeState = PoolStates::STATE_COMMIT_SHOOTING;
				}
			}
			else {
				//Send message to balance wiimote
				m_owner->Send(ComponentMessage::WIIMOTE_UNBALANCED);
			}
		}
		break;
		case STATE_COMMIT_SHOOTING:
		{
			//@We keep on charging
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			*occ->m_pitch = 0.35f;
			*occ->m_yaw = m_constrainedYaw;
			occ->m_zoom = 6.5f;

			//@Lerp
			m_lerpDelta += dt;
			m_lerpDelta = min(m_lerpDelta, 1.f);
			m_owner->m_transform.m_position = Math::VectorLerp( m_lerpStart, m_lerpEnd, m_lerpDelta);

			//@Store highest lateral delta
			if (abs(*m_deviation) > abs(m_lateralMotion)){
				m_lateralMotion = *m_deviation;
			}
			if (*m_swing <= 0 || abs(*m_wPitch >= 45) || abs(*m_wRoll >= 45)){
				//@Finish routine
				//@Shoot white ball in the right direction
				m_owner->Send(ComponentMessage::START_LOOKING);
				m_activeState = PoolStates::STATE_LOOKING;

				RigidbodyComponent * whiteBallRb = ObjectSystem::GetInstance()->FindObjectByName("White_Ball")->FindRigidbodyComponent();

				float deviationDegrees = *m_deviation*2.f*3.1416f/180.f * 10.f;
				guVector shootVector = Math::EulerToDirection(guVector{0, *occ->m_yaw + deviationDegrees, 0 });
				guVecScale(&shootVector, &shootVector, -10*abs(m_backMotion));
				whiteBallRb->m_velocity = shootVector;
				whiteBallRb->m_isSleeping = false;
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
		case ComponentMessage::RED_WIN:
		{
			//m_owner->m_isDeleted = true;
			//@Create a mesh ,screen space font and menu to go back to start.
			m_isActive = false;
			GameObject * redPlayer = new GameObject("Red_Player", guVector{ 0, -1.5, 0 }, Math::QuatIdentity, guVector{ 0.5, 0.5, 0.5 });
			redPlayer->AddComponent(new MeshComponent("chr_red"));
			redPlayer->AddComponent(new FontComponent(L"Player red wins!", guVector{-150, 0, 0 }, GXColor{ 255, 0, 0, 255 }, 3, false, true));
			redPlayer->AddComponent ( new BackToMenuComponent(m_buttonsHeld, m_buttonsDown, m_buttonsUp, m_wButtonsHeld, m_wButtonsDown,
			 m_wButtonsUp, m_swing, m_wPitch, m_deviation, m_wRoll));
			ObjectSystem::GetInstance()->AddObject(redPlayer);
		}
		break;
		case ComponentMessage::BLUE_WIN:
		{
			m_isActive = false;
			GameObject * bluePlayer = new GameObject("Blue_Player", guVector { 0, -1.5, 0 }, Math::QuatIdentity, guVector { 0.5, 0.5, 0.5 });
			bluePlayer->AddComponent(new MeshComponent("chr_blue"));
			bluePlayer->AddComponent( new FontComponent(L"Player blue wins!", guVector{ -150, 0, 0 }, GXColor{ 0, 0, 255, 255 }, 3, false, true ));
			bluePlayer->AddComponent ( new BackToMenuComponent(m_buttonsHeld, m_buttonsDown, m_buttonsUp, m_wButtonsHeld, m_wButtonsDown,
			 m_wButtonsUp, m_swing, m_wPitch, m_deviation, m_wRoll));
			ObjectSystem::GetInstance()->AddObject(bluePlayer);
		}
		break;
		case ComponentMessage::WHITE_IN_POT:
		{
			if (m_playerTurn){
				//@Blue turn, give redExtraTurn
				m_redExtraTurn = true;
				m_blueExtraTurn = false;//@Cancels any extra shots we had
			}
			else{
				//@Red turn, give blueExtraTurn
				m_blueExtraTurn = true;
				m_redExtraTurn = false;//@Cancel extra shots
			}	
		}
		break;
		case ComponentMessage::PLAYER_RED_SCORED:
		{
			//If it's red's turn, add extra shot, otherwise, do nothing.
			m_redBalls --;
			if (m_redBalls  == 0) m_owner->Send(ComponentMessage::RED_WIN);
			if (m_playerTurn){
				//@Blue
			}
			else {
				//@Red turn
				m_redExtraTurn = true;
			}
			//Reduce remaining ball counter and display on FontComponent
		}
		break;
		case ComponentMessage::PLAYER_BLUE_SCORED:
		{
			m_blueBalls --;
			if (m_blueBalls == 0) m_owner->Send(ComponentMessage::BLUE_WIN);
			if (m_playerTurn){
				//@Blue turn
				m_blueExtraTurn = true;
			}
			else{
				//@Red turn
			}
		}
		break;
		case ComponentMessage::START_LOOKING:
		{
			m_owner->m_transform.m_position = guVector{ 6.5, -0.5, -7.5};
			m_owner->m_transform.m_rotation =  Math::QuatIdentity;
		}
		break;
		case ComponentMessage::START_ALL_SLEEPING:
		{	
			ObjectSystem * os = ObjectSystem::GetInstance();
			if (m_playerTurn){
				if (m_blueExtraTurn){
					m_blueExtraTurn = false;
				}
				else m_playerTurn ^= 1;
			}
			else {
				//@Red player's turn
				if (m_redExtraTurn){
					m_redExtraTurn = false;
				}
				else m_playerTurn ^= 1;
			}
			//@If there's no White_Ball, spawn it
			if (os->FindObjectByName("White_Ball") == nullptr){
				GameObject * ball3 = new GameObject("White_Ball", guVector { -5, -1.0, 0 }, Math::QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
				ball3->AddComponent( new MeshComponent( "pool_ball_white" ));
				ball3->AddComponent( new RigidbodyComponent( 0.5f, 1.0f, false, false, BallType::BALL_NONE ) );

				os->AddObject(ball3);
			}//@else do nothing
		}
		break;
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

			//@Start and end of lerp
			m_lerpDelta = 0;
			m_lerpStart = m_owner->m_transform.m_position;
			OrbitCameraComponent * occ = m_owner->FindOrbitCameraComponent();
			guVector lookToCam;
			guVecSub( occ->m_cam, occ->m_look, &lookToCam);
			guVecAdd( &m_lerpStart, &lookToCam, &m_lerpEnd);
		}
		break;
		case ComponentMessage::START_COMMIT_SHOOTING:
		{
			//@Flip lerp
			guVector m_newStart = m_lerpStart;
			m_lerpStart = m_lerpEnd;
			m_lerpEnd = m_newStart;
			//@Reset delta
			m_lerpDelta = 1 - m_lerpDelta;
		}
		break;
		default:
		break;
	}
	return returned;
}
//You are a wizard