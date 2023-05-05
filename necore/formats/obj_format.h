#ifndef NECORE_FORMATS_OBJ_FORMAT_H_
#define NECORE_FORMATS_OBJ_FORMAT_H_

#include <string>
#include <vector>
#include <memory>

struct obj_mesh {
	std::string name;
	std::vector<float> data;
};

struct obj_object {
	std::string name;
	std::vector<obj_mesh> meshes;
};

std::vector<obj_object> load_obj_model(const std::string& content);


#endif /* NECORE_FORMATS_OBJ_FORMAT_H_ */
