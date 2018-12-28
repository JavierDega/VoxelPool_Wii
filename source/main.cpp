/*---------------------------------------------------------------------------------
	EEEH SI
---------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

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
	//Systems
	//ObjectFactory
	ObjectSystem * os = ObjectSystem::GetInstance();
	os->Initialize();
	//Input
	PadSystem * ps = PadSystem::GetInstance();
	ps->Initialize();
	//GX/Video/Debug
	GraphicSystem * gs = GraphicSystem::GetInstance();
	gs->Initialize();
	
	//GameObjects
	GameObject * poolTable = os->AddObject();
	poolTable->m_transform.m_position.z = -100.0f;
	poolTable->AddComponent(new MeshComponent(poolTable, "PoolWIP"));

	GameObject * titleText = os->AddObject();
	titleText->m_transform.m_position = guVector{0, 25, -50.0f};
	titleText->AddComponent(new FontComponent(titleText, L"SpacePool_Wii", GXColor{0, 0, 0, 255}));

	//Timestepping
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

