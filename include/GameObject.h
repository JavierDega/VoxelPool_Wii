#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>

#include "Component.h"

class TransformComponent;
class GameObject{
public:
	//Functions
	void AddComponent(Component);
	virtual void Update(float dt);
	//Messages
	//virtual void Send(ComponentMessage * msg);
	virtual Component * FindComponent(ComponentType type);

	//Variables
	//All gameobjects have a transform component
	TransformComponent m_transform;
	//Cache coherency avoiding 'new'
	std::vector<Component> m_components;


}
#endif /*GAMEOBJECT_H_*/