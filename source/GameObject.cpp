#include "GameObject.h"
#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"

using namespace std;

//Constructor
GameObject::GameObject( std::string name, guVector position, guQuaternion rotation, guVector scale )
	: m_name(name), m_transform(position, rotation, scale)
{
	m_isDeleted = false;
}
//Destructor
GameObject::~GameObject()
{
	//empty component vector
	while (!m_components.empty()){
		Component * curComp = m_components.back();
		delete curComp;
		m_components.pop_back();
	}
}
//AddComp
void GameObject::AddComponent( Component * component ){
	//We add the component to the vector, and we set reference (Just in case)
	component->m_owner = this;
	m_components.push_back(component);
}
void GameObject::Send(ComponentMessage msg){
	for (u16 i = 0; i < m_components.size(); i++){
		
		m_components[i]->Receive(msg);//@Receive returns boolean stating whether message was received or not.
	}
}
//Refresh addresses //NOT NEEDED
/*
void GameObject::RefreshComponentAddresses(){
	//@
	for(Component * comp : m_components){
		comp->m_owner = this;
	}
}*/

