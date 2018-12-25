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
//Destructor @Singleton so?
ObjectSystem::~ObjectSystem(){

}
//Init
void ObjectSystem::Initialize()
{

}
//Update
void ObjectSystem::Update( float dt )
{

}
//Add Obj
GameObject * ObjectSystem::AddObject( GameObject * gameObject){
	//Add to vector
	m_objectList.push_back(gameObject);

	return gameObject;
}
//Remove Objs
void ObjectSystem::RemoveAllObjects(){
	//Safety check
	while (!m_objectList.empty()) {
		GameObject * curObject = m_objectList[m_objectList.size() - 1];
		//Remove from vector
		m_objectList.pop_back();
		//Destructor**
		delete curObject;
		curObject = nullptr;
	}

}