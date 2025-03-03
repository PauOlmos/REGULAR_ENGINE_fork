#include "Application.h"
#include "ModuleUI.h"
#include "ModuleMesh.h"
#include "ComponentMesh.h"
#include "Hierarchy.h"
#include "ComponentTexture.h"
#include "Primitives.h"
#include "ComponentCamera.h"
#include "Transform.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	UICam = new CameraComponent(ComponentType::UICAMERA);
	UICam->frustum.pos = float3( 0,0,0 );
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	return UPDATE_CONTINUE;
}

GameObject* ModuleUI::CreateUI(UIType GOtype)
{
	GameObject* GO = new GameObject();
	GO->Dragable = true;
	ComponentMesh* cm = new ComponentMesh();
	ComponentTexture* ct = new ComponentTexture();
	//ct->SetTexture("Assets\crosshair.png");
	Mesh* m = nullptr;

	switch (GOtype) {
	case UIType::NORMAL:
		GO->name = "UI Plane";
		m = Primitives::CreateCube();
		GO->type = GOtype::UI_NORMAL;
		GO->AddComponent(ct);
		Application::GetInstance()->hierarchy->selectedGameObj = GO;
		if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr) {

			ComponentTexture* ct = Application::GetInstance()->hierarchy->selectedGameObj->GetComponent<ComponentTexture>();
		}
		if (ct == nullptr) {
			ct = new ComponentTexture();
			Application::GetInstance()->hierarchy->selectedGameObj->AddComponent(ct);
		}
		GO->transform->setScale({ 350,300,1 });

		ct->SetTexture("Assets/Baker_house.png");
		break;
	case UIType::CHECKBOX:
		GO->name = "UI CheckBox";
		m = Primitives::CreateCube();
		GO->type = GOtype::UI_CHECKBOX; 
		GO->AddComponent(ct);
		Application::GetInstance()->hierarchy->selectedGameObj = GO;
		if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr) {

			ComponentTexture* ct = Application::GetInstance()->hierarchy->selectedGameObj->GetComponent<ComponentTexture>();
		}
		if (ct == nullptr) {
			ct = new ComponentTexture();
			Application::GetInstance()->hierarchy->selectedGameObj->AddComponent(ct);
		}
		GO->transform->setScale({ 200,200,1 });
		ct->SetTexture("Assets/red.png");
		break;
	case UIType::BUTTON:
		GO->name = "UI Button";
		m = Primitives::CreateCube();
		GO->transform->setScale({ 300,150,1 });
		GO->type = GOtype::UI_BUTTON;
		GO->AddComponent(ct);

		break;
	}

	m->myGameObject = GO;
	//Create AABB box
	m->InitAABB();
	m->Mtype = MESHtype::UI;
	cm->meshes.push_back(m);
	GO->AddComponent(cm);
	Application::GetInstance()->meshRenderer->LoadMesh(m);
	return GO;
}

GameObject* ModuleUI::CreateUICrosshair(UIType GOtype)
{
	GameObject* GO = new GameObject();
	GO->type = GOtype::UI_NORMAL;
	GO->Dragable = true;
	ComponentMesh* cm = new ComponentMesh();
	ComponentTexture* ct = new ComponentTexture();
	Mesh* m = nullptr;

	switch (GOtype) {
	case UIType::NORMAL:
		GO->name = "UI Plane";
		m = Primitives::CreateCube();
		break;
	}

	m->myGameObject = GO;

	//Create AABB box
	m->InitAABB();
	m->Mtype = MESHtype::UI;
	cm->meshes.push_back(m);
	GO->AddComponent(cm);
	GO->AddComponent(ct);
	GO->transform->setPosition({ 0,0,0 });
	GO->transform->setScale({ 100,100,1 });
	Application::GetInstance()->meshRenderer->LoadMesh(m);
	return GO;
}

