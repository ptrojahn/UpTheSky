#include "SharedPreferences.h"

#include <SDL.h>

SharedPreferences::SharedPreferences() {
#ifdef ANDROID
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();

	jclass prefManagerClass = jni->FindClass("android/preference/PreferenceManager");
	jclass prefManagerEditorClass = jni->FindClass("android/content/SharedPreferences$Editor");
	jclass sharedPreferencesClass = jni->FindClass("android/content/SharedPreferences");

	jmethodID defaultPrefMethod = jni->GetStaticMethodID(prefManagerClass, "getDefaultSharedPreferences", "(Landroid/content/Context;)Landroid/content/SharedPreferences;");
	sharedPrefs = jni->NewGlobalRef(jni->CallStaticObjectMethod(prefManagerClass, defaultPrefMethod, (jobject)SDL_AndroidGetActivity()));
	jmethodID getEditorMethod = jni->GetMethodID(sharedPreferencesClass, "edit", "()Landroid/content/SharedPreferences$Editor;");
	sharedPrefsEditor = jni->NewGlobalRef(jni->CallObjectMethod(sharedPrefs, getEditorMethod));

	putIntMethod = jni->GetMethodID(prefManagerEditorClass, "putInt", "(Ljava/lang/String;I)Landroid/content/SharedPreferences$Editor;");
	getIntMethod = jni->GetMethodID(sharedPreferencesClass, "getInt", "(Ljava/lang/String;I)I");
	putBooleanMethod = jni->GetMethodID(prefManagerEditorClass, "putBoolean", "(Ljava/lang/String;Z)Landroid/content/SharedPreferences$Editor;");
	getBooleanMethod = jni->GetMethodID(sharedPreferencesClass, "getBoolean", "(Ljava/lang/String;Z)Z");
	applyMethod = jni->GetMethodID(prefManagerEditorClass, "apply", "()V");

	jni->DeleteLocalRef(prefManagerClass);
	jni->DeleteLocalRef(prefManagerEditorClass);
	jni->DeleteLocalRef(sharedPreferencesClass);
#endif
}

void SharedPreferences::putInt(const char* name, int value) {
#ifdef ANDROID
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();
	jstring prefName = jni->NewStringUTF(name);
	jni->DeleteLocalRef(jni->CallObjectMethod(sharedPrefsEditor, putIntMethod, prefName, value));
	jni->DeleteLocalRef(prefName);
#endif
}

int SharedPreferences::getInt(const char* name, int defaultValue) {
#ifdef ANDROID
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();
	jstring prefName = jni->NewStringUTF(name);
	int result = jni->CallIntMethod(sharedPrefs, getIntMethod, prefName, defaultValue);
	jni->DeleteLocalRef(prefName);
	return result;
#else
	return defaultValue;
#endif
}

void SharedPreferences::putBoolean(const char* name, bool value) {
#ifdef ANDROID
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();
	jstring prefName = jni->NewStringUTF(name);
	jni->DeleteLocalRef(jni->CallObjectMethod(sharedPrefsEditor, putBooleanMethod, prefName, value));
	jni->DeleteLocalRef(prefName);
#endif
}

bool SharedPreferences::getBoolean(const char* name, bool defaultValue) {
#ifdef ANDROID
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();
	jstring prefName = jni->NewStringUTF(name);
	bool result = jni->CallBooleanMethod(sharedPrefs, getBooleanMethod, prefName, defaultValue);
	jni->DeleteLocalRef(prefName);
	return result;
#else
	return defaultValue;
#endif
}

void SharedPreferences::apply() {
#ifdef ANDROID
	JNIEnv* jni = (JNIEnv*)SDL_AndroidGetJNIEnv();
	jni->CallVoidMethod(sharedPrefsEditor, applyMethod);
#endif
}