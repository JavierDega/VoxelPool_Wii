#include "Component/FontComponent.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

//Constructor
FontComponent::FontComponent(std::wstring text, guVector screenPos, GXColor textColor)
	: m_text(text), m_screenPos(screenPos), m_color(textColor)
{
	//Data
}
//Destructor
FontComponent::~FontComponent(){

	
}