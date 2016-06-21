#include "layer2d.h"
#include "graphics/shader/shader_simple.h"
#include "graphics/shader/shader_simple3d.h"
#include "graphics/shader/shaderatlas.h"
#include "system/memory.h"
#include "window/input.h"
#include "system/log.h"
#include "platform/platform.h"
#include "game/map.h"
#include <time.h>

#include <string>

namespace ho {
namespace graphics {

Layer2D::Layer2D(game::Game* game)
	: game(game)
{
	int ww = Window::GetCurrentWindow().GetWidth();
	int wh = Window::GetCurrentWindow().GetHeight();
	int ind = 0;
	winner = -1;

	Texture* tile = honew Texture(std::string("res/map_tileset.png"));
	Texture* background = honew Texture(std::string("res/background_1200x720.png"));
	Texture* aviato_cannon = honew Texture(std::string("res/Cannon/aviato_89x89.png"));
	Texture* aviato_cannon_base = honew Texture(std::string("res/Cannon/base_aviato.png"));
	Texture* cannon_ball = honew Texture(std::string("res/ball.png"));
	Texture* piedp_cannon = honew Texture(std::string("res/Cannon/piedpiper_89x89.png"));
	Texture* piedp_cannon_base = honew Texture(std::string("res/Cannon/base_piedpiper.png"));
	textures.push_back(cannon_ball);
	textures.push_back(aviato_cannon_base);
	textures.push_back(aviato_cannon);
	textures.push_back(background);
	textures.push_back(tile);
	textures.push_back(piedp_cannon);
	textures.push_back(piedp_cannon_base);

	// Background
	quads.push_back(honew Quad2D(ww, wh));
	entities.push_back(honew Entity(quads[ind], background));
	entities[ind]->GetTransform().SetPosition(glm::vec3(0, 0, 0));
	ind++;

	// Player 1_base
	quads.push_back(honew Quad2D(318, 318));
	entities.push_back(honew Entity(quads[ind], aviato_cannon_base));
	entities[ind]->GetTransform().SetPosition(glm::vec3(0, 0, 2.0f));
	entities[ind]->GetTransform().SetScale(glm::vec3(0.16f, 0.16f, 1.0f));
	Entity* player_ptr_base = entities[ind];
	ind++;

	// Player 2_base
	quads.push_back(honew Quad2D(318, 318));
	entities.push_back(honew Entity(quads[ind], piedp_cannon_base));
	entities[ind]->GetTransform().SetPosition(glm::vec3(0, 0, 2.0f));
	entities[ind]->GetTransform().SetScale(glm::vec3(0.16f, 0.16f, 1.0f));
	Entity* player2_ptr_base = entities[ind];
	ind++;

	// Cannon ball quad
	m_CannonBall = honew Quad2D(30, 30);
	quads.push_back(m_CannonBall);
	ind++;

	// P1 cannon
	quads.push_back(honew Quad2D(534, 534));
	m_Player1 = honew game::Player(0, quads[ind], aviato_cannon, 10.0f, 6, 31);
	m_Player1->GetTransform().SetPosition(glm::vec3(0, 0, 2.0f));
	m_Player1->GetTransform().SetScale(glm::vec3(0.16f, 0.16f, 1.0f));
	ind++;

	// P2 cannon
	quads.push_back(honew Quad2D(534, 534));
	m_Player2 = honew game::Player(1, quads[ind], piedp_cannon, 10.0f, 6, 31);
	m_Player2->GetTransform().SetPosition(glm::vec3(0, 0, 2.0f));
	m_Player2->GetTransform().SetScale(glm::vec3(0.16f, 0.16f, 1.0f));
	m_Player2->GetTransform().RotateAround(glm::vec3(0,0,1), -140.0f);
	m_Player2->SetAngle();
	ind++;


	game::Map* map = honew game::Map("res/map3.txt");
	map->LoadGameMap(m_Player1, player_ptr_base, m_Player2, player2_ptr_base, tile, entities, map_quads, ww, wh);
	
	m_Shader = honew ShaderAtlas(std::string("res/shaders/shader_atlas"));

	m_P1_Line = honew Line();
	m_P2_Line = honew Line();

	hodelete map;
}

Layer2D::~Layer2D()
{
	hodelete m_Player1;
	hodelete m_Player2;
	hodelete m_P1_Line;
	hodelete m_P2_Line;

	hodelete m_Shader;
	for (auto q : quads)
		hodelete q;
	for (auto q : map_quads)
		hodelete q;
	for(auto e : entities)
		hodelete e;
	for (auto p : projectiles)
		hodelete p;
	for (auto t : textures)
		hodelete t;
}

void Layer2D::Update()
{
	auto calcspeed = [](int key, float speed, game::Player* player) {
		glm::vec3 axis(0, 0, 1);
		switch (key)
		{
		case F_KEY:
		case E_KEY:
			player->GetTransform().RotateAround(axis, speed); break;
		case D_KEY:
		case R_KEY:
			player->GetTransform().RotateAround(axis, -speed); break;
		}
		player->SetAngle();
	};

	float speed = 1.0f;

	if (Input::Keys[SHIFT_KEY])
		speed -= 0.9f;

	if (Input::Keys[F_KEY])
		calcspeed(F_KEY, speed, m_Player2);
	if (Input::Keys[D_KEY])
		calcspeed(D_KEY, speed, m_Player2);
	if (Input::Keys[E_KEY])
		calcspeed(E_KEY, speed, m_Player1);
	if (Input::Keys[R_KEY])
		calcspeed(R_KEY, speed, m_Player1);

	if (Input::Keys[Q_KEY])
		m_Player1->IncForce(0.1f);
	if (Input::Keys[W_KEY])
		m_Player1->IncForce(-0.1f);
	if (Input::Keys[A_KEY])
		m_Player2->IncForce(0.1f);
	if (Input::Keys[S_KEY])
		m_Player2->IncForce(-0.1f);


	if (Input::Keys[SPACE_KEY])
	{
		if (game->GetTurn() == game::Turn::T_PLAYER1)
		{
			game::Projectile* p =
				honew game::Projectile(m_Player1, m_CannonBall, textures[0], timer);
			p->GetTransform().MoveTowards(glm::vec3(0, 0, 1), 3.0f);
			projectiles.push_back(p);
			game->SwitchTurn();
		}
	}

	if (Input::Keys[X_KEY])
	{
		if (game->GetTurn() == game::Turn::T_PLAYER2)
		{
			if (timer.GetTime() - game::Projectile::GetLastSpawnTime() < game::Projectile::cooldown)
				return;
			game::Projectile* p =
				honew game::Projectile(m_Player2, m_CannonBall, textures[0], timer);
			p->GetTransform().MoveTowards(glm::vec3(0, 0, 1), 3.0f);
			projectiles.push_back(p);
			game->SwitchTurn();
		}
	}
}

bool Layer2D::Collided(game::Projectile* projectile, std::vector<Entity*>& entities, bool shoulddelete)
{
	switch (projectile->GetPlayerID())
	{
	case 0: {
		if (projectile->CollidedWith(m_Player2))
		{
			log::print("player 1 ganhou!");
			winner = m_Player1->GetID();
			shoulddelete = true;
			RandomizePlayersAttribs();
		}
	} break;
	case 1: {
		if (projectile->CollidedWith(m_Player1))
		{
			winner = m_Player2->GetID();
			log::print("player 2 ganhou");
			shoulddelete = true;
			RandomizePlayersAttribs();
		}
	} break;
	}

	for (auto e : entities)
	{
		if (e->isTerrain)
		{
			glm::vec3 e_pos = e->GetTransform().GetPosition();
			glm::vec3 p_pos = projectile->GetTransform().GetPosition();
			if (e->isGrass)
			{
				e_pos.y -= 30.0f;
			}
			if (glm::length(e_pos - p_pos) <= 20.0f)
			{
				shoulddelete = true;
				break;
			}
		}
	}
	return shoulddelete;
}

void Layer2D::Render()
{
	m_Shader->UseShader();

	// Render entities in general (map)
	for (auto e : entities)
	{
		m_Shader->Update(*e);
		e->BindTextures();
		e->Render();
		e->UnbindTextures();
	}
	
	// Render Projectiles and calc collision with map or other player
	for (uint i = 0; i < projectiles.size(); i++)
	{
		m_Shader->Update(*projectiles[i]);
		projectiles[i]->BindTextures();
		bool shoulddelete = projectiles[i]->Update(timer);
		projectiles[i]->Render();
		projectiles[i]->UnbindTextures();
		shoulddelete = Collided(projectiles[i], entities, shoulddelete);		// Collision O(n^2)
		if (shoulddelete)
		{
			hodelete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}

	m_Shader->Update(*m_Player1);

	// Render Player 1 and line for it
	m_Player1->BindTextures();
	m_Player1->Render();
	m_Player1->UnbindTextures();
	m_P1_Line->UpdateLine(m_Player1->GetForce());
	m_P1_Line->Render();

	// Render Player 2 and line for it
	m_Shader->Update(*m_Player2);
	m_Player2->BindTextures();
	m_Player2->Render();
	m_Player2->UnbindTextures();
	m_P2_Line->UpdateLine(m_Player2->GetForce());
	m_P2_Line->Render();

	m_Shader->StopShader();
}

void Layer2D::RandomizePlayersAttribs()
{
	srand(time(NULL));
	float p1rand = (rand() % 400) / 10.0;
	float p2rand = (rand() % 400) / 10.0;
	float p1forcrand = (rand() % 100) / 10.0;
	float p2forcrand = (rand() % 100) / 10.0;

	m_Player1->GetTransform().RotateAround(glm::vec3(0, 0, 1), p1rand);
	m_Player2->GetTransform().RotateAround(glm::vec3(0, 0, 1), p2rand);

	m_Player1->SetForce(p1forcrand);
	m_Player2->SetForce(p2forcrand);
}

}}