cmake_minimum_required(VERSION 3.4.1)

project(layers)

include_directories(layers/include)
include_directories(../../SDL2/include)
include_directories(layers/include/GLES2)
include_directories(layers/include/KHR)

link_directories(../../jniLibs/${ANDROID_ABI})

add_library(layers STATIC
            layers/AnimationSystem.cpp
            layers/AudioManager.cpp
            layers/BufferManager.cpp
            layers/ButtonSystem.cpp
            layers/ClassId.cpp
            layers/Entity.cpp
            layers/glFunctions.cpp
            layers/Layer.cpp
            layers/LayersEngine.cpp
            layers/OnUpdateSystem.cpp
            layers/OnWaitFinishedSystem.cpp
            layers/RenderSystem.cpp
            layers/ShaderManager.cpp
            layers/SharedPreferences.cpp
            layers/TextureManager.cpp

            layers/include/AnimationComponent.h
            layers/include/AnimationSystem.h
            layers/include/AudioManager.h
            layers/include/BufferManager.h
            layers/include/ButtonComponent.h
            layers/include/ButtonSystem.h
            layers/include/ClassId.h
            layers/include/Component.h
            layers/include/Entity.h
            layers/include/gl2.h
            layers/include/glFunctions.h
            layers/include/Layer.h
            layers/include/LayersEngine.h
            layers/include/Matrix4x4.h
            layers/include/OnBackPressedComponent.h
            layers/include/OnLayerDisabledComponent.h
            layers/include/OnLayerEnabledComponent.h
            layers/include/OnUpdateComponent.h
            layers/include/OnUpdateSystem.h
            layers/include/OnWaitFinishedComponent.h
            layers/include/OnWaitFinishedSystem.h
            layers/include/RenderComponent.h
            layers/include/RenderSystem.h
            layers/include/ShaderManager.h
            layers/include/SharedPreferences.h
            layers/include/System.h
            layers/include/TextureComponent.h
            layers/include/TextureManager.h
            layers/include/TransformComponent.h
            layers/include/UniformsComponent.h
            layers/include/Vector2.h
            layers/include/Vector3.h)

target_link_libraries(layers SDL2 OpenSLES android)
