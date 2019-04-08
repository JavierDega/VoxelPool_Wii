#ifndef AUDIOSYSTEM_H_
#define AUDIOSYSTEM_H_

#include "System/System.h"
#include <asndlib.h>
#include <mp3player.h>

class AudioSystem : public System {
	private:
	/*Here will be the instance stored*/
	static AudioSystem* m_instance;
	/*Private constructor to prevent instancing*/
	AudioSystem();
	public:
	~AudioSystem();
	//Singleton
	static AudioSystem* GetInstance();	
	//Funcs
	//Events
	void Initialize();
	void Update( float dt );
	void SendMessage(ComponentMessage msg);
	//Utility
	void PlayMusic(unsigned int index);
	//Variables
};

#endif /*AUDIOSYSTEM_H_*/