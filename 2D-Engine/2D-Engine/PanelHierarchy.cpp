#include "PanelHierarchy.h"
#include "GameObject.h"
#include "Engine.h"
#include "ModuleSceneManager.h"
#include "ModuleInput.h"
#include "ModuleRenderWindow.h"


PanelHierarchy::PanelHierarchy()
{
	active = true;
	panelName = "Hierarchy Panel";
	panelPosition = { 0,20 };
	panelWidth = 200;
	panelHeight = 400;
}


PanelHierarchy::~PanelHierarchy()
{
}

void PanelHierarchy::DrawPanel()
{
	ImGui::Begin("Hierarchy", &active,
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_HorizontalScrollbar | 
		ImGuiWindowFlags_AlwaysAutoResize | 
		ImGuiWindowFlags_NoCollapse | 
		ImGuiWindowFlags_ShowBorders );
		
	if (ImGui::IsMouseClicked(1) && ImGui::IsMouseHoveringWindow()) {
		ImGui::OpenPopup("GameObject Options");
	}

	if (ImGui::BeginPopup("GameObject Options"))
	{
		if (!engine->sceneManagerModule->selectedGameObjects.empty()) {
			if (ImGui::MenuItem("Copy")) {
				for (list<GameObject*>::iterator it = engine->sceneManagerModule->selectedGameObjects.begin(); it != engine->sceneManagerModule->selectedGameObjects.end(); it++) {
					engine->sceneManagerModule->CopyGameObject(*it);
				}
			}
			if (ImGui::MenuItem("Duplicate")) {
				for (list<GameObject*>::iterator it = engine->sceneManagerModule->selectedGameObjects.begin(); it != engine->sceneManagerModule->selectedGameObjects.end(); it++) {
					engine->sceneManagerModule->DuplicateGameObject(*it);
				}
			}
			if (ImGui::MenuItem("Delete")) {
				for (list<GameObject*>::iterator it = engine->sceneManagerModule->selectedGameObjects.begin(); it != engine->sceneManagerModule->selectedGameObjects.end(); it++) {
					(*it)->Destroy();
				}
			}
			if (engine->sceneManagerModule->selectedGameObjects.size() == 1) {
				if (ImGui::MenuItem("Rename")) {
					showRenameWindow = true;
				}
				if (ImGui::MenuItem("Create Child Game Object")) {
					GameObject* parent = nullptr;
					if (engine->sceneManagerModule->selectedGameObjects.size() == 1) {
						parent = engine->sceneManagerModule->selectedGameObjects.front();
					}
					engine->sceneManagerModule->CreateGameObject(parent);
				}
			}
			else{
				if (ImGui::MenuItem("Create Game Object")) {
					engine->sceneManagerModule->CreateGameObject(nullptr);
				}
			}
		}
		else {
			if (ImGui::MenuItem("Create Game Object")) {
				engine->sceneManagerModule->CreateGameObject(nullptr);
			}
		}
		
		ImGui::EndPopup();
	}

	if (showRenameWindow) {
		ImGui::Begin("Rename", &active,
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_ShowBorders |
			ImGuiWindowFlags_NoTitleBar);

		ImGui::Text("Enter new name");

		char a[20];
		ImGui::InputText("", a, 20);
		if (ImGui::Button("Confirm")) {
			engine->sceneManagerModule->selectedGameObjects.front()->Rename(a);
			showRenameWindow = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			showRenameWindow = false;
		}
		ImGui::End();
	}

	for (list<GameObject*>::iterator it = engine->sceneManagerModule->sceneRootObjects.begin(); it != engine->sceneManagerModule->sceneRootObjects.end(); it++) {
		DrawChilds(*it);
	}
	
	ImGui::End();
	
}

void PanelHierarchy::DrawChilds(GameObject* gameObject)
{
	unsigned int flag = 0;

	if (!gameObject->childs.empty()) {
		flag = ImGuiTreeNodeFlags_Leaf;
	}
	
	for (list<GameObject*>::iterator it = engine->sceneManagerModule->selectedGameObjects.begin(); it != engine->sceneManagerModule->selectedGameObjects.end(); it++) {
		if (gameObject == *it) {
			flag = ImGuiTreeNodeFlags_Selected;
			break;
		}
	}

	if (ImGui::TreeNodeEx(gameObject->name.c_str(), flag))
	{
		CheckMouseHover(gameObject);
		for (list<GameObject*>::iterator it = gameObject->childs.begin(); it != gameObject->childs.end(); ++it) {
			DrawChilds(*it);
		}

		ImGui::TreePop();
	}
	else {
		CheckMouseHover(gameObject);
	}
	
}

void PanelHierarchy::CheckMouseHover(GameObject* gameObject)
{
	if (ImGui::IsMouseClicked(0)) {
		if (ImGui::IsItemHoveredRect())
		{
			list<GameObject*>::iterator it;

			if (!engine->sceneManagerModule->selectedGameObjects.empty()) {
				it = find(engine->sceneManagerModule->selectedGameObjects.begin(), engine->sceneManagerModule->selectedGameObjects.end(), gameObject);
				if (it != engine->sceneManagerModule->selectedGameObjects.end()) {
					if (!engine->inputModule->IsKeyRepeated(sf::Keyboard::LControl)) {
						engine->sceneManagerModule->selectedGameObjects.remove(gameObject);
					}
				}
				else {
					engine->sceneManagerModule->selectedGameObjects.push_back(gameObject);
				}
			}
			else {
				engine->sceneManagerModule->selectedGameObjects.push_back(gameObject);
			}
		}
		else {
			if (ImGui::IsMouseHoveringWindow()) {
				if (!engine->inputModule->IsKeyRepeated(sf::Keyboard::LControl) && !engine->sceneManagerModule->selectedGameObjects.empty() &&
					!showRenameWindow) {
					engine->sceneManagerModule->selectedGameObjects.remove(gameObject);
				}
			}
		}
	}

	if (ImGui::IsMouseDoubleClicked(0))
	{
		if (ImGui::IsItemHoveredRect())
		{
			if (!showRenameWindow) {
				showRenameWindow = true;
			}
		}
	}
	
}

void PanelHierarchy::Resize(float w, float h)
{
	panelWidth += w;
	panelHeight += h;
}