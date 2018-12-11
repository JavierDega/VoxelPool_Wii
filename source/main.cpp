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
#include "PadSystem.h"

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
	//Video
	VideoSystem* videoSystem = new VideoSystem();
	//GX
	GraphicsSystem *graphicsSystem = new GraphicsSystem(videoSystem);
	//Input
	PadSystem *padSystem = new PadSystem();
	//Font
	FreeTypeGX *fontSystem = new FreeTypeGX(GX_TF_IA8, GX_VTXFMT0);
	fontSystem->setCompatibilityMode(FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE
	| FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT);//BLEND AND TEX DIRECT
	FT_UInt fontSize = 64;
	fontSystem->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, fontSize, false);	// Initialize the font system with the font parameters from rursus_compact_mono_ttf.h


	uint32_t buttons = 0x0000;
	uint32_t textStyle = FTGX_JUSTIFY_CENTER;
	bool isUnderlined = false;
	bool isStrike = false;
	
	//Create model
	ModelMesh * myPoolModel = new ModelMesh((void *)PoolWIP_obj, PoolWIP_obj_size);
	
	while(!padSystem->pressedExitButton(buttons = padSystem->scanPads(0))) {

		if(padSystem->pressedUp(buttons)) {	// Increase font size
			fontSystem->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, ++fontSize, false);
		}
		if(padSystem->pressedDown(buttons)) {	// Decrease font size
			fontSystem->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, fontSize > 6 ? --fontSize : fontSize, false);
		}
		if(padSystem->pressedLeft(buttons)) {	// Toggle text underlining
			isUnderlined = !isUnderlined;
		}
		if(padSystem->pressedRight(buttons)) {	// Toggle text strikethrough
			isStrike = !isStrike;
		}

		
		//Lighting
		graphicsSystem->SetDirectionalLight(8, 20);
		
		//Font
		//Set up vtx desc and tex format?
		graphicsSystem->SetFontVtxDesc();
		//RENDER
		textStyle = FTGX_JUSTIFY_CENTER;
		textStyle = isUnderlined	? textStyle | FTGX_STYLE_UNDERLINE	: textStyle;
		textStyle = isStrike		? textStyle | FTGX_STYLE_STRIKE		: textStyle;

		fontSystem->drawText(320,	50,		_TEXT("THE QUICK BROWN"),	(GXColor){0xff, 0x00, 0x00, 0xff},	textStyle | FTGX_ALIGN_TOP);
		fontSystem->drawText(320,	125,	_TEXT("FOX JUMPS OVER"),	(GXColor){0x00, 0xff, 0x00, 0xff},	textStyle | FTGX_ALIGN_MIDDLE);
		fontSystem->drawText(320,	200,	_TEXT("THE LAZY DOG"),		(GXColor){0x00, 0x00, 0xff, 0xff},	textStyle | FTGX_ALIGN_BOTTOM);

		fontSystem->drawText(320,	275,	_TEXT("the quick brown"),	(GXColor){0xff, 0xff, 0x00, 0xff},	textStyle);
		fontSystem->drawText(320,	350,	_TEXT("fox jumps over"),	(GXColor){0xff, 0x00, 0xff, 0xff},	textStyle);
		fontSystem->drawText(320,	425,	_TEXT("the lazy dog"),		(GXColor){0x00, 0xff, 0xff, 0xff},	textStyle);
		
		
		//Model RENDER
		//Set up vtx desc and texture load
		graphicsSystem->SetModelVtxDesc();
		//myPoolModel->Render();
		//RENDER
		
		
		
		graphicsSystem->EndScene(videoSystem->getVideoFramebuffer());
		videoSystem->flipVideoFramebuffer();
	}

	delete fontSystem;
	delete padSystem;
	delete graphicsSystem;
	delete videoSystem;
	
	return 0;
}

