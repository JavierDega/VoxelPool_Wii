#ifndef COMPONENT_H_
#define COMPONENT_H_

enum ComponentMessage {
	BALL_IN_POT,
	MSG_02
};
class GameObject;
class Component{
public:
	//USE DYNAMIC CASTS FOR TYPE IDENTIFICATION?
	Component();
	virtual ~Component();
	//@Messaging how to use them?
	virtual bool Receive (ComponentMessage msg) = 0;

	//Variables
	GameObject * m_owner;
};
#endif /*COMPONENT_H_*/