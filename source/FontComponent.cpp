#include "Component/FontComponent.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

//Constructor
FontComponent::FontComponent(std::wstring text, GXColor textColor, guVector screenPos)
	: m_text(text), m_color(textColor), m_screenPos(screenPos)
{
	//Data
}
//Destructor
FontComponent::~FontComponent(){

	
}