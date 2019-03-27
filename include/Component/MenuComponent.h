#ifndef MENUCOMPONENT_H_
#define MENUCOMPONENT_H_

#include "Component/ControllableComponent.h"
#include "Component/FontComponent.h"
#include <vector>
#include <gccore.h>

//Iterates through font components, at a certain offset, logging the current selector, and doing some behaviour when clicked
class MenuComponent : public ControllableComponent{
public:
	//Constructor
	MenuComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp,
	 float offsetScale = 1.0f, bool rotate = false, bool isScreenSpace = false);
	virtual ~MenuComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	std::vector<FontComponent*> GetMenuFonts();
	//void OnDestroy()?
	//Messaging
	virtual bool Receive( ComponentMessage msg ){ return false;};

	//Variables
	u16 m_option;
	guVector m_screenPos;
	float m_offsetScale;
	bool m_rotate;
	bool m_isScreenSpace;
};
#endif /*MENUCOMPONENT_H_*/