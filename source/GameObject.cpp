#include "GameObject.h"
void GameObject::AddComponent( Component component ){
	//We add the component to the vector, and also call the function on the component that hands a reference to its system
	m_components.push_back(component);

}
void GameObject::Initialize(){
	//What do? Add GameObject reference to the Object Factory singleton

}