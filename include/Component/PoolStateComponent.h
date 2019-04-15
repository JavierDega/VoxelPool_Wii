#ifndef POOLSTATECOMPONENT_H_
#define POOLSTATECOMPONENT_H_

#include "Component/ControllableComponent.h"
#include <vector>
#include <gccore.h>

enum PoolStates{
	//@POOL SHOOTING ROUTINE
	STATE_LOOKING,
	STATE_ALL_SLEEPING,
	STATE_AIMING,
	STATE_LOCKED_DIRECTION,
	STATE_COMMIT_CHARGING,
	STATE_LOCKED_CHARGE,
	STATE_COMMIT_SHOOTING,
};
//StateMachine manages 
class PoolStateComponent : public ControllableComponent{
public:
	//Constructor
	//@Point to instances in PadSystem
	PoolStateComponent(u16 * buttonsHeld, u16 * buttonsDown, u16 * buttonsUp, u16 * wButtonsHeld, u16 * wButtonsDown, u16 * wButtonsUp,
	float * swing, float * pitch, float * deviation, float * roll );
	virtual ~PoolStateComponent();
	virtual void OnStart();
	virtual void ComputeLogic(float dt);
	std::vector<LogicComponent*> GetLogicComponents();
	//void OnDestroy()?
	//Messaging
	virtual bool Receive( ComponentMessage msg );

	//Variables
	PoolStates m_activeState;
	int m_redBalls, m_blueBalls;//@Remaining
	bool m_playerTurn, m_redExtraTurn, m_blueExtraTurn;//0/1 depending on player 1/2
	float m_constrainedYaw;
	float m_backMotion, m_lateralMotion;
};
#endif /*POOLSTATECOMPONENT_H_*/