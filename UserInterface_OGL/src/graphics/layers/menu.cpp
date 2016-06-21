#include "menu.h"
#include "game/game.h"
#include "graphics/shader/shader_simple.h"
#include "window/input.h"

namespace ho {
namespace graphics {

Menu::Menu()
{
	int ww = Window::GetCurrentWindow().GetWidth();
	int wh = Window::GetCurrentWindow().GetHeight();
	int ind = 0;
	start_game = false;
	quit_game = false;

	background = honew Texture(std::string("res/GUI/main_notext.png"));
	textures.push_back(background);
	Texture* new_game_normal = honew Texture(std::string("res/GUI/novo_jogo.png"));
	textures.push_back(new_game_normal);
	Texture* new_game_hover = honew Texture(std::string("res/GUI/novo_jogo_hover.png"));
	textures.push_back(new_game_hover);
	Texture* quit_normal = honew Texture(std::string("res/GUI/sair.png"));
	textures.push_back(quit_normal);
	Texture* quit_hover = honew Texture(std::string("res/GUI/sair_hover.png"));
	textures.push_back(quit_hover);

	p1w = honew Texture(std::string("res/GUI/p1wins.png"));
	textures.push_back(p1w);
	p2w = honew Texture(std::string("res/GUI/p2wins.png"));
	textures.push_back(p2w);

	// Background
	quads.push_back(honew Quad2D(ww, wh));
	entities.push_back(honew Entity(quads[ind], background));
	entities[ind]->GetTransform().SetPosition(glm::vec3(0, 0, 0));
	m_BackgroundEntity = entities[ind];
	ind++;

	// New Game normal & hover
	quads.push_back(honew Quad2D(128, 36));
	entities.push_back(honew Entity(quads[ind], new_game_normal));
	entities[ind]->GetTransform().SetPosition(glm::vec3(10.0f, -90.0f, 1.0f));
	m_NewGame = entities[ind];
	ind++;
	quads.push_back(honew Quad2D(128, 36));
	entities.push_back(honew Entity(quads[ind], new_game_hover));
	entities[ind]->GetTransform().SetPosition(glm::vec3(10.0f, -90.0f, 1.0f));
	entities[ind]->shouldRender = false;
	m_NewGameHover = entities[ind];
	ind++;

	// Quit normal & hover
	quads.push_back(honew Quad2D(54, 33));
	entities.push_back(honew Entity(quads[ind], quit_normal));
	entities[ind]->GetTransform().SetPosition(glm::vec3(10.0f, -160.0f, 1.0f));
	m_Quit = entities[ind];
	ind++;
	quads.push_back(honew Quad2D(54, 33));
	entities.push_back(honew Entity(quads[ind], quit_hover));
	entities[ind]->GetTransform().SetPosition(glm::vec3(10.0f, -160.0f, 1.0f));
	entities[ind]->shouldRender = false;
	m_QuitHover = entities[ind];
	ind++;

	m_Shader = honew SimpleShader(std::string("res/shaders/simple_shader"));

}

Menu::~Menu()
{
	hodelete m_Shader;
	for (auto e : entities)
		hodelete e;
	for (auto q : quads)
		hodelete q;
	for (auto t : textures)
		hodelete t;
}

void Menu::Render()
{
	((SimpleShader*)m_Shader)->UseShader();
	for (auto e : entities)
	{
		((SimpleShader*)m_Shader)->Update(*e);
		e->BindTextures();
		e->Render();
		e->UnbindTextures();
	}
}

void Menu::Update()
{
	auto ishovering = [](glm::vec2 mouse_pos, glm::vec3 pos, float y_size, float x_size) -> bool
	{
		pos.x += Window::GetCurrentWindow().GetWidth() / 2.0f;
		pos.y -= Window::GetCurrentWindow().GetHeight() / 2.0f;
		pos.y = -pos.y;

		glm::vec2 distance = glm::abs(mouse_pos - glm::vec2(pos));
		if (distance.x <= x_size / 2.0f && distance.y <= y_size / 2.0f)
			return true;
		return false;
	};

	if (ishovering(Input::mouse_pos, m_NewGameHover->GetTransform().GetPosition(), 36, 128))
	{
		m_NewGameHover->shouldRender = true;
		m_NewGame->shouldRender = false;
		if (Input::left_click)
		{
			log::print("New game started!");
			start_game = true;
			Input::left_click = false;
		}
	}
	else 
	{
		m_NewGameHover->shouldRender = false;
		m_NewGame->shouldRender = true;
	}

	if (ishovering(Input::mouse_pos, m_QuitHover->GetTransform().GetPosition(), 54, 33))
	{
		m_QuitHover->shouldRender = true;
		m_Quit->shouldRender = false;
		if (Input::left_click)
		{
			log::print("Quitting...");
			quit_game = true;
			Input::left_click = false;
		}
	}
	else
	{
		m_QuitHover->shouldRender = false;
		m_Quit->shouldRender = true;
	}

	Input::left_click = false;
}

void Menu::SwitchMenuTexture(int winner)
{
	switch (winner)
	{
	case 0: m_BackgroundEntity->SetTexture(p1w); break;
	case 1: m_BackgroundEntity->SetTexture(p2w); break;
	}
}

}}