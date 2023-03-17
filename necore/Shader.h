#ifndef NECORE_SHADER_H_
#define NECORE_SHADER_H_

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	virtual ~Shader();

	virtual void use() = 0;
	virtual void uniformMatrix(std::string name, glm::mat4 matrix) = 0;
	virtual void uniform1i(std::string name, int x) = 0;
	virtual void uniform1f(std::string name, float x) = 0;
	virtual void uniform2f(std::string name, float x, float y) = 0;
	virtual void uniform3f(std::string name, float x, float y, float z) = 0;
};

#endif /* NECORE_SHADER_H_ */
