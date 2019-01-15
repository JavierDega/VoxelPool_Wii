/*---------------------------------------------------------------------------------
	EEEH SI
---------------------------------------------------------------------------------*/
#include <time.h>
#include <ogc/lwp_watchdog.h>

#include "System/ObjectSystem.h"
#include "System/PadSystem.h"
#include "System/GraphicSystem.h"
#include "GameObject.h"
#include "Component/MeshComponent.h"
#include "Component/FontComponent.h"
#include "Component/OrbitCameraComponent.h"

using namespace std;

float globalTime;

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
	//Time
	/*
	extern u32 gettick(void);
	extern u64 gettime(void);
	extern void settime(u64);
	u32 diff_sec(u64 start,u64 end);
	u32 diff_msec(u64 start,u64 end);
	u32 diff_usec(u64 start,u64 end);
	u32 diff_nsec(u64 start,u64 end);
	*/
	__lwp_watchdog_init();
	//settime(0);
	u64 starttime = gettime();

	//ObjectFactory
	ObjectSystem * os = ObjectSystem::GetInstance();
	//Input
	PadSystem * ps = PadSystem::GetInstance();
	//Graphics (Does WaitForVsync() stuff so maybe initialized last?)
	GraphicSystem * gs = GraphicSystem::GetInstance();

	//BUILD GAMEOBJECTS
	//Beware of pointer becoming invalid arbitrarily(Like after adding another element to the vector)
	GameObject * poolTable = os->AddObject("PoolTable", guVector{ 0, -20, -150.0f});
	poolTable->AddComponent(new MeshComponent("PoolWIP"));
	poolTable->AddComponent(new FontComponent(L"PoolTable", guVector{-75, -75, 0}, GXColor{0, 255, 0, 255}));
	poolTable->AddComponent(new OrbitCameraComponent());

	GameObject * titleText = os->AddObject("TitleText", guVector{-45, 0, -100.0f});
	titleText->AddComponent(new MenuComponent(&ps->m_buttonsHeld, &ps->m_buttonsDown, &ps->m_buttonsUp));
	titleText->AddComponent(new FontComponent(L"Start", guVector{ 0, 0, 0 }, GXColor{50, 50, 50, 255}));
	titleText->AddComponent(new FontComponent(L"Options", guVector{ 0, 25, 0 }, GXColor{50, 50, 50, 255}));
	titleText->AddComponent(new FontComponent(L"Quit", guVector{ 0, 50, 0 }, GXColor{50, 50, 50, 255}));

	//INIT SYSTEMS (CALL CERTAIN SCENE START EVENTS)
	os->Initialize();
	ps->Initialize();
	gs->Initialize();
	while(1) {
		//Timestep
		float prevTime = globalTime;
		globalTime = diff_msec(starttime, gettime())/1000.0f;
		float dt = globalTime-prevTime;
		//Update
		gs->AddLog(to_string(globalTime));
		gs->AddLog(to_string(dt));
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

