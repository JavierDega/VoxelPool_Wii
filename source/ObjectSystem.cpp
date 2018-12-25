#include "System/ObjectSystem.h"


//Instance
ObjectSystem * ObjectSystem::m_instance = NULL;
ObjectSystem * ObjectSystem::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new ObjectSystem();
	}
	return m_instance;
}

//Constructor
ObjectSystem::ObjectSystem() {

}
//Init
void ObjectSystem::Initialize()
{

}
void ObjectSystem::Update( float dt )
{

}
