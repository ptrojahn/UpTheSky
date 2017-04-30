cmake_minimum_required(VERSION 3.4.1)

project(main)

add_subdirectory(src/main/cpp/layers)
include_directories(src/main/cpp/layers/layers/include)
include_directories(src/main/SDL2/include)

link_directories(src/main/jniLibs/${ANDROID_ABI})

add_library(main SHARED
            src/main/cpp/walljump/AnimationsCommon.cpp
            src/main/cpp/walljump/BackgroundLayer.cpp
            src/main/cpp/walljump/CloudSystem.cpp
            src/main/cpp/walljump/GameLayer.cpp
            src/main/cpp/walljump/GameOverlayLayer.cpp
            src/main/cpp/walljump/GhostWall.cpp
            src/main/cpp/walljump/helper.cpp
            src/main/cpp/walljump/HorizontalScrollSystem.cpp
            src/main/cpp/walljump/LevelManagerSystem.cpp
            src/main/cpp/walljump/MainMenuLayerGraphics.cpp
            src/main/cpp/walljump/MainMenuLayerLogic.cpp
            src/main/cpp/walljump/MersenneTwisterEngine.cpp
            src/main/cpp/walljump/main.cpp
            src/main/cpp/walljump/ParticleSystem.cpp
            src/main/cpp/walljump/PlayerLayer.cpp
            src/main/cpp/walljump/PlayerSystem.cpp
            src/main/cpp/walljump/ScrollSystem.cpp
            src/main/cpp/walljump/ShopLayerGraphics.cpp
            src/main/cpp/walljump/ShopLayerLogic.cpp
            src/main/SDL2/src/main/android/SDL_android_main.c)

target_link_libraries(main libSDL2.so layers)