#include "GraphicsSystem.h"
#include <math.h>

#include "palette_tpl.h"
#include "palette.h"

GraphicsSystem::GraphicsSystem(VideoSystem *videoSystem) {

	//Init vars
	background = {255, 255, 255, 0xff};
	cam = {0.0F, 0.0F, 0.0F};
	up = {0.0F, 1.0F, 0.0F};
	look = {0.0F, 0.0F, -1.0F};
	
	//setup our camera at the origin
	//looking down the -z axis wth y up
	guLookAt(view, &cam, &up, &look);
	
	litcolors[0] = { 0, 0, 0, 255}; // Light color 1
    litcolors[1] = { 255, 255, 255, 255 }; // Ambient 1
    litcolors[2] = { 255, 0, 0, 255 };  // Material 1
	
	//Init GP
	this->initializeGraphicsSystem(videoSystem);
}

void GraphicsSystem::SetFontVtxDesc(){

	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

}

//Also loads Texture, since all models use palette.bmp
void GraphicsSystem::SetModelVtxDesc(){
	
	GX_InvalidateTexAll();
	GX_LoadTexObj(&paletteTexture, GX_TEXMAP0);
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
	
	//For now lets put matrix transformations here
	guMtxIdentity(model);
	guMtxTransApply(model, model, 0.0f,0.0f,-70.0f);
	guMtxConcat(view,model,modelview);

	// load the modelview matrix into matrix memory
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	
	guMtxInverse(modelview,mvi);
	guMtxTranspose(mvi,modelview);
	GX_LoadNrmMtxImm(modelview, GX_PNMTX0);
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
	SetFontVtxDesc();

	// Texture vertext format 0 initialization
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

	GX_SetNumChans(1);

	// Tev graphics pipeline initialization
	GX_SetNumTexGens(1);
	GX_SetTevOp(GX_TEVSTAGE0, GX_BLEND);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY);	
	
	//Lighting
	f32 w = videoMode->viWidth;
	f32 h = videoMode->viHeight;
	guLightPerspective(mv,45, (f32)w/h, 1.05F, 1.0F, 0.0F, 0.0F);
    guMtxTrans(mr, 0.0F, 0.0F, -1.0F);
    guMtxConcat(mv, mr, mv);
    GX_LoadTexMtxImm(mv, GX_TEXMTX0, GX_MTX3x4);
	
	GX_InvalidateTexAll();
	//Load palette.bmp texture
	TPL_OpenTPLFromMemory(&paletteTPL, (void *)palette_tpl,palette_tpl_size);
	TPL_GetTexture(&paletteTPL,palette,&paletteTexture);
	
	// Reset the model view matrix
	guMtxIdentity(modelview);
	guMtxTransApply(modelview, modelview, 0.0f, 0.0f, -5.0f);
	
	// Apply changes to model view matrix
	GX_LoadPosMtxImm(modelview,GX_PNMTX0);
	guOrtho(perspective,0,479,0,639,0,300);

	// Apply changes to the projection matrix
	GX_LoadProjectionMtx(perspective, GX_ORTHOGRAPHIC);

	GX_SetViewport(0, 0, videoMode->fbWidth, videoMode->efbHeight, 0, 1);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);

	// The final scissor box
	GX_SetScissorBoxOffset(0, 0);
	GX_SetScissor(0, 0, this->gsWidth, this->gsHeight);
}

void GraphicsSystem::EndScene(uint32_t *frameBuffer) {
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetColorUpdate(GX_TRUE);
	GX_SetAlphaUpdate(GX_TRUE);
	GX_CopyDisp(frameBuffer,GX_TRUE);
	
	GX_DrawDone();
	
	GX_InvalidateTexAll();
}

void GraphicsSystem::SetDirectionalLight(u32 theta,u32 phi)
{
	guVector lpos;
	f32 _theta,_phi;
	GXLightObj lobj;
	
	GXColor litcol = litcolors[0];
	GXColor ambcol = litcolors[1];
	GXColor matcol = litcolors[2];
	
	_theta = (f32)theta*M_PI/180.0f;
	_phi = (f32)phi*M_PI/180.0f;
	lpos.x = 1000.0f * cosf(_phi) * sinf(_theta);
	lpos.y = 1000.0f * sinf(_phi);
	lpos.z = 1000.0f * cosf(_phi) * cosf(_theta);

	guVecMultiply(view,&lpos,&lpos);

	GX_InitLightPos(&lobj,lpos.x,lpos.y,lpos.z);
	GX_InitLightColor(&lobj,litcol);
	GX_LoadLightObj(&lobj,GX_LIGHT0);
	
	// set number of rasterized color channels
	GX_SetNumChans(1);
    GX_SetChanCtrl(GX_COLOR0A0,GX_ENABLE,GX_SRC_VTX,GX_SRC_VTX,GX_LIGHT0,GX_DF_CLAMP,GX_AF_NONE);
    GX_SetChanAmbColor(GX_COLOR0A0,ambcol);
    GX_SetChanMatColor(GX_COLOR0A0,matcol);
}