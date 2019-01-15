#ifndef MESHCOMPONENT_H_
#define MESHCOMPONENT_H_

#include "Component/Component.h"
#include <vector>
#include <gccore.h>
#include <string>

//Model class
class MeshComponent : public Component{
public:
	//Funcs
	//@Files to be taken from GraphicSystem, utilizing string name indexing
	MeshComponent(std::string name);
	virtual ~MeshComponent();
	//Messaging
	virtual bool Receive( ComponentMessage msg ) { return false;} ;
	bool FetchModel(std::string name);
	
	//Variables
	std::vector < guVector > m_vertices;
    std::vector < guVector > m_uvs;
    std::vector < guVector > m_normals;
};
#endif /*MESHCOMPONENT_H_*/