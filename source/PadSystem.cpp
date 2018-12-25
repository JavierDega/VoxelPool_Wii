#include "System/PadSystem.h"


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
}
//Update
void PadSystem::Update( float dt ){
	//Scan input
	ScanPads(0);
	//React to input?
}
//Scan
void PadSystem::ScanPads(int controller) {
	PAD_ScanPads();
	m_buttonsHeld = PAD_ButtonsHeld(controller);
	m_buttonsDown = PAD_ButtonsDown(controller);
	m_buttonsUp = PAD_ButtonsUp(controller);
}