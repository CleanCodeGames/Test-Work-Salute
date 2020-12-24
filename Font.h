#pragma once
#include "Define.h"

struct Font
{
	sf::Font common;
	sf::Font erica_type;

	Font() {
		cout << "Font Loaded\n";
		common.loadFromFile("./resources/fonts/common.ttf");
		erica_type.loadFromFile("./resources/fonts/erica_type.ttf");
	}

	~Font() {

	}
};