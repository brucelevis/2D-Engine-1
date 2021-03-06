#pragma once

#include "Module.h"
#include "ResourceAnimation.h"
#include "ResourceScript.h"
#include "ResourceSprite.h"
#include "ResourceMusic.h"
#include "ResourceSound.h"
#include "ResourceParticleEffect.h"

class ModuleResources : public Module
{
public:

	ModuleResources();
	virtual ~ModuleResources();

	bool Awake();
	bool CleanUp();

	vector<ResourceAnimation*> GetGameAnimationsList();
	vector<ResourceScript*> GetGameScriptsList();
	vector<ResourceSprite*> GetGameSpritesList();
	vector<ResourceSound*> GetGameSoundsList();
	vector<ResourceMusic*> GetGameMusicList();
	vector<ResourceParticleEffect*> GetGameParticleFXList();

	void AddResourceAnimation(ResourceAnimation* anim);
	void AddResourceScript(ResourceScript* script);
	void AddResourceSprite(ResourceSprite* sprite);
	void AddResourceSound(ResourceSound* sound);
	void AddResourceMusic(ResourceMusic* music);
	void AddResourceParticleFX(ResourceParticleEffect* particleFX);

	void* DrawResourcesWindow(Resource::ResourceType type);
	bool IsResourcesWindowOpen(Resource::ResourceType type);
	void SetResourcesWindowOpen(Resource::ResourceType type, bool open);

public:
	string isOpenFromPanel; //Panel that opens the resource window

private:
	vector<ResourceAnimation*> gameAnimationsList;
	vector<ResourceScript*> gameScriptsList;
	vector<ResourceSprite*> gameSpritesList;
	vector<ResourceSound*> gameSoundsList;
	vector<ResourceMusic*> gameMusicList;
	vector<ResourceParticleEffect*> gameParticleFXList;

	bool resourcesWindowIsOpen = false;
	bool animationsWindowIsOpen = false;
	bool spritesWindowIsOpen = false;
	bool scriptsWindowIsOpen = false;
	bool soundsWindowIsOpen = false;
	bool musicsWindowIsOpen = false;
	bool particleFXWindowIsOpen = false;
};

