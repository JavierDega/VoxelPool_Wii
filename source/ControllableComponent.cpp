#include "Component/ControllableComponent.h"

ControllableComponent::ControllableComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp,
 u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp, float * swing, float * pitch, float * deviation, float * roll)
	: m_buttonsHeld(buttonsHeld), m_buttonsDown(buttonsDown), m_buttonsUp(buttonsUp), 
	m_wButtonsHeld(wButtonsHeld), m_wButtonsDown(wButtonsDown), m_wButtonsUp(wButtonsUp), 
	m_swing(swing), m_wPitch(pitch), m_deviation(deviation), m_wRoll(roll)
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
	m_swing = nullptr;
	m_wPitch = nullptr;
	m_deviation = nullptr;
	m_wRoll = nullptr;
	delete m_buttonsHeld;
	delete m_buttonsDown;
	delete m_buttonsUp;
	delete m_wButtonsHeld;
	delete m_wButtonsDown;
	delete m_wButtonsUp;
	delete m_swing;
	delete m_wPitch;
	delete m_deviation;
	delete m_wRoll;
};