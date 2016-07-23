call adb push bin/UpTheSky-debug.apk /sdcard/
call adb shell pm install -r /sdcard/UpTheSky-debug.apk
call adb shell am start -n de.paultrojahn.UpTheSky/de.paultrojahn.UpTheSky.UpTheSkyActivity