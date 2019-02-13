#include "System/GraphicSystem.h"
#include "System/ObjectSystem.h"
#include "Component/FontComponent.h"
#include "Extra/Math.h"

#include "ogc/gu.h"
#include <stdio.h>

//@MODELS
#include "PoolWIP_obj.h"
#include "pool_ball_white_obj.h"
#include "pool_ball_red_obj.h"
#include "pool_ball_blue_obj.h"
#include "chr_old_obj.h"
#include "mydoom_obj.h"
#include "pool_scene1_obj.h"
#include "pooltable_obj.h"
#include "poolstick_obj.h"
//@TEXTURES
#include "palette_tpl.h"
#include "palette.h"
#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

using namespace std;

//Instance
GraphicSystem * GraphicSystem::m_instance = NULL;
GraphicSystem * GraphicSystem::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new GraphicSystem();
	}
	return m_instance;
}

//Constructor
GraphicSystem::GraphicSystem() {
	///Init vars
	m_background = {20, 20, 20, 0};
	m_cam = {0.0F, 0.0F, 0.0F};
	m_up = {0.0F, 1.0F, 0.0F};
	m_look = {0.0F, 0.0F, -1.0F};

	m_pitch = 0;
	m_yaw = 0;

	m_lightColor[0] =  { 255, 255, 255, 255 }; // Light color 1
    m_lightColor[1] = { 150, 150, 150, 255 }; // Ambient 1
	
	videoFrameBufferIndex = 0;

	m_debug = true;

	//MODEL PARSE(Need to do before creating MeshComponents)
	if(!LoadMeshFromObj("PoolWIP", (void *)PoolWIP_obj, PoolWIP_obj_size))exit(0);
	if(!LoadMeshFromObj("pool_ball_white", (void *)pool_ball_white_obj, pool_ball_white_obj_size))exit(0);
	if(!LoadMeshFromObj("pool_ball_red", (void *)pool_ball_red_obj, pool_ball_red_obj_size))exit(0);
	if(!LoadMeshFromObj("pool_ball_blue", (void *)pool_ball_blue_obj, pool_ball_blue_obj_size))exit(0);
	if(!LoadMeshFromObj("chr_old", (void *)chr_old_obj, chr_old_obj_size))exit(0);
	if(!LoadMeshFromObj("mydoom", (void *)mydoom_obj, mydoom_obj_size))exit(0);
	if(!LoadMeshFromObj("pool_scene1", (void *)pool_scene1_obj, pool_scene1_obj_size))exit(0);
	if(!LoadMeshFromObj("pooltable", (void *)pooltable_obj, pooltable_obj_size))exit(0);
	if(!LoadMeshFromObj("poolstick", (void *)poolstick_obj, poolstick_obj_size))exit(0);

	//GX/VIDEO
	InitGXVideo();
	//FONT
	m_font = new FreeTypeGX(GX_TF_IA8, GX_VTXFMT0);
	m_font->setCompatibilityMode(FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE
	| FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT);//BLEND AND TEX DIRECT
	FT_UInt fontSize = 30;
	m_font->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, fontSize, false);	// Initialize the font system with the font parameters from rursus_compact_mono_ttf.h

	//Set default logs
	std::wstring log = L"Default string log";
	m_stringLogs.insert(m_stringLogs.begin(), log);
}
//Destructor (Singleton so..?)
GraphicSystem::~GraphicSystem(){

}
//Init
void GraphicSystem::Initialize() {
	//@What do here?
}
//Update
void GraphicSystem::Update( float dt ){
	///DRAW ALL RENDERABLES: Fonts last because of z buffer **
	
	//Singletons needed
	ObjectSystem * os =  ObjectSystem::GetInstance();

	//Begin frame draw
	guLookAt(m_view, &m_cam, &m_up, &m_look);
	SetLight();

	//Draw Component pipeline
	DrawMeshes(os->GetMeshComponentList());
	DrawFonts(os->GetFontComponentList());

	//End frame draw
	EndDraw();
}
void GraphicSystem::InitGXVideo(){
	
	VIDEO_Init();
	
	videoMode = VIDEO_GetPreferredMode(NULL);

	for(uint8_t videoIndex = 0; videoIndex < FRAMEBUFFER_SIZE; videoIndex++) {
		videoFrameBuffer[videoIndex] = (uint32_t *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(videoMode));
		VIDEO_ClearFrameBuffer(videoMode, videoFrameBuffer[videoIndex], COLOR_BLACK);
	}
	videoFrameBufferIndex = 0;
	
	VIDEO_Configure(videoMode);
	VIDEO_SetNextFramebuffer(videoFrameBuffer[videoFrameBufferIndex]);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	
	if(videoMode->viTVMode & VI_NON_INTERLACE) {
		VIDEO_WaitVSync();
	}

	// Initialize GX system
	gsFifo = memalign(32, DEFAULT_FIFO_SIZE);
	memset(gsFifo, 0, DEFAULT_FIFO_SIZE);
	GX_Init(gsFifo, DEFAULT_FIFO_SIZE);

	// Set the background clear color
	GX_SetCopyClear(m_background, 0x00ffffff);

	// Setup the viewport display
	f32 yscale = GX_GetYScaleFactor(videoMode->efbHeight, videoMode->xfbHeight);
	uint32_t xfbHeight = GX_SetDispCopyYScale(yscale);

	GX_SetViewport(0, 0,videoMode->fbWidth,videoMode->efbHeight, 0, 1);
	GX_SetScissor(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopySrc(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopyDst(videoMode->fbWidth, xfbHeight);
	GX_SetCopyFilter(videoMode->aa, videoMode->sample_pattern, GX_TRUE, videoMode->vfilter);

	// Store graphics system width and height
	gsWidth = (uint32_t)videoMode->fbWidth;
	gsHeight = (uint32_t)videoMode->efbHeight;
	
	GX_SetFieldMode(videoMode->field_rendering, ((videoMode->viHeight == 2 * videoMode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

	// Anti-aliasing initialization
	if(videoMode->aa){
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	}
	else{
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	}

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(videoFrameBuffer[videoFrameBufferIndex], GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);
	
	// Texture vertex format setup
	GX_ClearVtxDesc();

	// Texture vertext format 0 initialization
	//FreeTypeGX draws fonts to this index
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	
	//My models are drawn to this index
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	// set number of rasterized color channels
	GX_SetNumChans(1);

	//set number of textures to generate
	GX_SetNumTexGens(1);

	GX_InvVtxCache();
	GX_InvalidateTexAll();
	
	//Load palette.bmp texture
	TPL_OpenTPLFromMemory(&m_paletteTPL, (void *)palette_tpl,palette_tpl_size);
	TPL_GetTexture(&m_paletteTPL,palette,&m_paletteTexture);
	
	//Setup TEV (Texture Environment) Stage
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);	

	// setup our projection matrix
	// this creates a perspective matrix with a view angle of 90,
	// and aspect ratio based on the display resolution
    f32 w = videoMode->viWidth;
    f32 h = videoMode->viHeight;	
	//Render mtx
	guPerspective(m_projection, 45, (f32)w/h, 0.1F, 1000.0F);
	GX_LoadProjectionMtx(m_projection, GX_PERSPECTIVE);
}
//Load obj
bool GraphicSystem::LoadMeshFromObj( std::string name, void* fileStream, unsigned int fileSize ){
	//Temp variables
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< guVector > temp_vertices, temp_uvs, temp_normals;
	
	FILE * file = fmemopen(fileStream, fileSize, "r");
	
	if( file == NULL ){
		printf("Impossible to open the file !\n");
		return false;
	}
	
	//Read loop: we only stop reading when End Of File is reached
	while(1){
		
		char lineHeader[128];
		//Lee la primera palabra de la linea
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; //EOF, final del archivo. Se finaliza el ciclo.
			
		//else : analizar el header
		
		if (strcmp(lineHeader, "v") == 0){
			guVector vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			guVector uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			guVector normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
			&vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices	 .push_back(uvIndex[0]);
			uvIndices	 .push_back(uvIndex[1]);
			uvIndices	 .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	//We finished reading in the file and parsing into temp variables,
	//Now we format it to our Mesh member
	//Para cada vertice de cada triangulo:
	Mesh currentMesh;
	currentMesh.name = name;
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		guVector vertex = temp_vertices[vertexIndex - 1];
		guVector uv = temp_uvs[uvIndex - 1];
		guVector normal = temp_normals[normalIndex - 1];
		
		currentMesh.m_vertices.push_back(vertex);
		currentMesh.m_uvs.push_back(uv);
		currentMesh.m_normals.push_back(normal);
	
	}
	m_meshes.push_back(currentMesh);
	return true;
}
//Lighting
void GraphicSystem::SetLight()
{
	//@Part of update
	guVector lpos;
	GXLightObj lobj;

	lpos.x = 0.0f;
	lpos.y = 100.0f;
	lpos.z = 0.0f;
	
	//guVecMultiply(view,&lpos,&lpos);

	GX_InitLightPos(&lobj,lpos.x,lpos.y,lpos.z);
	GX_InitLightColor(&lobj,m_lightColor[0]);
	GX_LoadLightObj(&lobj,GX_LIGHT0);
	
	// set number of rasterized color channels
	GX_SetNumChans(1);
    GX_SetChanCtrl(GX_COLOR0A0,GX_ENABLE,GX_SRC_REG,GX_SRC_VTX,
	GX_LIGHT0,GX_DF_CLAMP,GX_AF_NONE);
    GX_SetChanAmbColor(GX_COLOR0A0,m_lightColor[1]);
}
//Draw calls from Update()
void GraphicSystem::DrawMeshes(std::vector<MeshComponent * > meshes){
	//Texture	
	GX_LoadTexObj(&m_paletteTexture, GX_TEXMAP0);
	//Desc
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

	//RENDER MESHES
	for (u16 i = 0 ; i < meshes.size(); i++){
		MeshComponent * mesh = meshes[i];
		TransformComponent transform = mesh->m_owner->m_transform;
		//Matrix Setup
		guMtxIdentity(m_model);
		guMtxScaleApply(m_model, m_model, transform.m_scale.x, transform.m_scale.y, transform.m_scale.z);
		Mtx tempRotMtx;
		c_guMtxQuat(tempRotMtx, &transform.m_rotation);
		guMtxConcat(m_model, tempRotMtx, m_model);
		guMtxTransApply(m_model, m_model, transform.m_position.x, transform.m_position.y, transform.m_position.z);
		guMtxConcat(m_view, m_model, m_modelview);
		// load the modelview matrix into matrix memory
		GX_LoadPosMtxImm(m_modelview, GX_PNMTX0);
		GX_LoadNrmMtxImm(m_modelview, GX_PNMTX0);
		
		//Render
		GX_Begin(GX_TRIANGLES, GX_VTXFMT1, mesh->m_vertices.size() );
		for (unsigned int i = 0; i < mesh->m_vertices.size(); i++){
			guVector vertex = mesh->m_vertices[i];
			guVector normal = mesh->m_normals[i];
			guVector uv = mesh->m_uvs[i];
			GX_Position3f32(vertex.x, vertex.y, vertex.z);
			GX_Normal3f32(normal.x,normal.y,normal.z);
			GX_TexCoord2f32(uv.x,uv.y);
		}
		GX_End();
	}
}
void GraphicSystem::DrawFonts(std::vector<FontComponent *> fonts){
	//Desc
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	
	//RENDER FONTS
	for (u16 i = 0; i < fonts.size(); i++){
		FontComponent * font = fonts[i];
		TransformComponent transform = font->m_owner->m_transform;
		//Matrix setup
		guMtxIdentity(m_model);
		//@Default scale?
		guMtxScaleApply(m_model, m_model, font->m_offsetScale, -font->m_offsetScale, font->m_offsetScale);
		guMtxScaleApply(m_model, m_model, transform.m_scale.x, transform.m_scale.y, transform.m_scale.z );
		if (font->m_rotate){
			Mtx tempRotMtx;
			c_guMtxQuat(tempRotMtx, &transform.m_rotation);
			guMtxConcat(m_model, tempRotMtx, m_model);
		}
		guMtxTransApply(m_model, m_model, transform.m_position.x, transform.m_position.y, transform.m_position.z);
		guMtxConcat(m_view, m_model, m_modelview);

		// load the modelview matrix into matrix memory
		GX_LoadPosMtxImm(m_modelview, GX_PNMTX0);
		//Render
		//@Make default arguments into flexible FontComponent m_variables.
		m_font->drawText(font->m_screenPos.x, font->m_screenPos.y, font->m_text.c_str(), font->m_color);
	}

	//RENDER MENU SELECTORS
	//DRAW MENUS
	std::vector <MenuComponent * > menuSelectors = ObjectSystem::GetInstance()->GetMenuComponentList();
	for (u16 i = 0; i < menuSelectors.size(); i++){
		MenuComponent * menu = menuSelectors[i];
		TransformComponent transform = menu->m_owner->m_transform;
		//Matrix setup
		guMtxIdentity(m_model);
		guMtxScaleApply(m_model, m_model, menu->m_offsetScale, -menu->m_offsetScale, menu->m_offsetScale );
		guMtxTransApply(m_model, m_model, transform.m_position.x, transform.m_position.y, transform.m_position.z);
		guMtxConcat(m_view, m_model, m_modelview);

		// load the modelview matrix into matrix memory
		GX_LoadPosMtxImm(m_modelview, GX_PNMTX0);
		//Render
		//@Make default arguments into flexible FontComponent m_variables.
		m_font->drawText(menu->m_screenPos.x, menu->m_screenPos.y, _TEXT(">"), (GXColor){0xff, 0x00, 0x00, 0xff});
	}

	//DEBUG FONTS
	//Logic
	while (m_stringLogs.size() > 10){
		m_stringLogs.pop_back();
	}
	//@Delete logs after certain time?
	if (m_debug){
		//Desc same as fonts
		//Calculate dirVector
		guVector dirVector;
		guVecSub(&m_look, &m_cam, &dirVector);
		guVecNormalize(&dirVector);
		guVecScale(&dirVector, &dirVector, 0.11f);

		//Matrix
		guMtxIdentity(m_model);
		guMtxScaleApply(m_model, m_model, 0.0002f, -0.0002f, 0.0002f);


		//@Calculate pitch and yaw quaternion utilizing QuatFromAxisAngle, and then multiplying them together
		//@Alternatively, use matrices and gu.h's guMtxRotAxisRad.
		Mtx tempRotMtx;
		Mtx yawMtx;
		Mtx pitchMtx;
		guMtxIdentity(tempRotMtx);
		guVector yawAxis = guVector{ 0, 1, 0 };
		guVector pitchAxis = guVector{ 1, 0, 0 };
		guMtxRotAxisRad(yawMtx, &yawAxis, m_yaw);
		guMtxRotAxisRad( pitchMtx, &pitchAxis, m_pitch);
		guMtxConcat( yawMtx, pitchMtx, tempRotMtx );
		/*@@QUATERNION APPROACH DIDNT WORK: INVESTIGATE*/
		//guQuaternion yawQuat = Math::QuatFromAxisAngle(guVector{ 0, -1, 0 }, m_yaw);
		//guQuaternion pitchQuat = Math::QuatFromAxisAngle(guVector{ -1, 0, 0 }, m_pitch);
		//c_guMtxQuat(tempRotMtx, &yawQuat);
		//c_guMtxQuat(tempRotMtx, &pitchQuat);
		guMtxConcat(m_model, tempRotMtx, m_model);
		guMtxTransApply(m_model, m_model, m_cam.x + dirVector.x , m_cam.y + dirVector.y, m_cam.z + dirVector.z);
		guMtxConcat( m_view, m_model, m_modelview );
		// Apply changes to model view matrix
		GX_LoadPosMtxImm(m_modelview,GX_PNMTX0);

		for (u16 i = 0; i < m_stringLogs.size(); i++){
			m_font->drawText(-300, -200 + i*25, m_stringLogs[i].c_str(), (GXColor){255, 255, 255, 255}, FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		}
	}
}
//EndScene
void GraphicSystem::EndDraw() {
	//Draw done (Immediate mode)
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);	
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(videoFrameBuffer[videoFrameBufferIndex], GX_TRUE);
	GX_DrawDone();
	VIDEO_SetNextFramebuffer(videoFrameBuffer[videoFrameBufferIndex]);
	VIDEO_Flush();
	//VIDEO_WaitVSync();
	videoFrameBufferIndex ^= 1;
}
//Debug
void GraphicSystem::AddLog(std::wstring log){
	m_stringLogs.insert(m_stringLogs.begin(), log);
}
void GraphicSystem::AddLog(std::string log){
	//Convert
	std::wstring wlog(log.length(), L' '); // Make room for characters
	// Copy string to wstring.
	std::copy(log.begin(), log.end(), wlog.begin());
    //Add
    AddLog(wlog);
}