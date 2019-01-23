#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "System/PadSystem.h"
#include "Component/OrbitCameraComponent.h"
#include "GameObject.h"

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
//Load main menu
void ObjectSystem::LoadMenu(int sceneIndex){

	//Input
	PadSystem * ps = PadSystem::GetInstance();
	//Graphics (Does WaitForVsync() stuff so maybe initialized last?)
	GraphicSystem * gs = GraphicSystem::GetInstance();

	//BUILD GAMEOBJECTS
	switch (sceneIndex){
		//@MENU
		case 0:
		{
			//Beware of pointer becoming invalid arbitrarily(Like after adding another element to the vector)
			GameObject * poolTable = AddObject( "PoolTable", guVector{ 0, -20, -150.0f}, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			poolTable->AddComponent(new MeshComponent("PoolWIP"));
			poolTable->AddComponent(new FontComponent(L"PoolTable", guVector{-75, -75, 0}, GXColor{0, 255, 0, 255}, 0.5f));
			poolTable->AddComponent(new OrbitCameraComponent());

			GameObject * oldGuy = AddObject("FlyingOldMan", guVector { 10, 0, -100.f }, Math::QuatIdentity, guVector { 1, 1, 1 } );
			oldGuy->AddComponent(new MeshComponent("chr_old"));
			oldGuy->AddComponent(new FontComponent(L"Waaah!", guVector{-50, -50, 0}, GXColor{255, 0, 0, 255}, 0.25));
			oldGuy->AddComponent(new OrbitCameraComponent( guVector { 1, 0, 0 }));

			GameObject * titleText = AddObject("TitleText", guVector{-45, 0, -100.0f}, Math::QuatIdentity,
				guVector{ 1, 1, 1 });
			titleText->AddComponent(new MenuComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));
			titleText->AddComponent(new FontComponent(L"Start", guVector{ 0, 0, 0 }, GXColor{50, 50, 50, 255}, 0.5f));
			titleText->AddComponent(new FontComponent(L"Options", guVector{ 0, 25, 0 }, GXColor{50, 50, 50, 255}, 0.5f));
			titleText->AddComponent(new FontComponent(L"Quit", guVector{ 0, 50, 0 }, GXColor{50, 50, 50, 255}, 0.5f));
			break;
		}
		case 1:
		{
			break;
		}
		default:
		{

		}
		break;
	}

	//INIT SYSTEMS (CALL CERTAIN SCENE START EVENTS)
	Initialize();
	ps->Initialize();
	gs->Initialize();
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