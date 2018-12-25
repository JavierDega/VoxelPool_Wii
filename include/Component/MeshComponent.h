#ifndef MESHCOMPONENT_H_
#define MESHCOMPONENT_H_

#include "Component/Component.h"
#include <vector>
#include <gccore.h>

//Model class
class MeshComponent : public Component{
public:
	//@Files to be taken from GraphicSystem, utilizing string name indexing
	MeshComponent(GameObject * owner, void * fileStream, unsigned int fileSize);
	virtual ~MeshComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg);
	//Read in .obj
	bool MakeModelFromObj(void* fileStream, unsigned int fileSize);
	void Render();
	
	//Variables
	std::vector < guVector > m_vertices;
    std::vector < guVector > m_uvs;
    std::vector < guVector > m_normals;
};
#endif /*MESHCOMPONENT_H_*/