#include "DebugSystem.h"

#include "rursus_compact_mono_ttf.h"	// Include the compiled font.

//Instance
DebugSystem * DebugSystem::m_instance = NULL;
DebugSystem * DebugSystem::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new DebugSystem();
	}
	return m_instance;
}
//Constructor
DebugSystem::DebugSystem() {

	m_isEnabled = false;
	
	//Init font
	//Font
	m_debugFont = new FreeTypeGX(GX_TF_IA8, GX_VTXFMT0);
	m_debugFont->setCompatibilityMode(FTGX_COMPATIBILITY_DEFAULT_TEVOP_GX_MODULATE
	| FTGX_COMPATIBILITY_DEFAULT_VTXDESC_GX_DIRECT);//BLEND AND TEX DIRECT
	FT_UInt fontSize = 15;
	m_debugFont->loadFont(rursus_compact_mono_ttf, rursus_compact_mono_ttf_size, fontSize, false);	// Initialize the font system with the font parameters from rursus_compact_mono_ttf.h
	
	
	
	//Set default logs
	std::wstring log = L"Default string log";
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
	m_stringLogs.insert(m_stringLogs.begin(), log);
}

//Destructor
DebugSystem::~DebugSystem() {
	//Debug system is persistent, and only deleted at application quit.
	m_isEnabled = false;
	
	//Delete font
	//Font
	delete m_debugFont;
	
	//Delete vector 
	//Safety check
	while (!m_stringLogs.empty()) {
		//Remove from vector
		m_stringLogs.pop_back();
	}

}

void DebugSystem::SetFontTransform(GraphicsSystem * gs){
	//Position: view's camera origin + X units in look direction
	//Desc
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

	//For now lets put matrix transformations here
	guMtxIdentity(gs->model);
	guMtxScaleApply(gs->model, gs->model, 0.0004f, -0.0004f, 0.0004f);
	guMtxTransApply(gs->model, gs->model, gs->cam.x,gs->cam.y,gs->cam.z -0.11f);
	guMtxConcat(gs->view,gs->model,gs->modelview);
	// Apply changes to model view matrix
	GX_LoadPosMtxImm(gs->modelview,GX_PNMTX0);
}

void DebugSystem::AddLog(std::wstring log){
	m_stringLogs.insert(m_stringLogs.begin(), log);
}
//Update logs?Remove extra logs
void DebugSystem::Update(){
	
	while (m_stringLogs.size() > 10){
		m_stringLogs.pop_back();
	}

}

void DebugSystem::Render(){
	
	if (m_isEnabled){
		m_debugFont->drawText(-150, -115, m_stringLogs[0].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff}, FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, -100, m_stringLogs[1].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, -85, m_stringLogs[2].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, -70, m_stringLogs[3].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, -55, m_stringLogs[4].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, -40, m_stringLogs[5].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);	
		m_debugFont->drawText(-150, -25, m_stringLogs[6].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, -10, m_stringLogs[7].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, 5, m_stringLogs[8].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
		m_debugFont->drawText(-150, 20, m_stringLogs[9].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff},	FTGX_ALIGN_TOP | FTGX_JUSTIFY_LEFT);
	}

}