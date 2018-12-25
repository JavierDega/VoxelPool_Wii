#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_


#include "Component/Component.h"
#include "Component/TransformComponent.h"
#include <vector>
class GameObject{
public:
	//Functions
	void AddComponent( Component component );
	//Messages
	//virtual void Send(ComponentMessage * msg);
	//virtual Component * FindComponent(ComponentType type);
	void Initialize();
	//Variables
	//All gameobjects have a transform component
	TransformComponent m_transform;
	//Cache coherency avoiding 'new'
	std::vector<Component> m_components;
};
#endif /*GAMEOBJECT_H_*/