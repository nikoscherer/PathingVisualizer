#pragma once

class Color {
	int r;
	int b;
	int g;
	int a;

public:
	Color(int _r, int _g, int _b, int _a);

	int red();
	int green();
	int blue();
	int alpha();
};