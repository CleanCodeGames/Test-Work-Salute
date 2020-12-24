#pragma once
#include "Define.h"

class Texture
{
private:

	IMG Load(const string file, bool isSmooth = false) {
		IMG texture;
		texture.loadFromFile("./resources/images/" + file);
		texture.setSmooth(isSmooth);
		return texture;
	}

public:

	IMG background;

	Texture() {
		
	}
	
	void LoadLevel_0() {
		cout << "Texture Loaded: [Level 0]\n";
		background = Load("background.jpg");

		//for (int i = 0; i < NUM_EFFECTS; i++) \
			effects.push_back(Load("effects/effect" + to_string(i) + ".png"));
	}

	void LoadLevel_1() {
		// Code load textures for level 1
	}

	void ClearMemory() {
		// effects.clear();
		// clear vectors code...
	}

	~Texture(void) {
	}
};