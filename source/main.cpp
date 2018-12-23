/*---------------------------------------------------------------------------------
	EEEH SI
---------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "PadSystem.h"
#include "GraphicSystem.h"
#include "DebugSystem.h"

#include "rursus_compact_mono_ttf.h"	// Include the compiled font.
										// Once compiled you can view the contents of this file in example1/all/rursus_compact_mono_ttf.h
#include "ModelMesh.h"
#include "PoolWIP_obj.h"
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
	//Input
	PadSystem * ps = PadSystem::GetInstance();
	ps->Initialize();
	//GX
	GraphicSystem * gs = GraphicSystem::GetInstance();
	gs->Initialize();
	//Debug/font
	DebugSystem * ds = DebugSystem::GetInstance();
	ds->Initialize();
	
	//Create model
	ModelMesh * myPoolModel = new ModelMesh((void *)PoolWIP_obj, PoolWIP_obj_size);
	u32 rotValue = 0;
	while(1) {
		ps->ScanPads(0);
		if ( ps->m_buttonsHeld & PAD_BUTTON_LEFT ){
			gs->cam.x--;
			gs->look.x--;
		}
		if ( ps->m_buttonsHeld & PAD_BUTTON_RIGHT ){
			gs->cam.x++;
			gs->look.x++;
		}
		if ( ps->m_buttonsHeld & PAD_BUTTON_UP ){
			gs->cam.y++;
			gs->look.y++;
		}
		if ( ps->m_buttonsHeld & PAD_BUTTON_DOWN ){
			gs->cam.y--;
			gs->look.y--;
		}
		if ( ps->m_buttonsHeld & PAD_BUTTON_A ){
			gs->cam.z++;
			gs->look.z++;
		}
		if ( ps->m_buttonsHeld & PAD_BUTTON_B ){
			gs->cam.z--;
			gs->look.z--;
		}
		if ( ps->m_buttonsDown & PAD_BUTTON_X){
			ds->m_isEnabled = !ds->m_isEnabled;
		}

		//Setup our camera at the origin
		//looking down the -z axis wth y up
		guLookAt(gs->view, &gs->cam, &gs->up, &gs->look);
		//Lighting
		//Lighting direction is rotating with view
		gs->SetLight();
		rotValue++;
		//**ORDER OR RENDERING MATTERS BECAUSE OF Z BUFFERS(FONT TRANSPARENCY)**//		
		//Model RENDER
		//Set up vtx desc and texture load
		gs->SetModelDesc();
		myPoolModel->Render();
		
		//Debug (Fonts after geometry for transparency)
		ds->Update();
		ds->SetFontTransform(gs);
		ds->Render();
			
		gs->EndScene();
	}

	delete ds;
	delete gs;
	
	return 0;
}

