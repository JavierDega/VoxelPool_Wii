#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"

using namespace std;

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
GameObject * ObjectSystem::AddObject(std::string name, guVector position, guQuaternion rotation, guVector scale ){
	
	//Add to array
	bool m_reallocate = false;
	//Check if capacity is greater than size
	if (m_objectList.size() == m_objectList.capacity()){
		//This means its going to reallocate
		m_reallocate = true;
	}
	m_objectList.push_back(GameObject( name, position, rotation, scale ));

	//Has just reallocated
	if(m_reallocate){
		for (u16 i = 0; i < m_objectList.size(); i++){
			m_objectList[i].RefreshComponentAddresses();
		}
	}
	//Return address
	return &m_objectList.back();
}
//Remove Objs
void ObjectSystem::RemoveAllObjects(){
	//Safety check
}
void ObjectSystem::RemoveObject(GameObject * object){
	//Remove specific object. ideally called from Component itself.
	//i.e. Sphere collider requests removing attached gameObject when it is put on a hole.
	//We give an index? a pointer to the gameObject?
	for (u16 i = 0; i < m_objectList.size(); i++){
		//Compare addresses
		if (object == &(m_objectList[i])){
			//Remove
			//Swap and pop approach
			swap(m_objectList[i], m_objectList.back());
			m_objectList.pop_back();
			m_objectList[i].RefreshComponentAddresses();
		}
	}
}
//Get comp lists
//Model meshes
std::vector< MeshComponent * > ObjectSystem::GetMeshComponentList(){
	//Iterate through gameobjects, find MeshComponents through i.e dynamic_casts
	//Add pointers to such meshcomponents to the vector, return such vector
	std::vector< MeshComponent * > meshCompList;
	//@Beware of vectors dynamically moving instances in memory
	for(u16 i = 0; i < m_objectList.size() ; i++){
		GameObject curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj.m_components.size(); j++){
			//Dynamic casting to identify type;
			MeshComponent * meshComp = dynamic_cast< MeshComponent * >(curObj.m_components[j]);
			if (meshComp){ 
	 			meshCompList.push_back(meshComp);
			}
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
	for(u16 i = 0; i < m_objectList.size() ; i++){
		GameObject curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj.m_components.size(); j++){
			//Dynamic casting to identify type;
			FontComponent * fontComp = dynamic_cast< FontComponent * >(curObj.m_components[j]);
			if (fontComp) fontCompList.push_back(fontComp);
		}
	}
	return fontCompList;
}
//Logic
std::vector< LogicComponent * > ObjectSystem::GetLogicComponentList(){
	//Iterate through gameobjects, find x components through i.e dynamic_casts
	//Add pointers to such components to the vector, return such vector
	std::vector< LogicComponent * > logicCompList;
	//@Beware of vectors dynamically moving instances in memory
	for(u16 i = 0; i < m_objectList.size() ; i++){
		GameObject curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj.m_components.size(); j++){
			//Dynamic casting to identify type;
			LogicComponent * logicComp = dynamic_cast< LogicComponent * >(curObj.m_components[j]);
			if (logicComp) logicCompList.push_back(logicComp);
		}
	}
	return logicCompList;
}
//Menu selectors
std::vector< MenuComponent * > ObjectSystem::GetMenuComponentList(){
	//Iterate through gameobjects, find MeshComponents through i.e dynamic_casts
	//Add pointers to such meshcomponents to the vector, return such vector
	std::vector< MenuComponent * > menuCompList;
	//@Beware of vectors dynamically moving instances in memory
	for(u16 i = 0; i < m_objectList.size() ; i++){
		GameObject curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj.m_components.size(); j++){
			//Dynamic casting to identify type;
			MenuComponent * menuComp = dynamic_cast< MenuComponent * >(curObj.m_components[j]);
			if (menuComp) menuCompList.push_back(menuComp);
		}
	}
	return menuCompList;
}