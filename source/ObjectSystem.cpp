#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"

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
	m_objectCount = 0;
}
//Destructor @Singleton so?
ObjectSystem::~ObjectSystem(){

}
//Init
void ObjectSystem::Initialize()
{
	//@What do here?
	//Initialize component references
}
//Update
void ObjectSystem::Update( float dt )
{
	//@What do here?
}
//Add Obj
GameObject * ObjectSystem::AddObject(){
	
	if (m_objectCount == MAX_GAMEOBJECTS){
		GraphicSystem::GetInstance()->AddLog("Too many GameObjects!");
		return nullptr;
	}
	//Add to array
	m_objectList[m_objectCount] = GameObject();
	//Increase iterator
	m_objectCount++;
	//Return address
	return &m_objectList[m_objectCount - 1];
}
//Remove Objs
void ObjectSystem::RemoveAllObjects(){
	//Safety check
}
//Get comp lists
//Model meshes
std::vector< MeshComponent * > ObjectSystem::GetMeshComponentList(){
	//Iterate through gameobjects, find MeshComponents through i.e dynamic_casts
	//Add pointers to such meshcomponents to the vector, return such vector
	std::vector< MeshComponent * > meshCompList;
	//@Beware of vectors dynamically moving instances in memory
	for(u16 i = 0; i < m_objectCount ; i++){
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
	//Iterate through gameobjects, find MeshComponents through i.e dynamic_casts
	//Add pointers to such meshcomponents to the vector, return such vector
	std::vector< FontComponent * > fontCompList;
	//@Beware of vectors dynamically moving instances in memory
	for(u16 i = 0; i < m_objectCount ; i++){
		GameObject curObj = m_objectList[i];
		//Find mesh components
		for (u16 i = 0; i < curObj.m_components.size(); i++){
			//Dynamic casting to identify type;
			FontComponent * fontComp = dynamic_cast< FontComponent * >(curObj.m_components[i]);
			if (fontComp) fontCompList.push_back(fontComp);
		}
	}
	return fontCompList;
}