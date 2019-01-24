#include "Component/FontComponent.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

//Constructor
FontComponent::FontComponent(std::wstring text, guVector screenPos, GXColor textColor, float offsetScale, bool rotate)
	: m_text(text), m_screenPos(screenPos), m_color(textColor), m_offsetScale(offsetScale), m_rotate(rotate)
{
	//Data
}
//Destructor
FontComponent::~FontComponent(){

	
}