#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include "System/System.h"
#include <gccore.h>
#include <malloc.h>

#define FRAMEBUFFER_SIZE 2
#define DEFAULT_FIFO_SIZE (1024*1024)

class GraphicSystem : public System {
	private:
	/*Here will be the instance stored*/
	static GraphicSystem* m_instance;
	/*Private constructor to prevent instancing*/
	GraphicSystem();
	public:
	~GraphicSystem();
	//Singleton
	static GraphicSystem* GetInstance();	
	//Funcs
	void Initialize();
	void Update( float dt );
	void SetFontDesc();
	void SetModelDesc();
	void EndScene();
	void SetLight();
	//Video
	uint32_t * GetVideoFrameBuffer();
		
	//Variables
	//GX
	//Video
	GXRModeObj *videoMode;
	uint32_t *videoFrameBuffer[FRAMEBUFFER_SIZE];
	uint32_t videoFrameBufferIndex;
	//Graphics
	void* gsFifo;
	uint32_t gsWidth;
	uint32_t gsHeight;
	//Matrices
	Mtx view; // view and perspective matrices
	Mtx model, modelview;
	Mtx44 projection;
	guVector cam, up, look;
	
	guVector rotAxis;
	float rotValue;
	//Lighting
	GXColor lightColor [2];
	GXColor background;
	//Tex
	TPLFile paletteTPL;
	GXTexObj paletteTexture;

};

#endif /*GRAPHICSYSTEM_H_*/