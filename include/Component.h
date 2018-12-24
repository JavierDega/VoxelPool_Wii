#ifndef COMPONENT_H_
#define COMPONENT_H_

class GameObject;
class Component{
protected:
	//USE DYNAMIC CASTS FOR TYPE IDENTIFICATION?
	Component(GameObject * owner)
		: m_owner(owner) {}
public:
	virtual ~Component(){};
	//Messaging
	//virtual bool Receive (ComponentMessage * msg) = 0;

	//Variables
	GameObject * m_owner;
};
#endif /*COMPONENT_H_*/