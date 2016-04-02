#pragma once

typedef unsigned int ClassId;

class ClassIdManager{
public:
	template<class TClass>
	static ClassId getId() {
		static ClassId id = nextClassId++;
		return id;
	}
private:
	static ClassId nextClassId;
};

template<typename TClass>
static ClassId classId() {
	return ClassIdManager::getId<TClass>();
}