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

	//INPUT
	PAD_Init();
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
	
	if ( m_buttonsDown & PAD_BUTTON_X){
		gs->m_debug = !gs->m_debug;
	}

	//Update logic components
	std::vector <LogicComponent *> logicComponents = os->GetLogicComponentList();
	for (u16 i = 0; i < logicComponents.size(); i++){
		logicComponents[i]->ComputeLogic(dt);
	}
}
//Scan
void PadSystem::ScanPads(int controller) {
	PAD_ScanPads();
	m_buttonsHeld = PAD_ButtonsHeld(controller);
	m_buttonsDown = PAD_ButtonsDown(controller);
	m_buttonsUp = PAD_ButtonsUp(controller);
}