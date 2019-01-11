#include "GameObject.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"

using namespace std;

//Constructor
GameObject::GameObject( std::string name, guVector position )
	: m_name(name), m_transform(position)
{

}
//Destructor
GameObject::~GameObject()
{

}
//AddComp
void GameObject::AddComponent( Component * component ){
	//We add the component to the vector, and we set reference (Just in case)
	component->m_owner = this;
	m_components.push_back(component);

	//@Print obj address: GraphicSystem::GetInstance()->AddLog("Obj Addr: " + to_string((int)this));
}
//Refresh addresses
void GameObject::RefreshComponentAddresses(){
	//@
	for(u16 i = 0 ; i < m_components.size(); i++){
		m_components[i]->m_owner = this;
	}


}

