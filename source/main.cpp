/*---------------------------------------------------------------------------------

	EEEH SI
---------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "GraphicsSystem.h"
#include "DebugSystem.h"
#include "VideoSystem.h"

#include "FreeTypeGX.h"

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
	WPAD_Init();
	PAD_Init();
	
	//Video
	VideoSystem* videoSystem = new VideoSystem();
	//GX
	GraphicsSystem *graphicsSystem = new GraphicsSystem(videoSystem);
	
	//Debug/font
	DebugSystem * debugSystem = DebugSystem::GetInstance();
	debugSystem->m_isEnabled = true;
	
	//Create model
	ModelMesh * myPoolModel = new ModelMesh((void *)PoolWIP_obj, PoolWIP_obj_size);
	u32 rotValue = 0;
	while(1) {
	
		WPAD_ScanPads();
		PAD_ScanPads();
		u16 buttonsHeld = PAD_ButtonsHeld(0);
		u16 buttonsDown = PAD_ButtonsDown(0);
		if ( buttonsHeld & PAD_BUTTON_LEFT ){
			graphicsSystem->cam.x--;
			graphicsSystem->look.x--;
		
		}
		if ( buttonsHeld & PAD_BUTTON_RIGHT ){
			graphicsSystem->cam.x++;
			graphicsSystem->look.x++;
		
		}
		if ( buttonsHeld & PAD_BUTTON_UP ){
			graphicsSystem->cam.y++;
			graphicsSystem->look.y++;
		
		}
		if ( buttonsHeld & PAD_BUTTON_DOWN ){
			graphicsSystem->cam.y--;
			graphicsSystem->look.y--;
		
		}
		
		if ( buttonsHeld & PAD_BUTTON_A ){
			graphicsSystem->cam.z++;
			graphicsSystem->look.z++;
		
		}
		
		if ( buttonsHeld & PAD_BUTTON_B ){
			graphicsSystem->cam.z--;
			graphicsSystem->look.z--;
		
		}
		
		if (buttonsDown & PAD_BUTTON_X){
			debugSystem->m_isEnabled = !debugSystem->m_isEnabled;
		}
		//setup our camera at the origin
		//looking down the -z axis wth y up
		guLookAt(graphicsSystem->view, &graphicsSystem->cam, &graphicsSystem->up, &graphicsSystem->look);
		//Lighting
		//Lighting direction is rotating with view
		graphicsSystem->SetLight();
		rotValue++;
		//**ORDER OR RENDERING MATTERS BECAUSE OF Z BUFFERS(FONT TRANSPARENCY)**//		
		//Model RENDER
		//Set up vtx desc and texture load
		graphicsSystem->SetModelDesc();
		myPoolModel->Render();
		
		//Debug
		debugSystem->Update();
		debugSystem->SetFontTransform(graphicsSystem);
		debugSystem->Render();
			
		graphicsSystem->EndScene(videoSystem->getVideoFramebuffer());
		videoSystem->flipVideoFramebuffer();
	}

	delete debugSystem;
	delete graphicsSystem;
	delete videoSystem;
	
	return 0;
}

