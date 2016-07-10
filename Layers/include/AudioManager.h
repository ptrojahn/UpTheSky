#pragma once

#include <string>
#include <vector>
#ifdef ANDROID
#include <SLES/OpenSLES.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif

struct AudioData
{
#ifdef ANDROID
	std::string path;
	SLObjectItf player;
	SLPlayItf playInterface;
#endif
};
typedef AudioData* AudioAsset;

class AudioManager
{
public:
	static AudioManager& instance() {
		static AudioManager audioManager;
		return audioManager;
	}
	AudioManager();
	AudioAsset loadAudio(std::string path);
	void playAudio(AudioAsset asset);
	void setMute(bool isMute) { mute = isMute; }
	bool isMute() { return mute; }
private:
	std::vector<AudioData> audioData;
#ifdef ANDROID
	AAssetManager* assetManager;
	SLEngineItf engine;
	SLObjectItf outputMix;
#endif
	bool mute;
};