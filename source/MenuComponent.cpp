#include "Component/MenuComponent.h"
#include "GameObject.h"
#include "System/ObjectSystem.h"

#include <ogc/pad.h>

//Constructor
MenuComponent::MenuComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp)
	: ControllableComponent(buttonsHeld, buttonsDown, buttonsUp)
{
	m_option = 0;
	m_screenPos = guVector{ 0, 0, 0 };
}
//Destructor
MenuComponent::~MenuComponent(){
	//@
}
//Start
void MenuComponent::OnStart(){
	
}
//Update
void MenuComponent::ComputeLogic(float dt){
	//Choose option
	ObjectSystem * os = ObjectSystem::GetInstance();

	std::vector<FontComponent*> fontComponents = GetMenuFonts();
	u16 bdown = *(m_buttonsDown);

	if (bdown & (PAD_BUTTON_LEFT | PAD_BUTTON_UP)){
		
		if(m_option == 0) m_option = fontComponents.size() - 1;
		else m_option--;

	}
	if (bdown & (PAD_BUTTON_RIGHT | PAD_BUTTON_DOWN)){
		m_option++;
		if ( m_option == fontComponents.size()) m_option = 0;
	}

	if (bdown & ( PAD_BUTTON_A )){
		switch (m_option){
			case 0:
			{
				//Start option
				os->LoadScene(1);
				break;
			}
			default:
				break;
		}

	}
	FontComponent * selectedOption = fontComponents[m_option];
	m_screenPos = selectedOption->m_screenPos;
	m_screenPos.x -= 15;
}
//GetFontList
std::vector<FontComponent *> MenuComponent::GetMenuFonts(){
	//Get list of font components, place to the left of component index m_option = 0
	std::vector<FontComponent*> fontList;
	for(u16 i = 0; i < m_owner->m_components.size(); i++){
		FontComponent * fontComp = dynamic_cast<FontComponent *>(m_owner->m_components[i]);
		if (fontComp) fontList.push_back(fontComp);
	}
	return fontList;
}
