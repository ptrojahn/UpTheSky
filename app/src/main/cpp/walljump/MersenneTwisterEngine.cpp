#include "MersenneTwisterEngine.h"

std::mt19937& getMtEngine() {
	static std::mt19937 engine(time(0));
	return engine;
}