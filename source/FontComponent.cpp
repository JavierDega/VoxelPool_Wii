#include "Component/FontComponent.h"
#include "GameObject.h"

#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

using namespace std;

//Constructor
FontComponent::FontComponent(std::wstring text, guVector screenPos, GXColor textColor, float offsetScale, bool rotate, bool isScreenSpace)
	: m_text(text), m_screenPos(screenPos), m_color(textColor), m_offsetScale(offsetScale), m_rotate(rotate), m_isScreenSpace(isScreenSpace)
{
	//Data
}
//Destructor
FontComponent::~FontComponent(){

	
}
//@Messaging
bool FontComponent::Receive(ComponentMessage msg){
	bool returned = false;
	switch (msg){
		case ComponentMessage::PLAYER_RED_SCORED:
		{
			if (m_text.find(L"P1") != wstring::npos ){
				m_text = L"P1: Balls left: " + to_wstring(m_owner->FindPoolStateComponent()->m_redBalls);
			}
		}
		break;
		case ComponentMessage::PLAYER_BLUE_SCORED:
		{
			if (m_text.find(L"P2") != wstring::npos ){
				m_text = L"P2: Balls left: " + to_wstring(m_owner->FindPoolStateComponent()->m_blueBalls);
			}
		}
		break;
		case ComponentMessage::START_ALL_SLEEPING:
		{
			//@Check we're the right font component
			if (m_text.compare(L"Waiting for turn...") == 0){
				//We're the right screenSpace UI element
				m_text = (m_owner->FindPoolStateComponent()->m_playerTurn) ?  L"A for player 2 turn" : L"A for player 1 turn";
			}
		}
		break;
		case ComponentMessage::START_AIMING:
		{
			if ((m_text.compare(L"A for player 2 turn") == 0) || (m_text.compare(L"A for player 1 turn") == 0)){
				m_text = L"A to lock direction";
			}
		}
		break;
		case ComponentMessage::START_LOCKED_DIRECTION:
		{
			if (m_text.compare(L"A to lock direction") == 0)
			{
				m_text = L"Swing back to charge shot";
			}
		}
		break;
		case ComponentMessage::START_COMMIT_CHARGING:
		{
			if ((m_text.compare(L"Swing back to charge shot") == 0) || (m_text.compare(L"Swing to shoot") == 0)){
				m_text = L"Keep charging..";
			}
		}
		break;
		case ComponentMessage::WIIMOTE_BALANCED:
		{
			if (m_text.compare(L"Wiimote off balance!") == 0){
				m_text = L"Swing to shoot";
			}
		}
		break;
		case ComponentMessage::WIIMOTE_UNBALANCED:
		{
			if ((m_text.compare(L"Swing back to charge shot") == 0) || 
				(m_text.compare(L"Swing forward to shoot!") == 0) || (m_text.compare(L"Swing to shoot") == 0) ){
				m_text = L"Wiimote off balance!";
			}//else its probably already displaying this text
		}
		break;
		case ComponentMessage::START_LOCKED_CHARGE:
		{
			if (m_text.compare(L"Keep charging..") == 0){
				m_text = L"Swing forward to shoot!";
			}
		}
		break;
		case ComponentMessage::START_COMMIT_SHOOTING:
		{
			if ((m_text.compare(L"Swing forward to shoot!") == 0) || (m_text.compare(L"Swing to shoot") == 0)){
				m_text = L"Keep shooting..";
			}
		}
		break;
		case ComponentMessage::START_LOOKING:
		{
			if (m_text.compare(L"Keep shooting..") == 0){
				m_text = L"Waiting for turn...";
			}
		}
		break;
		default:
		break;
	}

	return returned;
}