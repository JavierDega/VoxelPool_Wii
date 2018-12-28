#include "Component/FontComponent.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

//Constructor
FontComponent::FontComponent(GameObject * owner, std::wstring text, GXColor textColor)
	: Component( owner ), m_text(text), m_color(textColor)
{
	//Data
}
//Destructor
FontComponent::~FontComponent(){

	
}