#include "GameObject.h"
#include "System/ObjectSystem.h"

//Constructor
GameObject::GameObject()
	: m_transform(this)
{
	
}
//Destructor
GameObject::~GameObject()
{

}
//AddComp
void GameObject::AddComponent( Component component ){
	//We add the component to the vector, and we set reference (Just in case)
	component.m_owner = this;
	m_components.push_back(component);
}
//Init
void GameObject::Initialize(){
	//What do? Add GameObject reference to the Object Factory singleton
	ObjectSystem::GetInstance()->AddObject( this );
}