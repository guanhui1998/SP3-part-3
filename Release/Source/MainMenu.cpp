#include "MainMenu.h"
#include "GL\glew.h"
#include "Application.h"

#define InputDelay 0.1f

MainMenu::MainMenu() : QuitGame(false), RestartGame(false)
{

}

MainMenu::~MainMenu()
{
    while (m_goList.size() > 0)
    {
        GameObject* go = m_goList.back();
        delete go;
        m_goList.pop_back();
    }
    SceneBase::Exit();
}

//void MainMenu::Init(CCharacter* Character, Buttons* button, bool *quitegame)
void MainMenu::Init(Buttons* button, CCharacter* character)
{
	SceneBase::Init();
	
	// Start Options for arrow
	StartOp = Start;
	startArrow = 0;
	// Pause Options for arrow
	PauseOp = Resume;
	pauseArrow = 0;
	// Dead options for arrow
	DeadOp = Restart;
	deadArrow = 0;
	// Win options for arrow
	WinOp = ReturnMenu4;
	winArrow = 0;

	m_objectCount = 0;
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	gamestate = Menu;
	InputDelayTimer = 0;
	this->Character = character;
	this->button = button;
	playerDead = false;
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


	if (gamestate == Menu)
	{
		button->PlayButton->active = true;
		button->PlayButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 13, 0.f);

		button->HelpButton->active = true;
		button->HelpButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 26, 0.f);

		button->ExitButton->active = true;
		button->ExitButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 39, 0.f);
	}

	if (gamestate == Pause)
	{
		button->ResumeButton->active = true;
		button->ResumeButton->pos.Set(m_worldWidth / 2, m_worldHeight / 2, 0.f);

		button->MenuButton->active = true;
		button->MenuButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 13, 0.f);

		button->ExitButton->active = true;
		button->ExitButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 26, 0.f);
	}

	if (gamestate == End)
	{
		button->RestartButton->active = true;
		button->RestartButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 26.f, 0.f);

		button->MenuButton->active = true;
		button->MenuButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 39.f, 0.f);
	}

	if (gamestate == Win)
	{
		button->MenuButton->active = true;
		button->MenuButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 26.f, 0.f);

		button->ExitButton->active = true;
		button->ExitButton->pos.Set(m_worldWidth / 2, (m_worldHeight / 2) - 39.f, 0.f);
	}

	if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
	{
		InputDelayTimer = InputDelay;
		if (gamestate == Menu)
		{
			if (startArrow != END - 1)
				startArrow++;
			else
				startArrow = 0;
		}
		
		if (gamestate == Pause)
		{
			if (pauseArrow != END2 - 1)
				pauseArrow++;
			else
				pauseArrow = 0;
		}

		if (gamestate == End)
		{
			if (deadArrow != END3 - 1)
				deadArrow++;
			else
				deadArrow = 0;
		}

		if (gamestate == Win)
		{
			if (winArrow != END4 - 1)
				winArrow++;
			else
				winArrow = 0;
		}
	}
	if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
	{
		InputDelayTimer = InputDelay;
		if (gamestate == Menu)
		{
			if (startArrow != 0)
				startArrow--;
			else
				startArrow = END - 1;
		}

		if (gamestate == Pause)
		{
			if (pauseArrow != 0)
				pauseArrow--;
			else
				pauseArrow = END2 - 1;
		}

		if (gamestate ==  End)
		{
			if (deadArrow != 0)
				deadArrow--;
			else
				deadArrow = END3 - 1;
		}

		if (gamestate == Win)
		{
			if (winArrow != 0)
				winArrow--;
			else
				winArrow = END3 - 1;
		}
	}

	switch (gamestate)
	{
	case Menu:
	{
		switch (startArrow)
		{
		case Start:
		{
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				button->isClick = true;
				gamestate = Game;
			}
		}
		break;

		case Instructions:
		{
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				button->isClick = true;
				gamestate = Help;
			}
		}
		break;

		case Quit:
		{
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				button->isClick = true;
				QuitGame = true;
			}
		}
		break;
		}
	}

	case Help:
	{
		if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			gamestate = Menu;
		}
	}
	break;

	case Game:
	{
		if (Application::IsKeyPressed('P') && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			gamestate = Pause;
		}

		if (Character->Attribute->GetCurrentHP() >= 0)
		{
			playerDead = false;
		}

	}

	case Pause:
	{
		switch (pauseArrow)
		{
		case Resume:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				gamestate = Game;
			}
			break;

		case ReturnMenu:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				gamestate = Menu;
			}
			break;

		case Quit2:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				QuitGame = true;
			}
			break;
		}
	}

	case End:
	{
		switch (deadArrow)
		{
		case Restart:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				RestartGame = true;
				gamestate = Game;
			}
			break;

		case ReturnMenu3:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				gamestate = Menu;
				RestartGame = true;
			}
			break;
		}
	}

	case Win:
	{
		switch (winArrow)
		{
		case ReturnMenu4:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				gamestate = Menu;
				RestartGame = true;
			}
			break;

		case Quit4:
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				QuitGame = true;
			}
			break;
		}
	}

	break;

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
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		modelStack.Scale(180, 100, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, (m_worldHeight / 2) + 35.f, 0.f);
		modelStack.Scale(150, 20, 0);
		RenderMesh(meshList[GEO_GAMENAME], false);
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

		modelStack.PushMatrix();
		modelStack.Translate(button->HelpButton->pos.x, button->HelpButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_HELP], false);
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
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 26.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->HelpButton->pos.x, button->HelpButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_HELPHOVER], false);
			modelStack.PopMatrix();
			break;

		case (Quit) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 39.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->ExitButton->pos.x, button->ExitButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_EXITHOVER], false);
			modelStack.PopMatrix();
			break;
		}
	}

	if (gamestate == Game)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 4.5, (m_worldHeight / 1) - 5, 0.f);
		modelStack.Scale(65.f, 8.f, 0.f);
		RenderMesh(meshList[GEO_HPUI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_PLAYERHP], false, Vector3(Character->Attribute->GetCurrentHP() * 0.2f, 2.f, 0.f), 26.f - (157.f - (float)Character->Attribute->GetCurrentHP())*0.1f, m_worldHeight - 42.9, 0.f, Vector3(0.f, 0.f, 0.f));
		modelStack.PopMatrix();
	}

	if (gamestate == Pause)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		modelStack.Scale(180, 100, 0);
		RenderMesh(meshList[GEO_PAUSEUI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->ResumeButton->pos.x, button->ResumeButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_RESUME], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->MenuButton->pos.x, button->MenuButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_MENU], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->ExitButton->pos.x, button->ExitButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_EXIT], false);
		modelStack.PopMatrix();

		switch (pauseArrow)
		{
		case(Resume) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2), 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->ResumeButton->pos.x, button->ResumeButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_RESUMEHOVER], false);
			modelStack.PopMatrix();
			break;

		case(ReturnMenu) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 13, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->MenuButton->pos.x, button->MenuButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_MENUHOVER], false);
			modelStack.PopMatrix();
			break;

		case(Quit2) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 26, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->ExitButton->pos.x, button->ExitButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_EXITHOVER], false);
			modelStack.PopMatrix();
			break;
		}
	}

	if (gamestate == End)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_DEATHSCREEN], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->RestartButton->pos.x, button->RestartButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_RESTART], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->MenuButton->pos.x, button->MenuButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_MENU], false);
		modelStack.PopMatrix();

		switch (deadArrow)
		{
		case(Restart) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 26.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->RestartButton->pos.x, button->RestartButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_RESTARTHOVER], false);
			modelStack.PopMatrix();
			break;

		case(ReturnMenu3) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 39.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->MenuButton->pos.x, button->MenuButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_MENUHOVER], false);
			modelStack.PopMatrix();
			break;
		}
	}

	if (gamestate == Win)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_VICTORY], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->MenuButton->pos.x, button->MenuButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_MENU], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(button->ExitButton->pos.x, button->ExitButton->pos.y, 0.f);
		modelStack.Scale(25.f, 10.f, 0.f);
		RenderMesh(meshList[GEO_EXIT], false);
		modelStack.PopMatrix();

		switch (winArrow)
		{
		case(ReturnMenu4) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 26.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->MenuButton->pos.x, button->MenuButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_MENUHOVER], false);
			modelStack.PopMatrix();
			break;

		case(Quit4) :
			modelStack.PushMatrix();
			modelStack.Translate((m_worldWidth / 2) - 20.f, (m_worldHeight / 2) - 39.f, 0.f);
			modelStack.Scale(10.f, 10.f, 0.f);
			RenderMesh(meshList[GEO_STARTARROW], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(button->ExitButton->pos.x, button->ExitButton->pos.y, 0.f);
			modelStack.Scale(27.f, 12.f, 0.f);
			RenderMesh(meshList[GEO_EXITHOVER], false);
			modelStack.PopMatrix();
			break;
		}

	}

	if (gamestate == Help)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		modelStack.Scale(180, 100, 0);
		RenderMesh(meshList[GEO_INSTRUCTIONS], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, (m_worldHeight / 2) - 43, 0.f);
		modelStack.Scale(27.f, 12.f, 0.f);
		RenderMesh(meshList[GEO_OKAYHOVER], false);
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