#include <vector>

//Handle Structs
typedef struct Vector3Str{
	float x,y,z;
}Vec3;

typedef struct Vector2Str{
	float x,y;
}Vec2;

//Model class
class ModelMesh{
public:
	ModelMesh();
	ModelMesh(void * fileStream, unsigned int fileSize);
	//Read in obj
	bool MakeModelFromObj(void* fileStream, unsigned int fileSize);
	void Render();
	
	//Variables
	std::vector < Vec3 > out_vertices;
    std::vector < Vec2 > out_uvs;
    std::vector < Vec3 > out_normals;
	
	Vec3 m_position;
};
