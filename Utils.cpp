#include "Utils.h"

Color::Color(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {};

int Color::red() {
	return r;
}

int Color::green() {
	return g;
}

int Color::blue() {
	return b;
}

int Color::alpha() {
	return a;
}