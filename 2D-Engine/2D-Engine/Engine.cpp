#include "Engine.h"
#include "ModuleRenderWindow.h"
#include "ModuleInput.h"
#include "ModuleGraphics.h"
#include "ModuleAudio.h"
#include "ModuleEditor.h"
#include "ModuleSceneManager.h"


Engine::Engine()
{
	modulesList.push_back(renderWindowModule = new ModuleRenderWindow());
	modulesList.push_back(inputModule = new ModuleInput());
	modulesList.push_back(graphicsModule = new ModuleGraphics());
	modulesList.push_back(audioModule = new ModuleAudio());
	modulesList.push_back(editorModule = new ModuleEditor());
	modulesList.push_back(sceneManagerModule = new ModuleSceneManager());
	
}


Engine::~Engine()
{
	for (list<Module*>::iterator it = modulesList.begin(); it != modulesList.end(); it++) {
		if ((*it) != NULL)
		{
			delete (*it);
			(*it) = NULL;
		}
	}

	modulesList.clear();
}

bool Engine::Awake()
{
	bool ret = false;
	for (list<Module*>::iterator it = modulesList.begin(); it != modulesList.end(); it++) {
		ret = (*it)->Awake();
	}
	return ret;
}

bool Engine::Start()
{
	bool ret = false;
	for (list<Module*>::iterator it = modulesList.begin(); it != modulesList.end(); it++) {
		ret = (*it)->Start();
	}
	return ret;
}

bool Engine::DoUpdate()
{
	bool ret = true;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = Update();

	if (ret == true)
		ret = PostUpdate();

	if (quit) ret = false;

	return ret;
}

bool Engine::PostUpdate()
{
	bool ret = true;
	for (list<Module*>::iterator it = modulesList.begin(); it != modulesList.end(); it++)
	{
		if ((*it)->enable)
			ret = (*it)->PostUpdate();
	}

	return ret;
}

bool Engine::CleanUp()
{
	return true;
}

bool Engine::PreUpdate()
{
	time = clock.restart();
	deltaTime = time.asSeconds();

	bool ret = true;
	for (list<Module*>::iterator it = modulesList.begin(); it != modulesList.end(); it++)
	{
		if ((*it)->enable)
			ret = (*it)->PreUpdate();
	}

	return ret;
}

bool Engine::Update()
{
	bool ret = true;
	for (list<Module*>::iterator it = modulesList.begin(); it != modulesList.end(); it++)
	{
		if ((*it)->enable)
			ret = (*it)->Update(deltaTime);
	}

	return ret;
}
