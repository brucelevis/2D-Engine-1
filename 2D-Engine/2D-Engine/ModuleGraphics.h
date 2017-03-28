#pragma once

#include "Module.h"

class ModuleGraphics : public Module
{
public:
	ModuleGraphics();
	virtual ~ModuleGraphics();

	bool Update(float deltaTime);
	bool CleanUp();

	sf::Texture LoadTexture(const char* path);
	sf::CircleShape* CreateShape();

private:
	list<sf::Drawable*> drawableObjectsList;
};
