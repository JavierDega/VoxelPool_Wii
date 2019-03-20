#include "System/ObjectSystem.h"
#include "System/GraphicSystem.h"
#include "System/PadSystem.h"
#include "Component/OrbitComponent.h"
#include "Component/PoolStateComponent.h"
#include "Component/OrbitCameraComponent.h"
#include "GameObject.h"

#include "Extra/Math.h"

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
	//@Late update pass to delete GameObjects flagged for deletion
	for (u16 i = 0; i < m_objectList.size(); i++){
		if (m_objectList[i]->m_isDeleted){
			//Delete object with swap and pop, so we keep on iterating through list correctly
			RemoveObject(nullptr, i);
			//Object that was on the back is on this one's position, and we need to update on it too.
			i--;
		}
	}
}
//Messaging
void ObjectSystem::SendMessage(ComponentMessage msg){
	//@What messages sent here? To whom, ideally to objects?

}
//Load scenes
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
			interestingQuote->AddComponent(new FontComponent(L"Who am I?", guVector{ 0, 0, 0 }, GXColor{255, 255, 0, 255}));
			interestingQuote->AddComponent(new FontComponent(L"For I have no model", guVector{ 0, 25, 0 }, GXColor{255, 255, 0, 255}));
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
			menuText->AddComponent(new MenuComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp, 0.5f));
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
			//GraphicSystem * gs = GraphicSystem::GetInstance();
			//PadSystem * ps = PadSystem::GetInstance();

			GameObject * gameController = new GameObject( "GameController", guVector{ 6.5, -0.5, -7.5}, Math::QuatIdentity, guVector{.3, .3, .3 } );
			gameController->AddComponent(new PoolStateComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));

			AddObject(gameController);

			GameObject * scenery =  new GameObject( "Scenery", guVector { -20, -7, 20 } );
			scenery->AddComponent( new MeshComponent("pool_scene1"));

			AddObject(scenery);
	
			GameObject * table =  new GameObject("PoolTable", guVector { 0, -7, 0 }, Math::QuatIdentity, guVector { 0.5, 0.5, 0.5 } );
			table->AddComponent( new MeshComponent( "pooltable" ));

			AddObject(table);

			//@TABLE COLLIDERS

			GameObject * tableCollider = new GameObject("TableCollider", guVector{ 6.25f, -1.5, 7.25 }, Math::QuatIdentity, guVector{ 1.45, 0.15, 0.19 });
			tableCollider->AddComponent( new MeshComponent( "8x8x8" ));
			tableCollider->AddComponent( new RigidbodyComponent( guVector { 6.f, 0.5f, 0.7f }, 10.0f, true ));
			
			AddObject(tableCollider);

			GameObject * tableCollider2 = new GameObject("TableCollider2", guVector{ 6.25f, -1.5, -7.25 }, Math::QuatIdentity, guVector{ 1.45, 0.15, 0.19 });
			tableCollider2->AddComponent( new MeshComponent( "8x8x8" ));
			tableCollider2->AddComponent( new RigidbodyComponent( guVector { 6.f, 0.5f, 0.7f }, 10.0f, true ));
			
			AddObject(tableCollider2);

			GameObject * tableCollider3 = new GameObject("TableCollider3", guVector{ -6.5f, -1.5, 7.25  }, Math::QuatIdentity, guVector{ 1.4, 0.15, 0.19 });
			tableCollider3->AddComponent( new MeshComponent( "8x8x8" ));
			tableCollider3->AddComponent( new RigidbodyComponent( guVector { 6.f, 0.5f, 0.7f }, 10.0f, true ));
			
			AddObject(tableCollider3);

			GameObject * tableCollider4 = new GameObject("TableCollider4", guVector{ -6.5f, -1.5, -7.25 }, Math::QuatIdentity, guVector{ 1.4, 0.15, 0.19 });
			tableCollider4->AddComponent( new MeshComponent( "8x8x8" ));
			tableCollider4->AddComponent( new RigidbodyComponent( guVector { 6.f, 0.5f, 0.7f }, 10.0f, true ));
			
			AddObject(tableCollider4);

			GameObject * tableCollider5 = new GameObject("TableCollider5", guVector{ -13.75f, -1.5, 0 }, Math::QuatIdentity, guVector{ 0.19, 0.15, 1.4 });
			tableCollider5->AddComponent( new MeshComponent( "8x8x8" ));
			tableCollider5->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 6.0f }, 10.0f, true ));
			
			AddObject(tableCollider5);

			GameObject * tableCollider6 = new GameObject("TableCollider6", guVector{ 13.75f, -1.5, 0 }, Math::QuatIdentity, guVector{ 0.19, 0.15, 1.4 });
			tableCollider6->AddComponent( new MeshComponent( "8x8x8" ));
			tableCollider6->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 6.0f }, 10.0f, true ));
			
			AddObject(tableCollider6);

			//TRIGGERS
			GameObject * trigger = new GameObject("trigger", guVector{ 13.f, -1.5f, 6.5f }, Math::QuatIdentity, guVector{ 0.19, 0.15, 0.19 });
			trigger->AddComponent( new MeshComponent( "8x8x8Red" ));
			trigger->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 0.7f }, 10.0f, true ));
			
			AddObject(trigger);

			GameObject * trigger2 = new GameObject("trigger2", guVector{ 13.f, -1.5, -6.5 }, Math::QuatIdentity, guVector{ 0.19, 0.15, 0.19 });
			trigger2->AddComponent( new MeshComponent( "8x8x8Red" ));
			trigger2->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 0.7f }, 10.0f, true, true ));
			
			AddObject(trigger2);

			GameObject * trigger3 = new GameObject("trigger3", guVector{ -13.f, -1.5f, 6.5f  }, Math::QuatIdentity, guVector{ 0.19, 0.15, 0.19 });
			trigger3->AddComponent( new MeshComponent( "8x8x8Red" ));
			trigger3->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 0.7f }, 10.0f, true, true ));
			
			AddObject(trigger3);

			GameObject * trigger4 = new GameObject("trigger4", guVector{ -13.f, -1.5, -6.5f }, Math::QuatIdentity, guVector{ 0.19, 0.15, 0.19 });
			trigger4->AddComponent( new MeshComponent( "8x8x8Red" ));
			trigger4->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 0.7f }, 10.0f, true, true ));
			
			AddObject(trigger4);

			GameObject * trigger5 = new GameObject("trigger5", guVector{ -0.25f, -1.5, 7.0f }, Math::QuatIdentity, guVector{ 0.19, 0.15, 0.19 });
			trigger5->AddComponent( new MeshComponent( "8x8x8Red" ));
			trigger5->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 6.5f }, 10.0f, true, true ));
			
			AddObject(trigger5);

			GameObject * trigger6 = new GameObject("trigger6", guVector{ -0.25f, -1.5f, -7.0f }, Math::QuatIdentity, guVector{ 0.19, 0.15, 0.19 });
			trigger6->AddComponent( new MeshComponent( "8x8x8Red" ));
			trigger6->AddComponent( new RigidbodyComponent( guVector { 0.7f, 0.5f, 0.7f }, 10.0f, true, true ));
			
			AddObject(trigger6);

			//@POOL BALLS @REMEMBER TO SET UP BALLTYPES (TEAM)
			GameObject * ball = new GameObject("BallRed", guVector { 5 , -1.0, 0.6 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball);

			GameObject * ball2 = new GameObject("BallBlue", guVector { 5, -1.0, -0.6 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball2->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball2->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball2);

			GameObject * ball3 = new GameObject("White_Ball", guVector { -5, -1.0, 0 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball3->AddComponent( new MeshComponent( "pool_ball_white" ));
			ball3->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball3);

			GameObject * ball4 = new GameObject("BallRed2", guVector { 4, -1.0, 0 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball4->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball4->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball4);

			GameObject * ball5 = new GameObject("BallBlue2", guVector { 6, -1.0, 0 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball5->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball5->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball5);

			GameObject * ball6 = new GameObject("BallRed3", guVector { 6, -1.0, -1.2 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball6->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball6->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball6);

			GameObject * ball7 = new GameObject("BallBlue3", guVector { 6, -1.0, 1.2 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball7->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball7->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball7);

			GameObject * ball8 = new GameObject("BallRed4", guVector { 7, -1.0, 0.6 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball8->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball8->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball8);

			GameObject * ball9 = new GameObject("BallBlue4", guVector { 7, -1.0, -0.6 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball9->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball9->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball9);

			GameObject * ball10 = new GameObject("BallRed5", guVector { 7, -1.0, -1.8 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball10->AddComponent( new MeshComponent( "pool_ball_red" ));
			ball10->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball10);

			GameObject * ball11 = new GameObject("BallBlue5", guVector { 7, -1.0, 1.8 }, QuatIdentity, guVector { 0.15f, 0.15f, 0.15f });
			ball11->AddComponent( new MeshComponent( "pool_ball_blue" ));
			ball11->AddComponent( new RigidbodyComponent( 0.5f ) );

			AddObject(ball11);

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
void ObjectSystem::RemoveObject(GameObject * object, int optionalIndex){
	//Remove specific object. ideally called from Component itself.
	//i.e. Sphere collider requests removing attached gameObject when it is put on a hole.
	//We give an index? a pointer to the gameObject?
	if( optionalIndex != -1)
	{
		//We remove by index
		//Remove
		//Swap and pop approach
		//@Try not to miss update on swapped object
		if ((u16)optionalIndex < m_objectList.size() - 1) {
			swap(m_objectList[optionalIndex], m_objectList.back());
		}
		GameObject * curObj = m_objectList.back();
		delete curObj;
		m_objectList.pop_back();
	}
	else{
		//We remove by ptrRef
		for (u16 i = 0; i < m_objectList.size(); i++){
			//Compare addresses
			if (object == (m_objectList[i])){
				//Remove
				//Swap and pop approach
				//@Try not to miss update on swapped object
				if (i < m_objectList.size() - 1) {
					swap(m_objectList[i], m_objectList.back());
				}
				GameObject * curObj = m_objectList.back();
				delete curObj;
				m_objectList.pop_back();
			}
		}
	}
}
GameObject * ObjectSystem::FindObjectByName( string name ){
	GameObject * returnedObj = nullptr;
	for (u16 i = 0; i < m_objectList.size(); i++){
		if (m_objectList[i]->m_name.compare(name) == 0 ) {
			returnedObj = m_objectList[i];
			GraphicSystem::GetInstance()->AddLog("Object: " + m_objectList[i]->m_name + " found");
		}
	}
	return returnedObj;
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
			if (meshComp && meshComp->m_isActive){ 
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
			if (fontComp && fontComp->m_isActive ) fontCompList.push_back(fontComp);
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
			if (logicComp && logicComp->m_isActive) logicCompList.push_back(logicComp);
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
			if (menuComp && menuComp->m_isActive) menuCompList.push_back(menuComp);
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
			//Dynamic casting to identify type
			RigidbodyComponent * rbComp = dynamic_cast< RigidbodyComponent * >(curObj->m_components[j]);
			if (rbComp && rbComp->m_isActive) rbCompList.push_back(rbComp);
		}
	}
	return rbCompList;
}