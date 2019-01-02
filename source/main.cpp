/*---------------------------------------------------------------------------------
	EEEH SI
---------------------------------------------------------------------------------*/
#include "System/ObjectSystem.h"
#include "System/PadSystem.h"
#include "System/GraphicSystem.h"
#include "GameObject.h"
#include "Component/MeshComponent.h"
#include "Component/FontComponent.h"

/**
 * Program entry point.
 *
 * @param argc	Number of provided command line parameters.
 * @param argv	List of command line parameters.
 *
 * @return Program exit status code.
 */
int main(int argc, char **argv) {
	//DECLARE SYSTEMS
	//ObjectFactory
	ObjectSystem * os = ObjectSystem::GetInstance();
	//Graphics
	GraphicSystem * gs = GraphicSystem::GetInstance();
	//Input
	PadSystem * ps = PadSystem::GetInstance();

	//BUILD GAMEOBJECTS
	GameObject * poolTable = os->AddObject();
	poolTable->m_transform.m_position = guVector{ 0, -20, -125.0f};
	poolTable->AddComponent(new MeshComponent("PoolWIP"));
	poolTable->AddComponent(new FontComponent(L"PoolTable", guVector{-75, -75, 0}, GXColor{0, 255, 0, 255}));

	GameObject * titleText = os->AddObject();
	titleText->m_transform.m_position = guVector{-45, 0, -100.0f};
	titleText->AddComponent(new MenuComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));
	titleText->AddComponent(new FontComponent(L"Start", guVector{ 0, 0, 0 }, GXColor{0, 0, 0, 255}));
	titleText->AddComponent(new FontComponent(L"Options", guVector{ 0, 25, 0 }, GXColor{0, 0, 0, 255}));
	titleText->AddComponent(new FontComponent(L"Quit", guVector{ 0, 50, 0 }, GXColor{0, 0, 0, 255}));

	//INIT SYSTEMS (CALL CERTAIN SCENE START EVENTS)
	os->Initialize();
	gs->Initialize();
	ps->Initialize();
	//TIME
	float dt = 0.0f;
	while(1) {
		//Input
		ps->Update(dt);
		//Draw
		gs->Update(dt);
	}
	delete os;
	delete ps;
	delete gs;
	
	return 0;
}

