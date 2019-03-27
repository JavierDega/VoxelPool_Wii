#include "System/PadSystem.h"
#include "System/ObjectSystem.h"
#include "System/PhysicSystem.h"
#include "System/GraphicSystem.h"

using namespace std;

//Instance
PadSystem * PadSystem::m_instance = NULL;
PadSystem * PadSystem::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new PadSystem();
	}
	return m_instance;
}
//Constructor
PadSystem::PadSystem() {
	m_buttonsHeld = 0;
	m_buttonsUp = 0;
	m_buttonsDown = 0;

	m_wButtonsHeld = 0;
	m_wButtonsUp = 0;
	m_wButtonsDown = 0;

	//INPUT
	PAD_Init();
	WPAD_Init();
	WPAD_SetVRes(0, 640, 480);
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR); 
}
//Destructor
PadSystem::~PadSystem(){
	m_buttonsHeld = 0;
	m_buttonsUp = 0;
	m_buttonsDown = 0;
}	
//Init
void PadSystem::Initialize() {
	//Initialize LogicComponents;
	std::vector <LogicComponent *> logicComponents = ObjectSystem::GetInstance()->GetLogicComponentList();
	for (u16 i = 0; i < logicComponents.size(); i++){
		logicComponents[i]->OnStart();
	}
}
//Update
void PadSystem::Update( float dt ){
	//Scan input
	ScanPads(0);

	//Systems it may interact with:
	GraphicSystem * gs = GraphicSystem::GetInstance();
	ObjectSystem * os = ObjectSystem::GetInstance();
	PhysicSystem * ps = PhysicSystem::GetInstance();
	
	std::vector <LogicComponent *> logicComponents = os->GetLogicComponentList();
	
	//@Generic input
	if ( m_wButtonsDown & WPAD_BUTTON_1){
		gs->m_debug = !gs->m_debug;
	}
	if ( m_wButtonsDown & WPAD_BUTTON_2 ){
		ps->m_stepMode = !ps->m_stepMode;
	}
	if ( m_wButtonsDown & WPAD_BUTTON_HOME ){
		ps->m_stepOnce = true;
	}

	//@Debug logs
	if ( m_wButtonsHeld & WPAD_BUTTON_LEFT){
		gs->AddLog("Left button is being held");
	}
	if (m_wButtonsDown & WPAD_BUTTON_LEFT){
		gs->AddLog("Left button was just pressed");
	}
	if ( m_wButtonsHeld & WPAD_BUTTON_RIGHT){
		gs->AddLog("Right button is being held");
	}
	if (m_wButtonsDown & WPAD_BUTTON_RIGHT){
		gs->AddLog("Right button was just pressed");
	}

	//@Update logic components
	for (u16 i = 0; i < logicComponents.size(); i++){
		LogicComponent * logic = logicComponents[i];
		logic->ComputeLogic(dt);
	}
}
//@Messaging
void PadSystem::SendMessage(ComponentMessage msg){
	//@Catch Player_Scored message
	if (msg == ComponentMessage::PLAYER_SCORED){
		//Get all logic components, find the one that's the player controller
		
	}
}
//Utility
//Scan
void PadSystem::ScanPads(int controller) {

	GraphicSystem * gs = GraphicSystem::GetInstance();

	PAD_ScanPads();
	WPAD_ScanPads();
	m_buttonsHeld = PAD_ButtonsHeld(controller);
	m_buttonsDown = PAD_ButtonsDown(controller);
	m_buttonsUp = PAD_ButtonsUp(controller);

	m_wButtonsHeld = WPAD_ButtonsHeld(controller);
	m_wButtonsDown = WPAD_ButtonsDown(controller);
	m_wButtonsUp = WPAD_ButtonsUp(controller);

	vec3w_t accel = vec3w_t{0,0,0};
	gforce_t gforce = gforce_t{ 0, 0, 0 };
	WPAD_Accel(0, &accel);
	WPAD_GForce(0, &gforce);
	string accel_log = "Accelerometer: " + to_string(accel.x) + " " + to_string(accel.y) + " " + to_string(accel.z);
	string gforce_log = "GForce: " + to_string(gforce.x) + " " + to_string(gforce.y) + " " + to_string(gforce.z);
	gs->AddLog(accel_log);
	gs->AddLog(gforce_log);
}