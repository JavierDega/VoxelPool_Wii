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
	for (Component * comp : m_components) delete comp;
	m_components.clear();
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
OrbitCameraComponent * GameObject::FindOrbitCameraComponent(){
	//@For whoever needs it's data
	//Iterate through components, find OrbitCameraComponent through i.e dynamic_casts
	for (u16 i = 0; i < m_components.size(); i++){
		//Dynamic casting to identify type;
		OrbitCameraComponent * orbitCamComp = dynamic_cast< OrbitCameraComponent * >(m_components[i]);
		if (orbitCamComp)return orbitCamComp;//We return the first one found (Could be active/inactive)
	}
	return nullptr;
}
PoolStateComponent * GameObject::FindPoolStateComponent(){
	//@Same as above
	for (u16 i = 0; i < m_components.size(); i++){
		//Dynamic cast
		PoolStateComponent * poolStateComp = dynamic_cast<PoolStateComponent *>(m_components[i]);
		if (poolStateComp) return poolStateComp;//We return the first one found
	}
	return nullptr;
}
RigidbodyComponent * GameObject::FindRigidbodyComponent(){
	for (u16 i = 0; i < m_components.size(); i++){
		//@Dynamic cast
		RigidbodyComponent * rbComp = dynamic_cast<RigidbodyComponent *>(m_components[i]);
		if (rbComp) return rbComp;//@Return first one found
	}
	return nullptr;
}
//Refresh addresses //NOT NEEDED DUE TO HEAP ALLOCATED POINTERS APPROACH
/*
void GameObject::RefreshComponentAddresses(){
	//@
	for(Component * comp : m_components){
		comp->m_owner = this;
	}
}*/

