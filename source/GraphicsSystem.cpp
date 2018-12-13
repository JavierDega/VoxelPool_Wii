#include "GraphicsSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include "palette_tpl.h"
#include "palette.h"

//Constructor
GraphicsSystem::GraphicsSystem(VideoSystem *videoSystem) {

	//Init vars
	background = {255, 255, 255, 0};
	cam = {0.0F, 0.0F, 0.0F};
	up = {0.0F, 1.0F, 0.0F};
	look = {0.0F, 0.0F, -1.0F};
	
	//setup our camera at the origin
	//looking down the -z axis wth y up
	guLookAt(view, &cam, &up, &look);
	
	//Rotation
	rotAxis = {1,1,1};
	rotValue = 0;
	
	lightColor[0] =  { 255, 255, 255, 255 }; // Light color 1
    lightColor[1] = { 128, 128, 128, 255 }; // Ambient 1
    lightColor[2] =  { 255, 255, 255, 255 };  // Material 1
	
	//Init GP
	this->initializeGraphicsSystem(videoSystem);
}

void GraphicsSystem::initializeGraphicsSystem(VideoSystem *videoSystem) {

	GXRModeObj *videoMode = videoSystem->getVideoMode();

	// Initialize GX system
	this->gsFifo = memalign(32, DEFAULT_FIFO_SIZE);
	memset(this->gsFifo, 0, DEFAULT_FIFO_SIZE);
	GX_Init(this->gsFifo, DEFAULT_FIFO_SIZE);

	// Set the background clear color
	GX_SetCopyClear(background, 0x00ffffff);

	// Setup the viewport display 
	f32 yscale = GX_GetYScaleFactor(videoMode->efbHeight, videoMode->xfbHeight);
	uint32_t xfbHeight = GX_SetDispCopyYScale(yscale);

	GX_SetViewport(0, 0,videoMode->fbWidth,videoMode->efbHeight, 0, 1);
	GX_SetScissor(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopySrc(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopyDst(videoMode->fbWidth, xfbHeight);
	GX_SetCopyFilter(videoMode->aa, videoMode->sample_pattern, GX_TRUE, videoMode->vfilter);

	// Store graphics system width and height
	this->gsWidth = (uint32_t)videoMode->fbWidth;
	this->gsHeight = (uint32_t)videoMode->efbHeight;
	
	GX_SetFieldMode(videoMode->field_rendering, ((videoMode->viHeight == 2 * videoMode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

	// Anti-aliasing initialization
	if(videoMode->aa){
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	}
	else{
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	}

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(videoSystem->getVideoFramebuffer(), GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);
	

	// Texture vertex format setup
	GX_ClearVtxDesc();

	// Texture vertext format 0 initialization
	//FreeTypeGX draws fonts to this index
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	
	//My models are drawn to this index
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	//Set number of rasterized color channels
	GX_SetNumChans(1);
	
	GX_InvVtxCache();
	GX_InvalidateTexAll();
	
	// Tev graphics pipeline initialization
	GX_SetNumTexGens(1);
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);	
	
	//Load palette.bmp texture
	TPL_OpenTPLFromMemory(&paletteTPL, (void *)palette_tpl,palette_tpl_size);
	TPL_GetTexture(&paletteTPL,palette,&paletteTexture);
	
	
	// setup our projection matrix
	// this creates a perspective matrix with a view angle of 90,
	// and aspect ratio based on the display resolution
    f32 w = videoMode->viWidth;
    f32 h = videoMode->viHeight;
	guPerspective(projection, 45, (f32)w/h, 0.1F, 1000.0F);
	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);
	
}

//Font settings
void GraphicsSystem::SetFontDesc(){
	//For now lets put matrix transformations here
	guMtxIdentity(model);
	guMtxScaleApply(model, model, 0.1f, -0.1f, 0.1f);
	guMtxTransApply(model, model, -12.5f,10.0f,-40.0f);
	guMtxConcat(view,model,modelview);
	// Apply changes to model view matrix
	GX_LoadPosMtxImm(modelview,GX_PNMTX0);
	
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

}

//Also loads Texture, since all models use palette.bmp
void GraphicsSystem::SetModelDesc(){
	//Texture	
	GX_LoadTexObj(&paletteTexture, GX_TEXMAP0);
	//Desc
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
	//Matrix
	//For now lets put matrix transformations here
	guMtxIdentity(model);
	guMtxRotAxisDeg(model, &rotAxis, rotValue);
	guMtxTransApply(model, model, 0.0f,-20.0f,-100.0f);
	guMtxConcat(view,model,modelview);

	// load the modelview matrix into matrix memory
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	
	rotValue+= 0.1f;
}

void GraphicsSystem::EndScene(uint32_t *frameBuffer) {
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(frameBuffer, GX_TRUE);
	
	GX_DrawDone();
}

void GraphicsSystem::SetLight()
{
	guVector lpos;
	GXLightObj lobj;

	lpos.x = 0.0f;
	lpos.y = 0.0f;
	lpos.z = 0.0f;
	
	guVecMultiply(view,&lpos,&lpos);

	GX_InitLightPos(&lobj,lpos.x,lpos.y,lpos.z);
	GX_InitLightColor(&lobj,lightColor[0]);
	GX_LoadLightObj(&lobj,GX_LIGHT0);
	
	// set number of rasterized color channels
	GX_SetNumChans(1);
    GX_SetChanCtrl(GX_COLOR0A0,GX_ENABLE,GX_SRC_REG,GX_SRC_REG,
	GX_LIGHT0,GX_DF_CLAMP,GX_AF_NONE);
    GX_SetChanAmbColor(GX_COLOR0A0,lightColor[1]);
    GX_SetChanMatColor(GX_COLOR0A0,lightColor[2]);
}

void GraphicsSystem::SetDirectionalLight(u32 theta,u32 phi)
{
	guVector lpos;
	f32 _theta,_phi;
	GXLightObj lobj;

	_theta = (f32)theta*M_PI/180.0f;
	_phi = (f32)phi*M_PI/180.0f;
	lpos.x = 1000.0f * cosf(_phi) * sinf(_theta);
	lpos.y = 1000.0f * sinf(_phi);
	lpos.z = 1000.0f * cosf(_phi) * cosf(_theta);

	guVecMultiply(view,&lpos,&lpos);

	GX_InitLightPos(&lobj,lpos.x,lpos.y,lpos.z);
	GX_InitLightColor(&lobj,lightColor[0]);
	GX_LoadLightObj(&lobj,GX_LIGHT0);
	
	// set number of rasterized color channels
	GX_SetNumChans(1);
    GX_SetChanCtrl(GX_COLOR0A0,GX_ENABLE,GX_SRC_REG,GX_SRC_VTX,GX_LIGHT0,GX_DF_CLAMP,GX_AF_NONE);
    GX_SetChanAmbColor(GX_COLOR0A0,lightColor[1]);
    GX_SetChanMatColor(GX_COLOR0A0,lightColor[2]);
}