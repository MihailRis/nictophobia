#ifndef NECORE_STAGE_STAGE_H_
#define NECORE_STAGE_STAGE_H_

#include <vector>

class Object;

class Stage {
	std::vector<Object*> sprites;
public:
	Stage();
	virtual ~Stage();

	Object* get(int index);
	void add(Object* object);
};

#endif /* NECORE_STAGE_STAGE_H_ */
