#ifndef NECORE_IMAGE_H_
#define NECORE_IMAGE_H_


class Image {
public:
	virtual ~Image(){};
	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;
};


#endif /* NECORE_IMAGE_H_ */
