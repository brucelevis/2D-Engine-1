#include "ModuleSceneWindow.h"
#include "ComponentTransform.h"
#include "ComponentSpriteRenderer.h"
#include "GameObject.h"
#include "ModuleInput.h"
#include "ModuleEngineWindow.h"


ModuleSceneWindow::ModuleSceneWindow()
{
	moduleName = windowName = "Game Scene";
	windowSize = { 400, 400 };
	
}

ModuleSceneWindow::ModuleSceneWindow(sf::Vector2i size)
{
	moduleName = windowName = "Game Scene";
	windowSize = size;
}


ModuleSceneWindow::~ModuleSceneWindow()
{
}

bool ModuleSceneWindow::Awake()
{
	//window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), windowName, sf::Style::None);
	//window->setFramerateLimit(60);
	window = new sf::RenderTexture();

	if (!window->create(windowSize.x, windowSize.y))
		return -1;
	return true;
}

bool ModuleSceneWindow::PreUpdate()
{
	//window->clear(sf::Color::White);
	if (engine->inputModule->IsKeyRepeated(sf::Keyboard::A)) {
		sf::View view = window->getView();
		view.zoom(1.1f);
		window->setView(view);
	}
	return true;
}

bool ModuleSceneWindow::PostUpdate()
{
	//window->clear(sf::Color::White);
	//for (int i = 0; i < drawableObjects.size(); i++) {
	//	if (drawableObjects[i]->isActive()) {
	//		window->draw(*drawableObjects[i]->gameObjectSprite);
	//	}
	//}
	//window->display();

	return true;
}

bool ModuleSceneWindow::CleanUp()
{
	delete window;

	return true;
}

void ModuleSceneWindow::Resize(uint width, uint height)
{
	sf::View view = window->getView();
	//cout << window->getDefaultView().getSize().x << endl;

	window->create(width, height);
	window->clear(sf::Color::White);
	window->setView(window->getDefaultView());
	for (int i = 0; i < drawableObjects.size(); i++) {
		if (drawableObjects[i]->isActive()) {
			drawableObjects[i]->gameObjectSprite->setColor(sf::Color::White);
			window->draw(*drawableObjects[i]->gameObjectSprite);
		}
	}
	if (engine->inputModule->IsKeyRepeated(sf::Keyboard::A)) {
		view.zoom(1.1f);
	}
	window->setView(view);

	window->display();
}
