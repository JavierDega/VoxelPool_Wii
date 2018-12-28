#include "Component/FontComponent.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

//Constructor
FontComponent::FontComponent(GameObject * owner, std::wstring text, GXColor textColor)
	: Component( owner ), m_text(text), m_color(textColor)
{
	//Init font
	//Font
	m_font = FreeTypeGX(GX_TF_IA8, GX_VTXFMT0);
	//After it draws, it resets to compatibility mode
	m_font.setCompatibilityMode(FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE
	| FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT);//MODULATE AND TEX DIRECT
	FT_UInt fontSize = 15;
	//Optimize font loading from buffer, just like with MeshComponents?
	m_font.loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, fontSize, false);	// Initialize the font system with the font parameters from rursus_compact_mono_ttf.h
}
//Destructor
FontComponent::~FontComponent(){

	
}