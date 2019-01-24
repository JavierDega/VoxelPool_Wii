#include "GameObject.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"

using namespace std;

//Constructor
GameObject::GameObject( std::string name, guVector position, guQuaternion rotation, guVector scale )
	: m_name(name), m_transform(position, rotation, scale)
{

}
//Destructor
GameObject::~GameObject()
{
	//empty component vector
	for (Component * comp : m_components){
		delete comp;
		//comp = nullptr;
	}
	m_components.clear();
}
//AddComp
void GameObject::AddComponent( Component * component ){
	//We add the component to the vector, and we set reference (Just in case)
	component->m_owner = this;
	m_components.push_back(component);

	//@Print obj address: GraphicSystem::GetInstance()->AddLog("Obj Addr: " + to_string((int)this));
}
void GameObject::Send(ComponentMessage msg){
	for (u16 i = 0; i < m_components.size(); i++){
		
		m_components[i]->Receive(msg);
	}
}
//Refresh addresses
void GameObject::RefreshComponentAddresses(){
	//@
	for(Component * comp : m_components){
		comp->m_owner = this;
	}
}

