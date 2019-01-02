#include "System/PadSystem.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"

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
}
//Destructor
PadSystem::~PadSystem(){
	m_buttonsHeld = 0;
	m_buttonsUp = 0;
	m_buttonsDown = 0;
}	
//Init
void PadSystem::Initialize() {
	PAD_Init();
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
	
	//Default input 
	/*if ( m_buttonsHeld & PAD_BUTTON_LEFT ){
		gs->m_cam.x--;
		gs->m_look.x--;
	}
	if ( m_buttonsHeld & PAD_BUTTON_RIGHT ){
		gs->m_cam.x++;
		gs->m_look.x++;
	}
	if ( m_buttonsHeld & PAD_BUTTON_UP ){
		gs->m_cam.y++;
		gs->m_look.y++;
	}
	if ( m_buttonsHeld & PAD_BUTTON_DOWN ){
		gs->m_cam.y--;
		gs->m_look.y--;
	}
	if ( m_buttonsHeld & PAD_BUTTON_A ){
		gs->m_cam.z++;
		gs->m_look.z++;
	}
	if ( m_buttonsHeld & PAD_BUTTON_B ){
		gs->m_cam.z--;
		gs->m_look.z--;
	}*/
	if ( m_buttonsDown & PAD_BUTTON_X){
		gs->m_debug = !gs->m_debug;
	}

	//Update logic components
	std::vector <LogicComponent *> logicComponents = os->GetLogicComponentList();
	for (u16 i = 0; i < logicComponents.size(); i++){
		logicComponents[i]->ComputeLogic();
	}
}
//Scan
void PadSystem::ScanPads(int controller) {
	PAD_ScanPads();
	m_buttonsHeld = PAD_ButtonsHeld(controller);
	m_buttonsDown = PAD_ButtonsDown(controller);
	m_buttonsUp = PAD_ButtonsUp(controller);
}