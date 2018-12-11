/*---------------------------------------------------------------------------------

	EEEH SI
---------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "GraphicsSystem.h"

#include "ModelMesh.h"
#include "PoolWIP_obj.h"

#define DEFAULT_FIFO_SIZE	(256*1024)

int main(int argc, char **argv) {

	//Matrix
	u32 first_frame = 1;
	
	//Model
	ModelMesh * poolMesh = new ModelMesh((void *)PoolWIP_obj,PoolWIP_obj_size);
	
	//Graphics System
	GraphicsSystem* myGs = new GraphicsSystem();
	myGs->InitializeGraphicsSystem(); 
	myGs->SetPerspective();
	
	//Transform values
	guVector rotAxis = {1,1,1};
	f32 rotVal = 0.0f;
	guVector trans = {0.0f, 0.0f, -70.0f};
	guVector scale = {1.0f, 1.0f, 1.0f};

	
	while(1) {

		WPAD_ScanPads();
		
		if(first_frame) {
			first_frame = 0;
			VIDEO_SetBlack(FALSE);
		}
		
		
		//Set transformation in slot
		myGs->SetTransformation(trans, rotVal, &rotAxis, 
		scale, GX_PNMTX0);
		//exit(0);
		//Render
		poolMesh->Render();
		exit(0);
		//GraphicsSystem UpdateScene()
		myGs->UpdateScene();
		
		rotVal -= 0.15f;				// Decrease The Rotation Variable For The Quad     ( NEW )
	}
}
