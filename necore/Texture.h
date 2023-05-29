#ifndef NECORE_TEXTURE_H_
#define NECORE_TEXTURE_H_

class Texture {
public:
	virtual ~Texture();

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual void bind() = 0;
	virtual void setSmooth(bool flag) = 0;
};

#endif /* NECORE_TEXTURE_H_ */
