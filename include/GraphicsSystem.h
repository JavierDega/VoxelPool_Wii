#ifndef GRAPHICSSYSTEM_H_
#define GRAPHICSSYSTEM_H_

#include <gccore.h>
#include <malloc.h>
#include <string.h>
#include "VideoSystem.h"

#define DEFAULT_FIFO_SIZE (1024*1024)

class GraphicsSystem {
	public:
		void* gsFifo;
		uint32_t gsWidth;
		uint32_t gsHeight;
		
		void initializeGraphicsSystem(VideoSystem *videoSystem);
		void SetFontVtxDesc();
		void SetModelVtxDesc();
		GraphicsSystem(VideoSystem *videoSystem);
		void EndScene(uint32_t *frameBuffer);
		void SetDirectionalLight(u32 theta, u32 phi);
		
	//Variables
	Mtx view,mv,mr,mvi; // view and perspective matrices
	Mtx model, modelview;
	Mtx44 perspective;
	GXColor background;
	guVector cam, up, look;
	
	//Light
	GXColor litcolors [3];

};

#endif /*GRAPHICSSYSTEM_H_*/