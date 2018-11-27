#include "ModelMesh.h"
#include <stdio.h>
#include <string.h>
#include <gccore.h>
ModelMesh::ModelMesh()
{
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;
}


//Format obj: vertex normal list, vertex texcoord list, vertex list
//faces:(vertex,texcoord, normal)
bool ModelMesh::MakeModelFromObj(void* fileStream, unsigned int fileSize){
	
	//Temp variables
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< Vec3 > temp_vertices;
	std::vector< Vec2 > temp_uvs;
	std::vector< Vec3 > temp_normals;
	
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
			Vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			Vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			Vec3 normal;
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
		
		Vec3 vertex = temp_vertices[vertexIndex - 1];
		Vec2 uv = temp_uvs[uvIndex - 1];
		Vec3 normal = temp_normals[normalIndex - 1];
		
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	
	}
	return true;
}

void ModelMesh::Render(){

	GX_Begin(GX_TRIANGLES, GX_VTXFMT0, out_vertices.size() );
		
		for (unsigned int i = 0; i < out_vertices.size(); i++){
			
			Vec3 vertex = out_vertices[i];
			Vec2 uv = out_uvs[i];
			
			GX_Position3f32(vertex.x, vertex.y, vertex.z);
			GX_Color3f32(0.0f,0.0f,0.0f);
			GX_TexCoord2f32(uv.x,uv.y);
		
		}	

	GX_End();
							

}