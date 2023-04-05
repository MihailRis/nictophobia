#ifndef NECORE_NECORE_H_
#define NECORE_NECORE_H_

class NeContext;

class Necore {
public:
	Necore();
	virtual ~Necore();

	void mainloop(NeContext* context);
};

#endif /* NECORE_NECORE_H_ */
