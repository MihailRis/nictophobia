#include "iopath.h"

using namespace std;

iopath::iopath(string data) {
	string::size_type position = data.find(':', 0);
	_label = data.substr(0, position);
	_path = data.substr(position+1, data.length());

}

iopath::iopath(string label, string path) : _label(label), _path(path) {
}


iopath iopath::child(std::string name) const {
	if (name[name.length()-1] == '/') {
		name = name.substr(0, name.length()-1);
	}
	if (!_path.length()) {
		return iopath(_label, name);
	}
	return iopath(_label, _path+"/"+name);
}

iopath iopath::parent() const {
	if (!_path.length()) {
		return *this;
	}
	string::size_type position = _path.rfind('/');
	if (position == string::npos) {
		return iopath(_label, "");
	}
	return iopath(_label, _path.substr(0, position));
}

string iopath::name() const {
	string::size_type position = _path.rfind('/');
	if (position == string::npos) {
		return _path;
	}
	return _path.substr(position+1, _path.length());
}

string iopath::extension() const {
	string::size_type sposition = _path.rfind('/');
	string::size_type position = _path.rfind('.');
	if (position == string::npos) {
		return "";
	}
	if (sposition != string::npos && position < sposition) {
		return "";
	}
	return _path.substr(position+1, _path.length());
}

string iopath::nameNoExt() const {
	string::size_type sposition = _path.rfind('/');
	string::size_type position = _path.rfind('.');
	if (position == string::npos) {
		if (sposition == string::npos) {
			return _path;
		} else {
			return _path.substr(sposition+1, _path.length());
		}
	} else {
		if (sposition == string::npos) {
			return _path.substr(0, position);
		} else if (position > sposition){
			return _path.substr(sposition+1, position);
		} else {
			return _path.substr(sposition+1, _path.length());
		}
	}
}
