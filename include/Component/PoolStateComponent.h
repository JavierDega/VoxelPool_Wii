#ifndef POOLSTATECOMPONENT_H_
#define POOLSTATECOMPONENT_H_

#include "Component/LogicComponent.h"
#include <vector>
#include <gccore.h>

enum PoolStates{
	STATE_LOOKING,
	STATE_NEXT_TURN,
	STATE_AIMING,
	STATE_SHOOTING
};
//StateMachine manages 
class PoolStateComponent : public LogicComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	PoolStateComponent();
	virtual ~PoolStateComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	virtual void ChangeState(PoolStates newState);
	std::vector<LogicComponent*> GetLogicComponents();
	//void OnDestroy()?
	//Messaging
	virtual bool Receive( ComponentMessage msg ){ return false;};

	//Variables
	PoolStates m_activeState;
	bool m_playerTurn;// 0/1 depending on player 1/2
};
#endif /*POOLSTATECOMPONENT_H_*/