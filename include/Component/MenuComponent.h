#ifndef MENUSELECTOR_H_
#define MENUSELECTOR_H_

#include "Component/ControllableComponent.h"
#include "Component/FontComponent.h"
#include <vector>
#include <gccore.h>

//Iterates through font components, at a certain offset, logging the current selector, and doing some behaviour when clicked
class MenuComponent : public ControllableComponent{
public:
	//Constructor
	MenuComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp);
	virtual ~MenuComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	std::vector<FontComponent*> GetMenuFonts();
	//void OnDestroy()?
	//Messaging
	//virtual bool Receive( ComponentMessage * msg );

	//Variables
	u16 m_option;
	guVector m_screenPos;
};
#endif /*MENUSELECTOR_H_*/