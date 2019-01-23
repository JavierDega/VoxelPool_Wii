#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "System/PadSystem.h"
#include "Component/OrbitComponent.h"
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
void ObjectSystem::LoadScene(int sceneIndex){

	//Input
	PadSystem * ps = PadSystem::GetInstance();
	//Graphics (Does WaitForVsync() stuff so maybe initialized last?)
	GraphicSystem * gs = GraphicSystem::GetInstance();

	//BUILD GAMEOBJECTS
	switch (sceneIndex){
		//@MENU
		case 0:
		{

			//CRAP
			GameObject * interestingQuote = AddObject("Quote", guVector{ 100.f, -150.f, -300.f }, Math::QuatIdentity,
			 guVector { 0.5f, 0.5f, 0.5f } );
			interestingQuote->AddComponent(new FontComponent(L"Who am I?", guVector{ 0, 0, 0 },
			 GXColor{255, 255, 0, 255}));
			interestingQuote->AddComponent(new FontComponent(L"For I have no model", guVector{ 0, 25, 0 },
			 GXColor{255, 255, 0, 255}));
			interestingQuote->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { -1, -1, 0 }, guVector { 0, 0, 0 }, 0.1f, 0.0f ));

			GameObject * poolTable = AddObject("PoolTable", guVector{ -10, -150, -150.f}, Math::QuatIdentity, guVector { 1, 1, 1 } );
			poolTable->AddComponent(new MeshComponent("PoolWIP"));
			poolTable->AddComponent(new FontComponent(L"What IS pool?", guVector{-75, -90, 0}, GXColor{255, 255, 0, 255}, 0.5f));
			poolTable->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { 1, 0, 0 }, guVector { 0, 0, 1}, 0.15f, 1.0f ));

			GameObject * oldGuy = AddObject( "FlyingOldMan", guVector{ 0, -20, 150.0f }, Math::QuatIdentity, guVector{ 2, 2, 2 } );
			oldGuy->AddComponent(new MeshComponent("chr_old"));
			oldGuy->AddComponent(new FontComponent(L"Waaah!", guVector{-50, -65, 0}, GXColor{ 255, 170, 0, 255 }, 0.20f));
			oldGuy->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0, 1, 0 }, guVector { 0, 0, 1 }, .75f, 0.8f ));

			GameObject * gameTitle = AddObject("GameTitle", guVector{ 0, -10, -140.f}, Math::QuatIdentity, guVector { 0.5f, 0.5f, 0.5f } );
			gameTitle->AddComponent(new FontComponent(L"Voxel Pool Wii", guVector{ -100, 0, 0 }, GXColor{255, 255, 255, 255}));
			gameTitle->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { 1, 0, 0 }, guVector { 0, 0, 0 }, 0.07f ));

			//MESHES
			GameObject * ball = AddObject( "ball1", guVector { 0, 0, 100 }, Math::QuatIdentity, guVector{ 1, 1, 1} );
			ball->AddComponent( new MeshComponent( "pool_ball_white" ));
			ball->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0.4, 0.9, 0 }, guVector{ 0, 1, 0 }, 0.25f ));

			GameObject * ball2 = AddObject( "ball2", guVector { 0, -20, 80 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			ball2->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball2->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0.9, 0.4, 0 }, guVector{ 1, 0, 0 }, 0.33f ));

			GameObject * ball3 = AddObject( "ball3", guVector { 0, -20, 80 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			ball3->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball3->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { -0.4, 0.9, 0 }, guVector{ 1, 0, 0 }, 0.33f ));

			GameObject * doomguy = AddObject( "doomguy", guVector { 0, 0, 130 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			doomguy->AddComponent( new MeshComponent( "mydoom" ));
			doomguy->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { -1, 0, 0 }, guVector{ 0, 0, 0 }, 1.33f, 0.f ));

			//GameObject * ball1 = AddObject( "ball2", guVector {});
			//MENU
			GameObject * titleText = AddObject("TitleText", guVector{-45, 0, -100.0f}, Math::QuatIdentity,
			 guVector{ 1, 1, 1 });
			titleText->AddComponent(new MenuComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));
			titleText->AddComponent(new FontComponent(L"Start", guVector{ 0, 0, 0 }, GXColor{255, 255, 255, 255}, 0.5f));
			titleText->AddComponent(new FontComponent(L"Options", guVector{ 0, 25, 0 }, GXColor{255, 255, 255, 255}, 0.5f));
			titleText->AddComponent(new FontComponent(L"Quit", guVector{ 0, 50, 0 }, GXColor{255, 255, 255, 255}, 0.5f));
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