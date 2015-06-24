#pragma once

#include <string>

//forward declaration
class Object;

enum Type {
	T_STRING,
	T_NUMBER,
	T_OBJECT,
	T_ARRAY,
	T_TRUE,
	T_FALSE,
	T_NUL
};

struct String {
	Type type = Type::T_STRING;
	std::string str; //NOTE: easier to use std::string
};

struct Number {
	Type type = Type::T_NUMBER;
	double num;
};

struct Object {
	Type type = Type::T_OBJECT;
	Object* obj;
};

struct Array {
	Type type = Type::T_ARRAY;
	int size;
	Object* head;
};

union Value {
	Type type;
	String string;
	Number number;
	Object object;
	Array array;
};
