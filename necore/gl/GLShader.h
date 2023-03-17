#ifndef NECORE_GLSHADER_H_
#define NECORE_GLSHADER_H_

#include <string>
#include "../Shader.h"

class GLShader : public Shader {
	unsigned int program;
public:
	GLShader(unsigned int program);
	virtual ~GLShader();

	void use();
	void uniformMatrix(std::string name, glm::mat4 matrix);
	void uniform1i(std::string name, int x);
	void uniform1f(std::string name, float x);
	void uniform2f(std::string name, float x, float y);
	void uniform3f(std::string name, float x, float y, float z);

	static Shader* create(std::string vertexFile, std::string fragmentFile);
};

#endif /* NECORE_GLSHADER_H_ */
