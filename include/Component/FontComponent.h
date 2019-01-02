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
	FontComponent( std::wstring text = L"Default Text", GXColor textColor = GXColor{0, 0, 0, 255}, guVector screenPos = guVector{ 0, 0, 0 } );
	virtual ~FontComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );
	std::wstring m_text;
	GXColor m_color;
	guVector m_screenPos;
};
#endif /*FONTCOMPONENT_H_*/