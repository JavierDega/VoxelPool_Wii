#ifndef COMPONENT_H_
#define COMPONENT_H_

enum ComponentMessage {
	RED_WIN,
	BLUE_WIN,
	WHITE_IN_POT,
	PLAYER_RED_SCORED,
	PLAYER_BLUE_SCORED,
	//@POOL SHOOTING ROUTINE
	START_LOOKING,
	START_ALL_SLEEPING,
	START_AIMING,
	START_LOCKED_DIRECTION,
	START_COMMIT_CHARGING,
	START_LOCKED_CHARGE,
	START_COMMIT_SHOOTING,
	WIIMOTE_BALANCED,
	WIIMOTE_UNBALANCED
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
	bool m_isActive;
};
#endif /*COMPONENT_H_*/