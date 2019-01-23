#include "Component/MeshComponent.h"
#include "System/GraphicSystem.h"
#include <stdio.h>

//Constructor
MeshComponent::MeshComponent(std::string name)
{
	//Copy contents from GSystem
	if(!FetchModel(name))GraphicSystem::GetInstance()->AddLog("Couldn't find model!: " + name);
}
//Destructor
MeshComponent::~MeshComponent(){
	//Empty vectors?
	while (!m_vertices.empty()){
		m_vertices.pop_back();
	}
	while (!m_uvs.empty()){
		m_uvs.pop_back();
	}
	while (!m_normals.empty()){
		m_normals.pop_back();
	}
}
//Fetch mesh from GraphicSystem
bool MeshComponent::FetchModel(std::string name){
	GraphicSystem * gs = GraphicSystem::GetInstance();
	for (u16 i = 0; i < gs->m_meshes.size(); i++){
		if (gs->m_meshes[i].name.compare(name) == 0){
			GraphicSystem::GetInstance()->AddLog("Found model: " + name);
			//Both names are equal
			m_vertices = gs->m_meshes[i].m_vertices;
			m_uvs = gs->m_meshes[i].m_uvs;
			m_normals = gs->m_meshes[i].m_normals;
			return true;
		}
	}
	//Model not found
	return false;
}
