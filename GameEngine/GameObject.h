#pragma once
#include "Globals.h"
#include <string>
#include <vector>

enum class ComponentType;
class Component;
class Transform;
class ComponentTexture;
class ComponentMesh;
class CameraComponent;

enum class GOtype {
	UI_CHECKBOX,UI_BUTTON,UI_NORMAL,NOTUI
};

class GameObject {
public:
	GOtype type;
	GameObject(bool noParent = false);
	GameObject(GameObject* Parent);
	~GameObject();
	
	bool Dragable = false;
	bool activeState = false;
	bool released = false;

	std::string subname;


	bool isEnabled = true;
	bool killMe = false;
	std::string name = "GameObject";
	
	//Pointer to transform component
	Transform* transform;

	std::vector<GameObject*> childs;

	void PrintInspector();
	void Update();

	void AddComponent(Component* component);
	
	//Returns first component of said Type, nullptr if not found
	template<class T> T* GetComponent();

	//Returns true if ALL parents are enabled
	bool isTotalEnabled();

	GameObject* getParent();

	//Returns true if <this> is under the GO hierarchy tree
	bool isChildFrom(GameObject* GO);

	//Adds GO child to current gameObject, returns false if <this> is in GO's hierarchy
	bool AddChild(GameObject* GO);

	//Removes GO from childs vector, returns true if able to do, false if it's not child
	bool RemoveChild(GameObject* GO);

	//Free <this> from parent, and set it to hierarchy child
	void Free();

	//Move <this> to GOparent, returns false if parent is <this> child
	bool MoveToParent(GameObject* GOparent);

	//Create a menu options with options for the Game Object
	bool MenuOptions();

private:
	GameObject* parent;

	std::vector<Component*> components;

	char aux[255] = {' '};

	char listComponenets[255] = {' '};

	int componentNum = 0;

	bool isSelected = false;
};