#include "obj_format.h"

#include <string_view>
#include <sstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

size_t split(const std::string &text, std::vector<std::string> &strings, char ch) {
	strings.clear();
    size_t pos = text.find(ch);
    size_t initialPos = 0;
    strings.clear();

    while (pos != std::string::npos) {
        strings.push_back(text.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = text.find(ch, initialPos);
    }

    strings.push_back(text.substr(initialPos, std::min(pos, text.size()) - initialPos + 1));
    return strings.size();
}

struct vertex_data {
	vector<float> v;
	vector<float> vt;
	vector<float> vn;
};

obj_mesh build_obj_mesh(vertex_data vdata, vector<string>& lines, size_t& pos) {
	string line = lines[pos++];
	string mtlname = line.substr(7, line.length());

	vector<string> tokens;
	vector<string> subtokens;
	vector<float> buffer;
	while (pos < lines.size()) {
		line = lines[pos];
		if (line[0] == 'f' && line[1] == ' ') {
			// face
			split(line, tokens, ' ');
			for (unsigned int i = 0; i < 3; i++) {
				// build vertex from 3 indices
				split(tokens[i+1], subtokens, '/');
				int vidx = stoi(subtokens[0])-1;
				for (int j = 0; j < 3; j++) {
					buffer.push_back(vdata.v[vidx*3+j]);
				}
				int tidx = stoi(subtokens[1])-1;
				for (int j = 0; j < 2; j++) {
					buffer.push_back(vdata.vt[tidx*2+j]);
				}
				int nidx = stoi(subtokens[2])-1;
				for (int j = 0; j < 3; j++) {
					buffer.push_back(vdata.vn[nidx*3+j]);
				}
			}
		}
		pos++;
	}
	return {mtlname, buffer};
}

obj_object load_obj_object(vector<string> lines, size_t& pos) {
	string line = lines[pos];
	string name = line.substr(2, line.length());
	vector<obj_mesh> meshes;

	vertex_data vdata;

	vector<string> tokens;

	while (pos < lines.size()) {
		line = lines[pos];
		if (line[0] == 'v' && line[1] == ' ') {
			split(line, tokens, ' ');
			for (unsigned int i = 1; i <= 3; i++) {
				vdata.v.push_back(std::stof(tokens[i]));
			}
		} else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			split(line, tokens, ' ');
			vdata.vt.push_back(std::stof(tokens[1]));
			vdata.vt.push_back(std::stof(tokens[2]));
		} else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			split(line, tokens, ' ');
			for (unsigned int i = 1; i <= 3; i++) {
				vdata.vn.push_back(std::stof(tokens[i]));
			}
		} else if (line[0] == 'u' && line[1] == 's'){
			obj_mesh mesh = build_obj_mesh(vdata, lines, pos);
			meshes.push_back(mesh);
		}
		pos++;
	}

	return {name, meshes};
}

vector<obj_object> load_obj_model(const string& content) {
	vector<obj_object> objects;
	vector<obj_mesh> meshes;

	vector<std::string> lines;
	stringstream ss(content);
	string line;
	while (getline(ss, line, '\n')) {
		lines.push_back(line);
	}

	size_t position = 0;
	for (size_t i = 0; i < lines.size(); i++) {
		line = lines[i];
		if (line[0] == 'o' && line[1] == ' ') {
			position++;
			obj_object obj = load_obj_object(lines, position);
			objects.push_back(obj);
			continue;
		}
	}

	return objects;
}
