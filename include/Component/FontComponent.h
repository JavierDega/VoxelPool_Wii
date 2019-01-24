#ifndef FONTCOMPONENT_H_
#define FONTCOMPONENT_H_

#include "Component/Component.h"
#include "Extra/FreeTypeGX.h"
#include <gccore.h>
#include <string>

//Model class
class FontComponent : public Component{
public:
	//Constructor
	FontComponent( std::wstring text = L"Default Text", guVector screenPos = guVector{ 0, 0, 0 }, GXColor textColor = GXColor{0, 0, 0, 255},
		float offsetScale = 1, bool rotate = false);
	virtual ~FontComponent();
	//Messaging
	virtual bool Receive( ComponentMessage msg ){ return false;};

	std::wstring m_text;
	guVector m_screenPos;
	GXColor m_color;
	float m_offsetScale;//@THIS IS WIP
	bool m_rotate;
};
#endif /*FONTCOMPONENT_H_*/