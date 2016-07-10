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
	void putBoolean(const char* name, bool value);
	int getBoolean(const char* name, bool defaultValue = false);
	void apply();
private:
#ifdef ANDROID
	jobject sharedPrefs;
	jobject sharedPrefsEditor;
	jmethodID putIntMethod;
	jmethodID getIntMethod;
	jmethodID putBooleanMethod;
	jmethodID getBooleanMethod;
	jmethodID applyMethod;
#endif
};