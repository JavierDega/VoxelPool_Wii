#ifndef MESHCOMPONENT_H_
#define MESHCOMPONENT_H_

#include "Component/Component.h"
#include <vector>
#include <gccore.h>

//Model class
class MeshComponent : public Component{
public:
	MeshComponent(GameObject * owner, void * fileStream, unsigned int fileSize);
	virtual ~MeshComponent();
	//Messaging
	//virtual bool Receive( ComponentMessage * msg);
	//Read in .obj
	bool MakeModelFromObj(void* fileStream, unsigned int fileSize);
	void Render();
	
	//Variables
	std::vector < guVector > out_vertices;
    std::vector < guVector > out_uvs;
    std::vector < guVector > out_normals;
};
#endif /*MESHCOMPONENT_H_*/