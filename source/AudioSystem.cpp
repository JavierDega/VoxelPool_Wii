#include "System/AudioSystem.h"

#include "PoolHallJam_320_110bpm_mp3.h"
#include "PoolHallJam_128kb_120bpm_mp3.h"

using namespace std;

AudioSystem * AudioSystem::m_instance = NULL; //@Null at compile time

AudioSystem * AudioSystem::GetInstance(){
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new AudioSystem();
	}
	return m_instance;
}
//@Constructor
AudioSystem::AudioSystem(){
	// Initialise the audio subsystem
	ASND_Init();
	MP3Player_Init();
}
//@Destructor
AudioSystem::~AudioSystem(){


}
//@Initialize (called on every scene load)
void AudioSystem::Initialize(){

}
void AudioSystem::Update( float dt ){

}
//@Messaging
void AudioSystem::SendMessage(ComponentMessage msg ){

}
//Utility
void AudioSystem::PlayMusic(unsigned int index){
	if (MP3Player_IsPlaying()) MP3Player_Stop();
	switch (index){
		case 0:
		//@Song 0
		MP3Player_PlayBuffer(PoolHallJam_128kb_120bpm_mp3, PoolHallJam_128kb_120bpm_mp3_size, NULL);
		break;
		default:
		break;
	}
}