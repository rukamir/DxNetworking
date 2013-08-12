//#include "SoundManager.h"
//
//SoundManager::SoundManager()
//{
//	result = FMOD::System_Create(&system);
//	//ERRCHECK(result);
//
//	result = system->init(100, FMOD_INIT_NORMAL, 0);
//	//ERRCHECK(result);
//
//	result = system->createSound("Audio/MIRRORMIRROR- Wishing Never Works (woomwood).wav", FMOD_HARDWARE, 0, &sound);
//	result = system->createSound("Audio/67357__bidone__tiger.mp3", FMOD_HARDWARE, 0, &soundTiger);
//	result = system->createSound("Audio/12812__jilliancallahan__generic-prop-idle.wav", FMOD_HARDWARE, 0, &soundPlane);
//	result = system->createSound("Audio/MIRRORMIRROR- train rough.wav", FMOD_HARDWARE, 0, &soundGame);
//
//	//set sound to loop
//	sound->setMode(FMOD_LOOP_NORMAL);
//	soundPlane->setMode(FMOD_LOOP_NORMAL);
//	soundGame->setMode(FMOD_LOOP_NORMAL);
//	//ERRCHECK(result);
//}
//
//void SoundManager::PlaySong()
//{
//	result = system->playSound(FMOD_CHANNEL_FREE, sound, 0, &channel);
//	result = channel->setVolume(0.25f);		// Set the volume while it is paused.
//	//ERRCHECK(result);
//	result = channel->setPaused(false);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
//
//void SoundManager::ResumeSong()
//{
//	result = channel->setPaused(false);		// This is where the sound really starts.
//	//ERRCHECK(result);
//
//	//FMOD_BOOL p;
// //   FMOD_Channel_GetPaused(channel,&p);
// //   FMOD_Channel_SetPaused(channel,!p);
//}
//
//void SoundManager::PauseSong()
//{
//	result = channel->setPaused(true);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
//
//
//void SoundManager::Update()
//{
//	//to be updated once per frame
//	system->update();
//}
//
//void SoundManager::PlayTigerSound()
//{
//	result = system->playSound(FMOD_CHANNEL_FREE, soundTiger, 0, &channelTiger);
//	result = channelTiger->setVolume(1.0f);		// Set the volume while it is paused.
//	//ERRCHECK(result);
//	result = channelTiger->setPaused(false);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
//
//void SoundManager::PlayPlaneSound()
//{
//	result = system->playSound(FMOD_CHANNEL_FREE, soundPlane, 0, &channelPlane);
//	result = channelPlane->setVolume(0.4f);		// Set the volume while it is paused.
//	//ERRCHECK(result);
//	result = channelPlane->setPaused(false);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
//
//void SoundManager::PausePlaneSound()
//{
//	result = channelPlane->setPaused(true);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
//
//void SoundManager::PlayGameSound()
//{
//	result = system->playSound(FMOD_CHANNEL_FREE, soundGame, 0, &channelGame);
//	result = channelGame->setVolume(0.5f);		// Set the volume while it is paused.
//	//ERRCHECK(result);
//	result = channelGame->setPaused(false);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
//
//void SoundManager::PauseGameSound()
//{
//	result = channelGame->setPaused(true);		// This is where the sound really starts.
//	//ERRCHECK(result);
//}
