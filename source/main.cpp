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
	//Font
	FreeTypeGX *fontSystem = new FreeTypeGX(GX_TF_IA8, GX_VTXFMT0);
	fontSystem->setCompatibilityMode(FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE
	| FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT);//BLEND AND TEX DIRECT
	FT_UInt fontSize = 20;
	fontSystem->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, fontSize, false);	// Initialize the font system with the font parameters from rursus_compact_mono_ttf.h


	uint32_t textStyle = FTGX_JUSTIFY_CENTER;
	bool isUnderlined = false;
	bool isStrike = false;
	
	//Create model
	ModelMesh * myPoolModel = new ModelMesh((void *)PoolWIP_obj, PoolWIP_obj_size);
	
	while(1) {
	
		WPAD_ScanPads();
		PAD_ScanPads();
		u16 buttonsHeld = PAD_ButtonsHeld(0);
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

		//setup our camera at the origin
		//looking down the -z axis wth y up
		guLookAt(graphicsSystem->view, &graphicsSystem->cam, &graphicsSystem->up, &graphicsSystem->look);
		//Lighting
		graphicsSystem->SetDirectionalLight(8, 20);		
		
		//Model RENDER
		//Set up vtx desc and texture load
		graphicsSystem->SetModelDesc();
		myPoolModel->Render();
	
		//Font
		//Set up vtx desc and tex format?
		graphicsSystem->SetFontDesc();
		//RENDER
		textStyle = FTGX_JUSTIFY_CENTER;
		textStyle = isUnderlined	? textStyle | FTGX_STYLE_UNDERLINE	: textStyle;
		textStyle = isStrike		? textStyle | FTGX_STYLE_STRIKE		: textStyle;

		fontSystem->drawText(0,	-40,		_TEXT("THE QUICK BROWN"),	(GXColor){0xff, 0x00, 0x00, 0xff},	textStyle | FTGX_ALIGN_TOP);
		fontSystem->drawText(0,	-10,	_TEXT("FOX JUMPS OVER"),	(GXColor){0x00, 0xff, 0x00, 0xff},	textStyle | FTGX_ALIGN_MIDDLE);
		fontSystem->drawText(0,	20,	_TEXT("THE LAZY DOG"),		(GXColor){0x00, 0x00, 0xff, 0xff},	textStyle | FTGX_ALIGN_BOTTOM);

		fontSystem->drawText(0,	50,	_TEXT("the quick brown"),	(GXColor){0xff, 0xff, 0x00, 0xff},	textStyle);
		fontSystem->drawText(0,	80,	_TEXT("fox jumps over"),	(GXColor){0xff, 0x00, 0xff, 0xff},	textStyle);
		fontSystem->drawText(0,	110,	_TEXT("the lazy dog"),		(GXColor){0x00, 0xff, 0xff, 0xff},	textStyle);

		
		graphicsSystem->EndScene(videoSystem->getVideoFramebuffer());
		videoSystem->flipVideoFramebuffer();
	}

	delete fontSystem;
	delete graphicsSystem;
	delete videoSystem;
	
	return 0;
}

