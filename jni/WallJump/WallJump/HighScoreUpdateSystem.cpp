#include "HighScoreUpdateSystem.h"

#include "GameLayer.h"
#include "PlayerLayer.h"
#include "ScoreComponent.h"
#include "HighScoreComponent.h"
#include "UniformsComponent.h"
#include "SharedPreferences.h"

#include <string>

void HighScoreUpdateSystem::update(LayersEngine& engine) {
	//Get highscore and score entity
	if (!engine.getLayer<GameLayer>()->isEnabled()){
		for (Entity* highScore : engine.getEntities()){
			HighScoreComponent* highScoreComponent = highScore->getComponent<HighScoreComponent>();
			if (highScoreComponent && !highScoreComponent->updated){
				for (Entity* score : engine.getEntities()){
					if (score->getComponent<ScoreComponent>()){
						if (*(int*)&score->getComponent<UniformsComponent>()->uniforms[0].data[0] > *(int*)&highScore->getComponent<UniformsComponent>()->uniforms[0].data[0]){
							//Update and save highscore
							UniformsComponent* uniforms = highScore->getComponent<UniformsComponent>();
							*(int*)&uniforms->uniforms[0].data[0] = *(int*)&score->getComponent<UniformsComponent>()->uniforms[0].data[0];
							*(int*)&uniforms->uniforms[1].data[0] = std::to_string(*(int*)&uniforms->uniforms[0].data[0]).length();
							SharedPreferences::getSharedPreferences().putInt("highScore", *(int*)&score->getComponent<UniformsComponent>()->uniforms[0].data[0]);
							SharedPreferences::getSharedPreferences().apply();
							break;
						} else if (*(int*)&highScore->getComponent<UniformsComponent>()->uniforms[0].data[0] == 0){
							//The game started: Load highscore from SharedPreferences
							highScoreComponent->updated = true;
							UniformsComponent* uniforms = highScore->getComponent<UniformsComponent>();
							*(int*)&uniforms->uniforms[0].data[0] = SharedPreferences::getSharedPreferences().getInt("highScore", 0);
							*(int*)&uniforms->uniforms[1].data[0] = std::to_string(*(int*)&uniforms->uniforms[0].data[0]).length();
							break;
						}
					}
				}
			}
		}
	}
}