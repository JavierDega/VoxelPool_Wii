#include "PadSystem.h"


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
	buttonsHeld = 0;
	buttonsUp = 0;
	buttonsDown = 0;
}
//Destructor
PadSystem::~PadSystem(){
	buttonsHeld = 0;
	buttonsUp = 0;
	buttonsDown = 0;
}	
void PadSystem::Initialize() {
	PAD_Init();
	//WPAD_Init();
}

void PadSystem::ScanPads(int controller) {
	PAD_ScanPads();
	buttonsHeld = PAD_ButtonsHeld(controller);
	buttonsDown = PAD_ButtonsDown(controller);
	buttonsUp = PAD_ButtonsUp(controller);
}