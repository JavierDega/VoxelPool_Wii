#ifndef OBJECTSYSTEM_H_
#define OBJECTSYSTEM_H_

#include "System/System.h"
#include "GameObject.h"
#include "Component/MeshComponent.h"
#include "Component/FontComponent.h"
#include "Component/MenuComponent.h"
#include "Extra/Math.h"
#include <vector>

///OBJECT FACTORY/ STORES POINTERS TO GAMEOBJECTS AND ALLOWS US TO FILTER COMPONENTS
//FOR THE DIFFERENT SYSTEMS
class ObjectSystem : public System {
	private:
	/*Here will be the instance stored*/
	static ObjectSystem * m_instance;
	/*Private constructor to prevent instancing*/
	ObjectSystem();
	public:
	~ObjectSystem();
	//Singleton
	static ObjectSystem * GetInstance();	
	
	///Functions
	//Events
	void Initialize();
	void Update( float dt );
	//Utility
	void LoadScene(int sceneIndex);
	GameObject * AddObject(std::string name = "Default name", guVector position = guVector{ 0, 0, 0 }, guQuaternion rotation = Math::QuatIdentity,
		guVector scale = guVector{ 1, 1, 1 } );
	void RemoveAllObjects();
	void RemoveObject( GameObject * object );
	std::vector< MeshComponent * > GetMeshComponentList();
	std::vector< FontComponent * > GetFontComponentList();
	std::vector< LogicComponent * > GetLogicComponentList();
	std::vector< MenuComponent * > GetMenuComponentList();
	
	///MEMORY MANAGEMENT
	/*typedef struct pool
	{
	  char * next;
	  char * end;
	} POOL;

	POOL * pool_create( size_t size ) {
	    POOL * p = (POOL*)malloc( size + sizeof(POOL) );
	    p->next = (char*)&p[1];
	    p->end = p->next + size;
	    return p;
	}

	void pool_destroy( POOL *p ) {
	    free(p);
	}

	size_t pool_available( POOL *p ) {
	    return p->end - p->next;
	}

	void * pool_alloc( POOL *p, size_t size ) {
	    if( pool_available(p) < size ) return NULL;
	    void *mem = (void*)p->next;
	    p->next += size;
	    return mem;
	}*/

	//Variables
	std::vector<GameObject> m_objectList;
};

#endif /*OBJECTSYSTEM_H_*/