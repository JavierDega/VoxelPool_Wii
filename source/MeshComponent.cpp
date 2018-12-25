#include "Component/MeshComponent.h"
#include <stdio.h>
#include <string.h>

//Constructor
MeshComponent::MeshComponent(GameObject * owner, void * fileStream, unsigned int fileSize)
	: Component(owner)
{
	MakeModelFromObj(fileStream, fileSize);	
}
//Destructor
MeshComponent::~MeshComponent(){
	//Empty vectors?
	while (!out_vertices.empty()){
		out_vertices.pop_back();
	}
	while (!out_uvs.empty()){
		out_uvs.pop_back();
	}
	while (!out_normals.empty()){
		out_normals.pop_back();
	}
}
//Format obj: vertex normal list, vertex texcoord list, vertex list
//faces:(vertex,texcoord, normal)
bool MeshComponent::MakeModelFromObj(void* fileStream, unsigned int fileSize){
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
	//Now we format it to our member variables
	//Para cada vertice de cada triangulo:
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		guVector vertex = temp_vertices[vertexIndex - 1];
		guVector uv = temp_uvs[uvIndex - 1];
		guVector normal = temp_normals[normalIndex - 1];
		
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	
	}
	return true;
}
//Logic to be moved onto Systems, for a more data driven approach
void MeshComponent::Render(){
	GX_Begin(GX_TRIANGLES, GX_VTXFMT1, out_vertices.size() );
		for (unsigned int i = 0; i < out_vertices.size(); i++){
			guVector vertex = out_vertices[i];
			guVector normal = out_normals[i];
			guVector uv = out_uvs[i];
			GX_Position3f32(vertex.x, vertex.y, vertex.z);
			GX_Normal3f32(normal.x,normal.y,normal.z);
			GX_TexCoord2f32(uv.x,uv.y);
		}	
	GX_End();
}