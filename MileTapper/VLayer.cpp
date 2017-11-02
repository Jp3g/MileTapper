#include "VLayer.hpp"

namespace MileTapper {
	VLayer::VLayer(const std::string& type, int z, bool isStatic) : _type(type), _z(z), _isStatic(isStatic) {

	}

	VLayer::~VLayer() {

	}

	int VLayer::z() const {
		return _z;
	}

	const std::string& VLayer::getType() const {
		return _type;
	}

	bool VLayer::isStatic() const {
		return _isStatic;
	}
}