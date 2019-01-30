#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "System/PadSystem.h"
#include "Component/OrbitComponent.h"
#include "GameObject.h"

using namespace std;
using namespace Math;
extern int WriteToFile(string toWrite);

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
	//@Late update pass to delete GameObjects flagged for deletion
}
//Load main menu
void ObjectSystem::LoadScene(int sceneIndex){

	//Input
	PadSystem * ps = PadSystem::GetInstance();
	//Graphics (Does WaitForVsync() stuff so maybe initialized last?)
	GraphicSystem * gs = GraphicSystem::GetInstance();

	//Empty scene
	RemoveAllObjects();
	//BUILD GAMEOBJECTS
	switch (sceneIndex){
		//@MENU
		case 0:
		{
			//CRAP
			GameObject * interestingQuote =  new GameObject("Quote", guVector{ 100.f, -150.f, -300.f }, Math::QuatIdentity,
			 guVector { 0.5f, 0.5f, 0.5f } );
			interestingQuote->AddComponent(new FontComponent(L"Who am I?", guVector{ 0, 0, 0 },
			 GXColor{255, 255, 0, 255}));
			interestingQuote->AddComponent(new FontComponent(L"For I have no model", guVector{ 0, 25, 0 },
			 GXColor{255, 255, 0, 255}));
			interestingQuote->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { -1, -1, 0 }, guVector { 0, 0, 0 }, 0.15f, 0.0f ));

			AddObject(interestingQuote);

			GameObject * poolTable =  new GameObject("PoolTable", guVector{ -10, -170, -140.f}, Math::QuatIdentity, guVector { 1, 1, 1 } );
			poolTable->AddComponent(new MeshComponent("PoolWIP"));
			poolTable->AddComponent(new FontComponent(L"What IS pool?", guVector{-75, -90, 0}, GXColor{255, 255, 0, 255}, 0.5f));
			poolTable->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { 1, 0, 0 }, guVector { 0, 0, 1}, 0.15f, 1.0f ));

			AddObject(poolTable);

			GameObject * oldGuy =  new GameObject( "FlyingOldMan", guVector{ 0, -20, 150.0f }, Math::QuatIdentity, guVector{ 2, 2, 2 } );
			oldGuy->AddComponent(new MeshComponent("chr_old"));
			oldGuy->AddComponent(new FontComponent(L"Waaah!", guVector{-50, -65, 0}, GXColor{ 255, 170, 0, 255 }, 0.20f));
			oldGuy->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0, 1, 0 }, guVector { 0, 0, 1 }, .75f, 0.8f ));

			AddObject(oldGuy);

			GameObject * doomGuy =  new GameObject( "doomGuy", guVector { 0, 0, 180 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			doomGuy->AddComponent( new MeshComponent( "mydoom" ));
			doomGuy->AddComponent(new FontComponent(L"Wait, this isn't hell..", guVector{-170, -240, 0}, GXColor{ 255, 170, 0, 255 }, 0.25f));
			doomGuy->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { -1, 0, 0 }, guVector{ 0, 0, 0 }, 0.18f, 0.f ));

			AddObject(doomGuy);

			GameObject * gameTitle =  new GameObject("GameTitle", guVector{ -10, 35, -140.f}, Math::QuatIdentity, guVector { 0.5f, 0.5f, 0.5f } );
			gameTitle->AddComponent(new FontComponent(L"Voxel Pool Wii", guVector{ -100, 0, 0 }, GXColor{ 0, 255, 0, 255 }, 1.0f, true ));
			gameTitle->AddComponent(new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0, 1, 0 }, guVector { 0, 1, 0 }, 0.0f ));

			AddObject(gameTitle);

			//MESHES
			GameObject * ball =  new GameObject( "ball1", guVector { 0, 0, 100 }, Math::QuatIdentity, guVector{ 1, 1, 1} );
			ball->AddComponent( new MeshComponent( "pool_ball_white" ));
			ball->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0.4, 0.9, 0 }, guVector{ 0, 1, 0 }, 0.25f ));

			AddObject(ball);

			GameObject * ball2 =  new GameObject( "ball2", guVector { 0, -20, 80 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			ball2->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball2->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0.9, 0.4, 0 }, guVector{ 1, 0, 0 }, 0.33f ));

			AddObject(ball2);

			GameObject * ball3 =  new GameObject( "ball3", guVector { 0, -20, 80 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			ball3->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball3->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { -0.4, 0.9, 0 }, guVector{ 1, 0, 0 }, 0.33f ));

			AddObject(ball3);

			GameObject * stick =  new GameObject( "PoolStick", guVector { 0, -20, 80 }, Math::QuatIdentity, guVector{ 1, 1, 1 } );
			stick->AddComponent( new MeshComponent( "poolstick" ));
			stick->AddComponent( new OrbitComponent( guVector { 0, 0, 0 }, guVector { 0.5, 0.5, 0 }, guVector{ 0, 0, 1 }, 0.11f ));

			AddObject(stick);

			//MENU
			GameObject * menuText =  new GameObject("TitleText", guVector{-45, 0, -100.0f}, Math::QuatIdentity,
			 guVector{ 1, 1, 1 });
			menuText->AddComponent(new MenuComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));
			menuText->AddComponent(new FontComponent(L"Start", guVector{ 0, 0, 0 }, GXColor{255, 255, 255, 255}, 0.5f));
			menuText->AddComponent(new FontComponent(L"Options", guVector{ 0, 25, 0 }, GXColor{255, 255, 255, 255}, 0.5f));
			menuText->AddComponent(new FontComponent(L"Quit", guVector{ 0, 50, 0 }, GXColor{255, 255, 255, 255}, 0.5f));

			AddObject(menuText);

			break;
		}
		case 1:
		{	
			//Gamescene
			///@PLACE CAMERA
			GameObject * scenery =  new GameObject( "Scenery", guVector { 0, -30, -60 }, QuatFromAxisAngle(guVector { 0, 1, 0 }, 2.6f ) );
			scenery->AddComponent( new MeshComponent("pool_scene1"));

			AddObject(scenery);
	
			GameObject * table =  new GameObject("PoolTable", guVector { 0, -30, -67 }, QuatFromAxisAngle(guVector { 0, 1, 0 }, 2.6f ), guVector { 0.5, 0.5, 0.5 } );
			table->AddComponent( new MeshComponent( "pooltable" ));

			AddObject(table);

			GameObject * ball = new GameObject("SphereTest", guVector { 0 , 0, -67 }, QuatIdentity );
			ball->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball->AddComponent( new RigidbodyComponent());

			AddObject(ball);

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
int ObjectSystem::AddObject(GameObject * obj){
	
	//Add to array
	/*bool m_reallocate = false;
	//Check if capacity is greater than size
	if (m_objectList.size() == m_objectList.capacity()){
		//This means its going to reallocate
		m_reallocate = true;
	}*/

	m_objectList.push_back(obj);
	return 1;
}
//Remove Objs
void ObjectSystem::RemoveAllObjects(){
	//Safety check
	m_objectList.clear();
}
void ObjectSystem::RemoveObject(GameObject * object){
	//Remove specific object. ideally called from Component itself.
	//i.e. Sphere collider requests removing attached gameObject when it is put on a hole.
	//We give an index? a pointer to the gameObject?
	for (u16 i = 0; i < m_objectList.size(); i++){
		//Compare addresses
		if (object == (m_objectList[i])){
			//Remove
			//Swap and pop approach
			//@Try not to miss update on swapped object
			//Swap and pop approach (NOT Needed)
			if (i < m_objectList.size() - 1) {
				swap(m_objectList[i], m_objectList.back());
			}
			GameObject * curObj = m_objectList.back();
			delete curObj;
			m_objectList.pop_back();
		
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
		GameObject * curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj->m_components.size(); j++){
			//Dynamic casting to identify type;
			MeshComponent * meshComp = dynamic_cast< MeshComponent * >(curObj->m_components[j]);
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
		GameObject * curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj->m_components.size(); j++){
			//Dynamic casting to identify type;
			FontComponent * fontComp = dynamic_cast< FontComponent * >(curObj->m_components[j]);
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
		GameObject * curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj->m_components.size(); j++){
			//Dynamic casting to identify type;
			LogicComponent * logicComp = dynamic_cast< LogicComponent * >(curObj->m_components[j]);
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
		GameObject * curObj = m_objectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj->m_components.size(); j++){
			//Dynamic casting to identify type;
			MenuComponent * menuComp = dynamic_cast< MenuComponent * >(curObj->m_components[j]);
			if (menuComp) menuCompList.push_back(menuComp);
		}
	}
	return menuCompList;
}
//Physics components
std::vector< RigidbodyComponent * > ObjectSystem::GetRigidbodyComponentList(){
	//Iterate through gameobjects, find x components through i.e dynamic_casts
	//Add pointers to such x components to the vector, return such vector
	std::vector< RigidbodyComponent * > rbCompList;
	//@Beware of vectors dynamically moving instances in memory
	for(u16 i = 0; i < m_objectList.size() ; i++){
		GameObject * curObj = m_objectList[i];
		for (u16 j = 0; j < curObj->m_components.size(); j++){
			//Dynamic casting to identify type;
			RigidbodyComponent * rbComp = dynamic_cast< RigidbodyComponent * >(curObj->m_components[j]);
			if (rbComp) rbCompList.push_back(rbComp);
		}
	}
	return rbCompList;
}