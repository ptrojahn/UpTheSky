#include "helper.h"

bool intersect(Vector2<float> pos1, Vector2<float> size1, Vector2<float> pos2, Vector2<float> size2) {
	return pos1.x < pos2.x + size2.x
		&& pos1.x + size1.x > pos2.x
		&& pos1.y < pos2.y + size2.y
		&& pos1.y + size1.y > pos2.y;
}