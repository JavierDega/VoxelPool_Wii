#include "Component/LogicComponent.h"

LogicComponent::LogicComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp)
	: m_buttonsHeld(buttonsHeld), m_buttonsDown(buttonsDown), m_buttonsUp(buttonsUp)
{

};
LogicComponent::~LogicComponent(){

};