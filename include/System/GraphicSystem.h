#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include "System/System.h"
#include "FreeTypeGX.h"
#include <string>
#include <vector>
#include <gccore.h>

#define FRAMEBUFFER_SIZE 2
#define DEFAULT_FIFO_SIZE (1024*1024)

typedef struct MeshStr{
	//Variables
	std::string name;
	std::vector < guVector > m_vertices;
    std::vector < guVector > m_uvs;
    std::vector < guVector > m_normals;
}Mesh;

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
	void InitGXVideo();
	bool LoadMeshFromObj(std::string name, void* fileStream, unsigned int fileSize);
	void SetLight();
	void EndDraw();
	uint32_t * GetVideoFrameBuffer();
	//Debug
	void AddLog(std::wstring log);
	void AddLog(std::string log);
		
	//Variables
	//Video
	GXRModeObj *videoMode;
	uint32_t *videoFrameBuffer[FRAMEBUFFER_SIZE];
	uint32_t videoFrameBufferIndex;
	//Graphics
	void* gsFifo;
	uint32_t gsWidth;
	uint32_t gsHeight;
	//Matrices - Coordinate spaces
	Mtx m_view, m_model, m_modelview;
	Mtx44 m_projection;
	guVector m_cam, m_up, m_look;
	//Models
	std::vector<Mesh> m_meshes;
	//Font
	FreeTypeGX * m_font;
	//Lighting
	GXColor m_lightColor [2];
	GXColor m_background;
	//Tex
	TPLFile m_paletteTPL;
	GXTexObj m_paletteTexture;
	//Debug
	bool m_debug;
	std::vector < std::wstring > m_stringLogs;
};

#endif /*GRAPHICSYSTEM_H_*/