#pragma once

#ifdef ANDROID
#include "jni.h"
#endif

class SharedPreferences
{
public:
	static SharedPreferences& getSharedPreferences() {
		static SharedPreferences sp;
		return sp;
	}
	SharedPreferences();
	void putInt(const char* name, int value);
	int getInt(const char* name, int defaultValue = 0);
	void apply();
private:
#ifdef ANDROID
	JNIEnv* jni;
	jobject sharedPrefs;
	jobject sharedPrefsEditor;
	jmethodID putIntMethod;
	jmethodID getIntMethod;
	jmethodID applyMethod;
#endif
};