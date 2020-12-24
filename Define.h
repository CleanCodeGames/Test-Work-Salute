#pragma once
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>
#include <memory>
#include <cmath>
#include <list>

#include "SFML/Graphics.hpp"

static constexpr auto PI  = 3.141592;
static constexpr auto DEG = 57.29582;
static constexpr auto RAD = 0.017453;

class Base;
typedef Base B;
using std::cout;
using std::endl;
using std::to_string;
using std::cos;
using std::sin;
using std::make_shared;
using std::make_unique;

using std::list;
using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

typedef unsigned int uint;
typedef sf::Vector2i v2i;
typedef sf::Vector2f v2f;
typedef sf::Keyboard Key;
typedef sf::RectangleShape Shape;
typedef sf::Texture IMG;
typedef sf::Color Color;
