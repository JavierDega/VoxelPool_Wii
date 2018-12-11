#include <stdlib.h>
#include <math.h>
#include <gccore.h>
#include <malloc.h>
#include <string.h>
#include <wiiuse/wpad.h>

#define FRAMEBUFFER_SIZE 2
#define DEFAULT_FIFO_SIZE (256*1024)

class GraphicsSystem{
	public:
	
		GraphicsSystem();
		~GraphicsSystem();
		GXRModeObj* GetVideoMode();
		uint32_t *GetVideoFrameBuffer();
		void InitializeGraphicsSystem();
		void SetTransformation(guVector translation, f32 rotation,
		guVector * rotAxis, guVector scale, u32 slotIndex);
		void SetPerspective();
		void SetUpLighting();
		void SetLight();
		void UpdateScene();
		
		
		//Variables
		GXRModeObj * rmode;
		void * frameBuffer[FRAMEBUFFER_SIZE];
		uint32_t fb;
		void* gpfifo;
		uint32_t gsWidth;
		uint32_t gsHeight;
		
		//Tex
		TPLFile paletteTPL;
		GXTexObj texture;
		
		//Matrix
		Mtx44 projection;
		Mtx view; // view and perspective matrices
		Mtx model, modelview;
		Mtx44 perspective;
		guVector cam, up, look;


};