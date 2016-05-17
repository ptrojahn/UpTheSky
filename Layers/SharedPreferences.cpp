#include "SharedPreferences.h"

#include <SDL.h>

SharedPreferences::SharedPreferences() {
#ifdef ANDROID
	jni = (JNIEnv*)SDL_AndroidGetJNIEnv();

	jclass prefManagerClass = jni->FindClass("android/preference/PreferenceManager");
	jclass prefManagerEditorClass = jni->FindClass("android/content/SharedPreferences$Editor");
	jclass sharedPreferencesClass = jni->FindClass("android/content/SharedPreferences");

	jmethodID defaultPrefMethod = jni->GetStaticMethodID(prefManagerClass, "getDefaultSharedPreferences", "(Landroid/content/Context;)Landroid/content/SharedPreferences;");
	sharedPrefs = jni->CallStaticObjectMethod(prefManagerClass, defaultPrefMethod, (jobject)SDL_AndroidGetActivity());
	jmethodID getEditorMethod = jni->GetMethodID(sharedPreferencesClass, "edit", "()Landroid/content/SharedPreferences$Editor;");
	sharedPrefsEditor = jni->CallObjectMethod(sharedPrefs, getEditorMethod);

	putIntMethod = jni->GetMethodID(prefManagerEditorClass, "putInt", "(Ljava/lang/String;I)Landroid/content/SharedPreferences$Editor;");

	getIntMethod = jni->GetMethodID(sharedPreferencesClass, "getInt", "(Ljava/lang/String;I)I");

	applyMethod = jni->GetMethodID(prefManagerEditorClass, "apply", "()V");
#endif
}

void SharedPreferences::putInt(const char* name, int value) {
#ifdef ANDROID
	jstring prefName = jni->NewStringUTF(name);
	jni->CallObjectMethod(sharedPrefsEditor, putIntMethod, prefName, value);
#endif
}

int SharedPreferences::getInt(const char* name, int defaultValue) {
#ifdef ANDROID
	jstring prefName = jni->NewStringUTF(name);
	return jni->CallIntMethod(sharedPrefs, getIntMethod, prefName, defaultValue);
#else
	return defaultValue;
#endif
}

void SharedPreferences::apply() {
#ifdef ANDROID
	jni->CallVoidMethod(sharedPrefsEditor, applyMethod);
#endif
}