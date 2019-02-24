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
	void SendMessage(ComponentMessage msg);
	//Utility
	void UpdatePhysics(float dt);
	bool NarrowPhase(RigidbodyComponent * rb1, RigidbodyComponent *rb2, float dt);
	bool SphereToSphere(RigidbodyComponent * rb1, RigidbodyComponent * rb2, float dt);
	bool SphereToAABB(RigidbodyComponent * rb1, RigidbodyComponent * rb2, float dt );
	//Helpful queries
	guVector ClosestPtPointAABB(guVector point, RigidbodyComponent * rb);

	//Variables
	//@Timestep
	float m_minDt;
	float m_accumulator;
	//@Simulation settings
	bool m_stepMode, m_stepOnce;
	float m_gravity;
	float m_airViscosity;
	float m_frictionCoefficient;
	//Space subdivision

};
#endif /*PHYSICSYSTEM_H_*/