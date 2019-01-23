/*---------------------------------------------------------------------------------
	EEEH SI
---------------------------------------------------------------------------------*/

#include "System/ObjectSystem.h"
#include "System/PadSystem.h"
#include "System/GraphicSystem.h"
#include "GameObject.h"
#include "Component/MeshComponent.h"
#include "Component/FontComponent.h"
#include "Component/OrbitCameraComponent.h"

#include "Extra/Math.h"

#include <time.h>
#include <ogc/lwp_watchdog.h>

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

	//Load Main Menu
	os->LoadMenu(0);

	while(1) {
		//Timestep
		float prevTime = globalTime;
		globalTime = diff_msec(starttime, gettime())/1000.0f;
		float dt = globalTime-prevTime;
		//Update
		//gs->AddLog(to_string(globalTime));
		//gs->AddLog(to_string(dt));
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

