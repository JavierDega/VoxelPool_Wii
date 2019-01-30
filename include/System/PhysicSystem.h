#ifndef PHYSICSYSTEM_H_
#define PHYSICSYSTEM_H_

#include "System/System.h"
#include "Component/RigidbodyComponent.h"

//@Iterates on all rigidbodies
class PhysicSystem :
	public System
{
private:
	/*Here will be the instance stored*/
	static PhysicSystem * m_instance;
	/*Private constructor to prevent instancing*/
	PhysicSystem();
public:
	~PhysicSystem();
	//Singleton
	static PhysicSystem * GetInstance();

	///Functions
	//Events
	void Initialize();
	virtual void Update(float dt);
	//Utility
	void UpdatePhysics(float dt);
	bool BroadPhase(RigidbodyComponent * rb1, RigidbodyComponent *rb2);
	bool NarrowPhase(RigidbodyComponent * rb1, RigidbodyComponent *rb2);

	//Variables
	//@Timestep
	float m_minDt;
	float m_accumulator;
	//@Simulation settings
	guVector m_gravity;
	float m_airViscosity;
	//Space subdivision
	//Medium phase

};
#endif /*PHYSICSYSTEM_H_*/