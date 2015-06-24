#pragma once

#include "value.hpp"

#include <string>

struct Object {
	std::string name;
	Value value;
};