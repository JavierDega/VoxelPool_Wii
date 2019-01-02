#include "GameObject.h"
#include "System/ObjectSystem.h"

//Constructor
GameObject::GameObject()
	: m_transform(guVector{ 0, 0, 0 })
{
	
}
GameObject::GameObject(guVector position)
	: m_transform(position)
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
}

