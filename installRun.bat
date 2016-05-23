call adb push bin/SDLActivity-debug.apk /sdcard/
call adb shell pm install -r /sdcard/SDLActivity-debug.apk
call adb shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity