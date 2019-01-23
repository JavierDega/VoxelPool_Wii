#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Component/Component.h"
#include "Component/TransformComponent.h"
#include "Extra/Math.h"
#include <string>
#include <vector>
class GameObject{
public:
	GameObject(std::string name = "Default name" , guVector position = guVector { 0, 0, 0 }, guQuaternion rotation = Math::QuatIdentity,
			guVector scale = guVector{ 1, 1, 1 });
	~GameObject();
	//Functions
	void AddComponent( Component * component );
	//Messages
	void Send(ComponentMessage msg);
	//virtual Component * FindComponent(ComponentType type);
	void RefreshComponentAddresses();
	
	//Variables
	std::string m_name;
	//All gameobjects have a transform component
	TransformComponent m_transform;
	//Cache coherency avoiding 'new'
	std::vector<Component *> m_components;
};
#endif /*GAMEOBJECT_H_*/