#pragma once

#include "Entity.h"
#include "LayersEngine.h"
#include "ClassId.h"

class Layer;

class System
{
public:
	System(ClassId id, int priority) : id(id), priority(priority), layer(nullptr){}
	virtual void update(LayersEngine& data) = 0;
	int getPriority() { return priority; }
	ClassId getId() { return id; }
	Layer* getLayer() { return layer; }
protected:
	int priority;
private:
	void setLayer(Layer* l) { layer = l; }
	Layer* layer;
	ClassId id;

	friend Layer;
};

template<typename TSystem>
class BaseSystem : public System
{
public:
	BaseSystem(int updatePriority) : System(classId<TSystem>(), updatePriority) {}
};