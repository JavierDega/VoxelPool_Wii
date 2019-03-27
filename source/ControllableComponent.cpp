#include "Component/ControllableComponent.h"

ControllableComponent::ControllableComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp,
 u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp)
	: m_buttonsHeld(buttonsHeld), m_buttonsDown(buttonsDown), m_buttonsUp(buttonsUp), 
	m_wButtonsHeld(wButtonsHeld), m_wButtonsDown(wButtonsDown), m_wButtonsUp(wButtonsUp)
{

};
ControllableComponent::~ControllableComponent(){
	//@The actual values are held inside the PadSystem
	m_buttonsHeld = nullptr;
	m_buttonsDown = nullptr;
	m_buttonsUp = nullptr;
	m_wButtonsHeld = nullptr;
	m_wButtonsDown = nullptr;
	m_wButtonsUp = nullptr;
	delete m_buttonsHeld;
	delete m_buttonsDown;
	delete m_buttonsUp;
	delete m_wButtonsHeld;
	delete m_wButtonsDown;
	delete m_wButtonsUp;
};