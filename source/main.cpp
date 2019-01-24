/*---------------------------------------------------------------------------------
	EEEH SI
---------------------------------------------------------------------------------*/

#include "System/ObjectSystem.h"
#include "System/PadSystem.h"
#include "System/GraphicSystem.h"

#include "Extra/Math.h"

#include <time.h>
#include <ogc/lwp_watchdog.h>

#include <iostream>
#include <fstream>

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
int WriteToFile (string toWrite) 
{
  ofstream myfile;
  myfile.open ("debug.txt");
  myfile << "Writing this to a file.\n";
  myfile << toWrite + "\n";
  myfile.close();
  return 0;
}

int main(int argc, char **argv) {
	//DECLARE SYSTEMS
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
	os->LoadScene(0);

	while(1) {
		//Timestep
		float prevTime = globalTime;
		globalTime = diff_msec(starttime, gettime())/1000.0f;
		float dt = globalTime-prevTime;
		//Update
		//gs->AddLog(to_string(globalTime));
		gs->AddLog(to_string(1/dt));
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

