#ifndef MESHCOMPONENT_H_
#define MESHCOMPONENT_H_
#include <vector>
#include "Component.h"

//Handle Structs
typedef struct Vector3Str{
	float x,y,z;
}Vec3;

typedef struct Vector2Str{
	float x,y;
}Vec2;

//Model class
class MeshComponent : public Component{
public:
	MeshComponent(GameObject * owner, void * fileStream, unsigned int fileSize);
	//Messaging
	//virtual bool Receive( ComponentMessage * msg);
	//Read in .obj
	bool MakeModelFromObj(void* fileStream, unsigned int fileSize);
	void Render();
	
	//Variables
	std::vector < Vec3 > out_vertices;
    std::vector < Vec2 > out_uvs;
    std::vector < Vec3 > out_normals;
};
#endif /*MESHCOMPONENT_H_*/