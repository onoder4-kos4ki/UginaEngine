#include "uginaDontDestroyOnLoad.h"

ugina::DontDestroyOnLoad::DontDestroyOnLoad()
{
}

ugina::DontDestroyOnLoad::~DontDestroyOnLoad()
{
}

void ugina::DontDestroyOnLoad::Initialize()
{
	Scene::Initialize();
}

void ugina::DontDestroyOnLoad::Update()
{
	Scene::Update();
}

void ugina::DontDestroyOnLoad::LateUpdate()
{
Scene:: LateUpdate();
}

void ugina::DontDestroyOnLoad::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void ugina::DontDestroyOnLoad::OnEnter()
{
	Scene::OnEnter();
}

void ugina::DontDestroyOnLoad::OnExit()
{
	Scene::OnExit();
}
