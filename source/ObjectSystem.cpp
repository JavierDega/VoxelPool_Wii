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
	//@What do here?	
}
//Update
void ObjectSystem::Update( float dt )
{
	//@What do here?
}
//Add Obj
GameObject * ObjectSystem::AddObject(){
	//Add to vector
	GameObject obj = GameObject(guVector{0, 0, 0});
	m_objectList.push_back(obj);
	//return object just pushed
	return &m_objectList[m_objectList.size() - 1];
}
//Remove Objs
void ObjectSystem::RemoveAllObjects(){
	//Safety check
	while (!m_objectList.empty()) {
		//Remove from vector
		m_objectList.pop_back();
	}

}
//Get comp lists
//Model meshes
std::vector< MeshComponent * > ObjectSystem::GetMeshComponentList(){
	//Iterate through gameobjects, find MeshComponents through i.e dynamic_casts
	//Add pointers to such meshcomponents to the vector, return such vector
	std::vector< MeshComponent * > meshCompList;
	for (u16 i = 0; i < m_objectList.size(); i++){
		GameObject curObj = m_objectList[i];
		//Find mesh components
		for (u16 i = 0; i < curObj.m_components.size(); i++){
			//Dynamic casting to identify type;
			MeshComponent * meshComp = dynamic_cast<MeshComponent *>(curObj.m_components[i]);
			if (meshComp) meshCompList.push_back(meshComp);
		}
	}
	return meshCompList;
}
//Font meshes
std::vector< FontComponent * > ObjectSystem::GetFontComponentList(){
	//Iterate through gameobjects, find specific components through i.e dynamic_casts
	//Add pointers to certain components to the vector, return such vector
	std::vector< FontComponent * > fontCompList;
	for (u16 i = 0; i < m_objectList.size(); i++){
		GameObject curObj = m_objectList[i];
		//Find components
		for (u16 i = 0; i < curObj.m_components.size(); i++){
			//Dynamic casting to identify type;
			FontComponent * fontComp = dynamic_cast<FontComponent *>(curObj.m_components[i]);
			if (fontComp) fontCompList.push_back(fontComp);
		}
	}
	return fontCompList;
}