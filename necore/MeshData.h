#ifndef NECORE_MESHDATA_H_
#define NECORE_MESHDATA_H_

#include <string>
#include <vector>
#include "common.h"

class MeshData {
	std::string name;
	std::vector<float> data;
	uint vertexSize;
public:
	MeshData(std::string name, std::vector<float> data, uint vertexSize);
	std::string getName() const;
	uint getVertexSize() const;
	const std::vector<float>& getData() const;
};

#endif /* NECORE_MESHDATA_H_ */
