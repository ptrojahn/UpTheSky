#include "AudioManager.h"

#include <SDL.h>

#ifdef ANDROID
#include <SLES/OpenSLES_Android.h>
#endif

AudioManager::AudioManager() : mute(false) {
#ifdef ANDROID
	SLObjectItf engineObject;
	slCreateEngine(&engineObject, 0, nullptr, 0, nullptr, nullptr);
	(*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	(*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engine);
	(*engine)->CreateOutputMix(engine, &outputMix, 0, nullptr, nullptr);
	(*outputMix)->Realize(outputMix, SL_BOOLEAN_FALSE);

	//Get the AssetManager through jni
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();
	jobject activity = (jobject)SDL_AndroidGetActivity();
	jclass contextClass = jni->FindClass("android/content/Context");
	jmethodID getResources = jni->GetMethodID(contextClass, "getResources", "()Landroid/content/res/Resources;");
	jclass resourcesClass = jni->FindClass("android/content/res/Resources");
	jmethodID getAssets = jni->GetMethodID(resourcesClass, "getAssets", "()Landroid/content/res/AssetManager;");
	jobject assetManagerObject = jni->CallObjectMethod(jni->CallObjectMethod(activity, getResources), getAssets);
	assetManager = AAssetManager_fromJava(jni, assetManagerObject);
#endif
}

AudioAsset AudioManager::loadAudio(std::string path) {
#ifdef ANDROID
	for (AudioData* data : audioData){
		if (data->path == path)
			return data;
	}

	AudioData* newData = new AudioData();
	newData->path = path;

	AAsset* audioAsset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
	off_t start, length;
	int allocated = AAsset_openFileDescriptor(audioAsset, &start, &length);

	SLDataLocator_AndroidFD dataLocator = {SL_DATALOCATOR_ANDROIDFD, allocated, start, length};
	SLDataFormat_MIME formatMime = { SL_DATAFORMAT_MIME, nullptr, SL_CONTAINERTYPE_UNSPECIFIED };
	SLDataSource source = {&dataLocator, &formatMime};

	SLDataLocator_OutputMix outMix = {SL_DATALOCATOR_OUTPUTMIX, outputMix};
	SLDataSink sink = { &outMix, nullptr };

	(*engine)->CreateAudioPlayer(engine, &newData->player, &source, &sink, 0, nullptr, nullptr);
	(*newData->player)->Realize(newData->player, SL_BOOLEAN_FALSE);
	(*newData->player)->GetInterface(newData->player, SL_IID_PLAY, &newData->playInterface);
	audioData.push_back(newData);
	return audioData.back();
#else
	return 0;
#endif
}

void AudioManager::playAudio(AudioAsset asset) {
#ifdef ANDROID
	if(!mute){
		//The player needs to be stopped before it can be restarted
		(*asset->playInterface)->SetPlayState(asset->playInterface, SL_PLAYSTATE_STOPPED);
		(*asset->playInterface)->SetPlayState(asset->playInterface, SL_PLAYSTATE_PLAYING);
	}
#endif
}