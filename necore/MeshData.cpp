#include "MeshData.h"

#include <iostream>

MeshData::MeshData(std::string name, std::vector<float> data, uint vertexSize)
	: name(name), data(data), vertexSize(vertexSize) {
}

std::string MeshData::getName() const {
	return name;
}

uint MeshData::getVertexSize() const {
	return vertexSize;
}

const std::vector<float>& MeshData::getData() const {
	return data;
}
