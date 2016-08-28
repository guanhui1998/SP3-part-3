#include "MainMenu.h"
#include "GL\glew.h"
#include "Application.h"

#define InputDelay 0.1f

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

//void MainMenu::Init(CCharacter* Character, Buttons* button, bool *quitegame)
void MainMenu::Init(Buttons* button, bool *quitegame)
{
	SceneBase::Init();

	StartOp = Start;
	startArrow = 0;

	m_objectCount = 0;
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	gamestate = Menu;
	InputDelayTimer = 0;
	quitGame = false;
	//this->Character = Character;
	this->button = button;
	m_quitgame = quitegame;

	button->PlayButton->active = true;
    button->PlayButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 13, 0.f);
  
//  button->EditButton->active = true;
//  button->EditButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 26, 0.f);
  
//  button->LoadButton->active = true;
//  button->LoadButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 39, 0.f);
  
//  button->ExitButton->active = true;
//  button->ExitButton->pos.Set(m_worldWidth / 14, m_worldHeight - 10, 0.f);
}

GameObject* MainMenu::FetchGO()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		std::vector<GameObject *>::iterator it2 = it;
		if (!go->active)
		{
			go->Init();
			go->active = true;


			++m_objectCount;
			return go;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(go);
	}
	GameObject *go = m_goList.back();
	go->active = true;
	++m_objectCount;
	return go;
}

void MainMenu::Update(double dt)
{
	if (InputDelayTimer > 0)
		InputDelayTimer -= dt;

	if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
	{
		InputDelayTimer = InputDelay;
		if (startArrow != END - 1)
		{
			startArrow++;
		}
		else
			startArrow = 0;
	}
	if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
	{
		InputDelayTimer = InputDelay;
		if (startArrow != 0)
			startArrow--;
		else
			startArrow = END - 1;
	}

	switch (startArrow)
	{
	case Start:
		if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			gamestate = Game;
		}
		break;
	}

	switch (gamestate)
	{
	case Edit:
		break;

	case Menu:
		if (button->isClick == true && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;

			switch (button->button->type)
			{
			case(GameObject::GO_PLAYHOVER) :
				gamestate = Game;
				break;

			case(GameObject::GO_LOADHOVER) :
				break;

			case(GameObject::GO_EDITHOVER) :
				gamestate = Edit;
				break;

			case(GameObject::GO_EXITHOVER) :
				*m_quitgame = true;
				//Application::Exit();
				break;
			}
		}
		break;

	case Load:
		break;

	case Pause:
		if (button->isClick == true && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;

			switch (button->button->type)
			{
			case(GameObject::GO_PLAYHOVER) :
				gamestate = Game;
				break;

			case(GameObject::GO_MENUHOVER) :
				gamestate = Menu;
				break;
				
			case(GameObject::GO_EXITHOVER) :
				*m_quitgame = true;
				break;
			}
		}
		break;

	case Game:
		if (playerDead == true)
		{
			if (button->isClick == true && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;

				switch (button->button->type)
				{
				case(GameObject::GO_RESTARTHOVER) :
					playerDead = false;
					gamestate = Game;
					break;

				case(GameObject::GO_MENUHOVER) :
					playerDead = false;
					gamestate = Menu;
					break;

				case(GameObject::GO_EXITHOVER) :
					playerDead = false;
					*m_quitgame = true;
					break;
				}
			}
		}

		if (Application::IsKeyPressed('P') && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			gamestate = Pause;
		}

		if (Application::IsKeyPressed('O') && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			gamestate = End;
		}
		break;

	case End:
		if (button->isClick == true && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;

			switch (button->button->type)
			{
			case(GameObject::GO_MENUHOVER) :
				gamestate = Menu;
				break;

			case(GameObject::GO_EXITHOVER) :
				*m_quitgame = true;
				break;
			}
		}
	}
}

void MainMenu::RenderMenu(MapLoad* m_cMap)
{

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	if (gamestate == Menu)
	{
		modelStack.PushMatrix();
		//RenderModelOnScreen(meshList[GEO_PLAYERHP], false, Vector3(Character->Attribute->GetCurrentHP() * 0.2f, 2.f, 0.f), 50.f - (157.f - (float)Character->Attribute->GetCurrentHP())*0.1f, 57.7f, 1.f, Vector3(0.f, 0.f, 0.f));
		//modelStack.Translate(50.f - (157.f - (float)Character->Attribute->GetCurrentHP())*0.1f, 57.7f, 1.f);
		//modelStack.Scale(Character->Attribute->GetCurrentHP() * 0.2f, 2.f, 0.f);
		//RenderMesh(meshList[GEO_PLAYERHP], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		modelStack.Scale(180, 100, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(10.f, 10.f, 0.f);
		modelStack.Scale(10.f, 13.f, 0.f);
		RenderMesh(meshList[GEO_PRINCESS], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->PlayButton->pos.x, button->PlayButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_PLAY], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->ExitButton->pos.x, button->ExitButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_EXIT], false);
		modelStack.PopMatrix();

		switch (startArrow)
		{
		case(Start) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 13.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->PlayButton->pos.x, button->PlayButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_PLAYHOVER], false);
			modelStack.PopMatrix();
			break;

		case(Instructions) :
			modelStack.PushMatrix();
			modelStack.Translate(30.f, 25.f, 0.f);
			modelStack.Scale(5.f, 5.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();
			break;

		case (Quit) :
			modelStack.PushMatrix();
			modelStack.Translate(30.f, 20.f, 0.f);
			modelStack.Scale(5.f, 5.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();
			break;
		}

	}

	if (gamestate == Game)
	{
		//button->PlayButton->pos.Set(-20, -20, 0);
		button->EditButton->pos.Set(-20, -20, 0);
		button->LoadButton->pos.Set(-20, -20, 0);
		button->ExitButton->pos.Set(-20, -20, 0);
		button->RestartButton->pos.Set(-20, -20, 0);
		button->MenuButton->pos.Set(-20, -20, 0);
		button->SaveButton->pos.Set(-20, -20, 0);
	
		if (playerDead == true)
		{
			button->RestartButton->active = true;
			button->RestartButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30.f) / 2 + camera.position.y, 1.f);
			button->MenuButton->active = true;
			button->MenuButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 60.f) / 2 + camera.position.y, 1.f);
			button->ExitButton->active = true;
			button->ExitButton->pos.Set(16.f + camera.position.x, 94.f + camera.position.y, 1.f);
		
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
			modelStack.Scale(180, 110, 0);
			RenderMesh(meshList[GEO_DEATHSCREEN], false);
			modelStack.PopMatrix();

			button->EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
			button->LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
			button->PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		}
	}

	if (gamestate == Pause)
	{
		button->LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		button->PlayButton->active = true;
		button->PlayButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30.f) / 2 + camera.position.y, 1.f);
		button->MenuButton->active = true;
		button->MenuButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 60.f) / 2 + camera.position.y, 1.f);
		button->ExitButton->active = true;
		button->ExitButton->pos.Set(16.f + camera.position.x, 94.f + camera.position.y, 1.f);

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_PAUSEUI], false);
		modelStack.PopMatrix();
	}

	if (gamestate == End)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_VICTORY], false);
		modelStack.PopMatrix();

		button->PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->RestartButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		button->MenuButton->active = true;
		button->MenuButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30.f) / 2 + camera.position.y, 1.f);

		button->ExitButton->active = true;
		button->ExitButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 60.f) / 2 + camera.position.y, 1.f);
	}

	if (gamestate == Edit)
	{
		button->PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->ExitButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->RestartButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->MenuButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		button->SaveButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_EDITBACKGROUND], false);
		modelStack.PopMatrix();
	}

	/*for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);

		}
	}*/
}

void MainMenu::RenderGO(GameObject* go)
{

	Vector3 temp;
	switch (go->type)
	{
	case(GameObject::GO_PLAY) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		//RenderMesh(meshList[GEO_PLAY], false);
		Render2DMesh(meshList[GEO_PLAY], false, 10.f, go->pos.x, go->pos.y, false, false);
		break;

	case(GameObject::GO_PLAYHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_PLAYHOVER], false);
		break;

	case(GameObject::GO_MENU) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MENU], false);
		break;

	case(GameObject::GO_MENUHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MENUHOVER], false);
		break;

	case(GameObject::GO_EDIT) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EDIT], false);
		break;

	case(GameObject::GO_EDITHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EDITHOVER], false);
		break;

	case(GameObject::GO_LOAD) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_LOAD], false);
		break;

	case(GameObject::GO_LOADHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_LOADHOVER], false);
		break;

	case(GameObject::GO_HIGHSCORE) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_HIGHSCORE], false);
		break;

	case(GameObject::GO_HIGHSCOREHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_HIGHSCOREHOVER], false);
		break;

	case(GameObject::GO_SAVE) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SAVE], false);
		break;

	case(GameObject::GO_SAVEHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SAVEHOVER], false);
		break;

	case(GameObject::GO_EXIT) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EXIT], false);
		break;

	case(GameObject::GO_EXITHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EXITHOVER], false);
		break;

	case(GameObject::GO_RESTART) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_RESTART], false);
		break;

	case(GameObject::GO_RESTARTHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_RESTARTHOVER], false);
		break;

	case(GameObject::GO_OKAY) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_OKAY], false);
		break;

	case(GameObject::GO_OKAYHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_OKAYHOVER], false);
		break;


	default:
		break;
	}
	modelStack.PopMatrix();
}