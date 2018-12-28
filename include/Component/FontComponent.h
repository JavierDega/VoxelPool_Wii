#ifndef FONTCOMPONENT_H_
#define FONTCOMPONENT_H_

#include "Component/Component.h"
#include "FreeTypeGX.h"
#include <gccore.h>
#include <string>

//Model class
class FontComponent : public Component{
public:
	//Constructor
	FontComponent(GameObject * owner, std::wstring text = L"Default Text", GXColor textColor = GXColor{0, 0, 0, 255});
	virtual ~FontComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );
	
	FreeTypeGX m_font;
	std::wstring m_text;
	GXColor m_color;
};
#endif /*FONTCOMPONENT_H_*/