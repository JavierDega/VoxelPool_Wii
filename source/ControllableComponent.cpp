#include "Component/ControllableComponent.h"

ControllableComponent::ControllableComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp)
	: m_buttonsHeld(buttonsHeld), m_buttonsDown(buttonsDown), m_buttonsUp(buttonsUp)
{

};
ControllableComponent::~ControllableComponent(){
	m_buttonsHeld = nullptr;
	m_buttonsDown = nullptr;
	m_buttonsUp = nullptr;
	delete m_buttonsHeld;
	delete m_buttonsDown;
	delete m_buttonsUp;
};