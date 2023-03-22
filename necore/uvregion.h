#ifndef NECORE_UVREGION_H_
#define NECORE_UVREGION_H_


struct uvregion {
	float u1;
	float v1;
	float u2;
	float v2;

	uvregion(float u1, float v1, float u2, float v2)
	: u1(u1), v1(v1), u2(u2), v2(v2){}

	uvregion() : u1(0.0f), v1(0.0f), u2(1.0f), v2(1.0f){}
};


#endif /* NECORE_UVREGION_H_ */
