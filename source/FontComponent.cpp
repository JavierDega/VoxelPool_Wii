#include "Component/FontComponent.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

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
		case ComponentMessage::PLAYER1_TURN:
		{
			//@Check we're the right font component
			if (m_text.compare(L"Waiting for turn...") == 0){
				//We're the right screenSpace UI element
				m_text = L"Press A for player one's turn";
			}
		}
		break;
		case ComponentMessage::PLAYER2_TURN:
		{
			//@Check we're the right font component
			if (m_text.compare(L"Waiting for turn...") == 0){
				//We're the right screenSpace UI element
				m_text = L"Press A for player two's turn";
			}
		}
		default:
		break;
	}

	return returned;
}