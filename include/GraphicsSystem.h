#ifndef GRAPHICSSYSTEM_H_
#define GRAPHICSSYSTEM_H_

#include <gccore.h>
#include <malloc.h>
#include "VideoSystem.h"


#define DEFAULT_FIFO_SIZE (1024*1024)

class GraphicsSystem {
	public:
		void* gsFifo;
		uint32_t gsWidth;
		uint32_t gsHeight;
		
		void InitializeGraphicsSystem(VideoSystem *videoSystem);
		void SetFontDesc();
		void SetModelDesc();
		GraphicsSystem(VideoSystem *videoSystem);
		void EndScene(uint32_t *frameBuffer);
		void SetLight();
		void SetDirectionalLight(u32 theta, u32 phi);
		
	//Variables
	Mtx view; // view and perspective matrices
	Mtx model, modelview;
	Mtx44 projection;
	GXColor background;
	guVector cam, up, look;
	
	guVector rotAxis;
	float rotValue;
	
	//Light
	GXColor lightColor [3];
	
	//Tex
	TPLFile paletteTPL;
	GXTexObj paletteTexture;

};

#endif /*GRAPHICSSYSTEM_H_*/