#include <Trappist-1\scenes\SceneGame.hpp>
#include <Trappist-1\World.hpp>
#include <Trappist-1\entities\Entity.hpp>
#include <Trappist-1\entities\Player.hpp>
#include <Trappist-1\Util.hpp>

#include <Trappist-1\graphics\Renderer2D.hpp>

#include <Trappist-1\Core.hpp>

#include <iostream>
#include <Trappist-1\Components.hpp>

SceneGame::SceneGame()
{
	type = SceneType::GAME;

	testTexture.load("res/textures/entities/Player.png");
	testTexture.setSmooth(false);

	// Initialize tiles
	TextureManager::load(TextureManager::TextureHandles::TILE_ATLAS, "res/textures/tiles");
	TextureManager::get(TextureManager::TextureHandles::TILE_ATLAS)->setSmooth(false);

	World::loadTileSelection(*TextureManager::get(TextureManager::TextureHandles::TILE_ATLAS));

	for (int y = 0; y < World::TILE_HEIGHT; ++y)
	{
		for (int x = 0; x < World::TILE_WIDTH; ++x)
		{
			World::setTile(static_cast<Tile::Type>((y * World::TILE_HEIGHT + x) % static_cast<int>(Tile::Type::COUNT)), x, y);
		}
	}

	Entity *e1 = new Entity;
	e1->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 2));
	e1->setPosition(-static_cast<float>(World::TILE_WIDTH * World::TILE_PIXEL_WIDTH) * 0.5f, -static_cast<float>(World::TILE_HEIGHT * World::TILE_PIXEL_HEIGHT) * 0.5f);
	e1->setOrigin(e1->getSize() * 0.5f);
	e1->setTexture(&testTexture);
	World::addEntity(e1);

	Entity *e2 = new Entity;
	e2->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 2));
	e2->setPosition(static_cast<float>(World::TILE_WIDTH * World::TILE_PIXEL_WIDTH) * 0.5f, -static_cast<float>(World::TILE_HEIGHT * World::TILE_PIXEL_HEIGHT) * 0.5f);
	e2->setOrigin(e2->getSize() * 0.5f);
	e2->setTexture(&testTexture);
	World::addEntity(e2);

	Entity *e3 = new Entity;
	e3->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 2));
	e3->setPosition(-static_cast<float>(World::TILE_WIDTH * World::TILE_PIXEL_WIDTH) * 0.5f, static_cast<float>(World::TILE_HEIGHT * World::TILE_PIXEL_HEIGHT) * 0.5f);
	e3->setOrigin(e3->getSize() * 0.5f);
	e3->setTexture(&testTexture);
	World::addEntity(e3);

	Entity *e4 = new Entity;
	e4->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 2));
	e4->setPosition(100.0f, 300.0f);
	e4->setOrigin(glm::vec2(e4->getSize().x * 0.5f, e4->getSize().y * 0.75f));
	e4->setTexture(&testTexture);
	//e4->addComponent(new Collider(e4, glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT)));
	e4->addComponent(new Collider(e4, World::TILE_PIXEL_WIDTH * 0.4f));
	World::addEntity(e4);

	player = new Player;
	player->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 2));
	player->setTexture(&testTexture);
	player->setOrigin(glm::vec2(player->getSize().x * 0.5f, player->getSize().y * 0.75f));
	player->addComponent(new Collider(player, World::TILE_PIXEL_WIDTH * 0.4f));
	player->addComponent(new Movement(player));
	World::addEntity(player);

	World::camera.setOrigin(Core::windowSize.x * 0.5f, Core::windowSize.y * 0.5f);
}

SceneGame::~SceneGame()
{
	while (!World::entities.empty()) {
		delete World::entities.back();
		World::entities.pop_back();
	}
}

void SceneGame::update()
{
	inputUpdate();

	if (!paused)
	{
		playerMovement();
		World::update();
	}
}

void SceneGame::render(Renderer2D &renderer2d)
{
	renderer2d.pushMatrix(glm::inverse(World::camera.getTransform()));

	// Render tiles
	VertexPCT2D tileVertices[4];
	const Tile *currTile;
	for (int y = 0; y < World::TILE_HEIGHT; ++y)
	{
		for (int x = 0; x < World::TILE_WIDTH; ++x)
		{
			currTile = &World::getTileSelectionAt(World::getTile(x, y));

			if (currTile)
			{
				// positions

				tileVertices[0].position.x = x * World::TILE_PIXEL_WIDTH_F - World::WIDTH_F * 0.5f;
				tileVertices[0].position.y = y * World::TILE_PIXEL_HEIGHT_F - World::HEIGHT_F * 0.5f;

				tileVertices[1].position.x = x * World::TILE_PIXEL_WIDTH_F - World::WIDTH_F * 0.5f;
				tileVertices[1].position.y = y * World::TILE_PIXEL_HEIGHT_F + World::TILE_PIXEL_HEIGHT - World::HEIGHT_F * 0.5f;

				tileVertices[3].position.x = x * World::TILE_PIXEL_WIDTH_F + World::TILE_PIXEL_WIDTH - World::WIDTH_F * 0.5f;
				tileVertices[3].position.y = y * World::TILE_PIXEL_HEIGHT_F - World::HEIGHT_F * 0.5f;

				tileVertices[2].position.x = x * World::TILE_PIXEL_WIDTH_F + World::TILE_PIXEL_WIDTH - World::WIDTH_F * 0.5f;
				tileVertices[2].position.y = y * World::TILE_PIXEL_HEIGHT_F + World::TILE_PIXEL_HEIGHT - World::HEIGHT_F * 0.5f;

				// tex coords

				tileVertices[0].texCoord.x = currTile->textureRect.left;
				tileVertices[0].texCoord.y = currTile->textureRect.top;

				tileVertices[1].texCoord.x = currTile->textureRect.left;
				tileVertices[1].texCoord.y = currTile->textureRect.top + currTile->textureRect.height;

				tileVertices[3].texCoord.x = currTile->textureRect.left + currTile->textureRect.width;
				tileVertices[3].texCoord.y = currTile->textureRect.top;

				tileVertices[2].texCoord.x = currTile->textureRect.left + currTile->textureRect.width;
				tileVertices[2].texCoord.y = currTile->textureRect.top + currTile->textureRect.height;

				// color

				tileVertices[0].color = currTile->color;
				tileVertices[1].color = currTile->color;
				tileVertices[2].color = currTile->color;
				tileVertices[3].color = currTile->color;

				renderer2d.submit4(tileVertices, TextureManager::get(TextureManager::TextureHandles::TILE_ATLAS)->getTexture());
			}
		}
	}

	for (auto it = World::entities.begin(); it != World::entities.end(); ++it)
		(*it)->render(renderer2d);

	renderer2d.popMatrix();
}

void SceneGame::onSizeChanged(unsigned int width, unsigned int height)
{
	World::camera.setOrigin(width * 0.5f, height * 0.5f);
}

void SceneGame::playerMovement()
{
	static constexpr float speed = 300.0f;
	/*
	if (Input::getKeyPressed(sf::Keyboard::A))
	{
		player->translate(Time::deltaTime * -speed, 0);
	}
	if (Input::getKeyPressed(sf::Keyboard::D))
	{
		player->translate(Time::deltaTime * speed, 0);
	}
	if (Input::getKeyPressed(sf::Keyboard::W))
	{
		player->translate(0, Time::deltaTime * -speed);
	}
	if (Input::getKeyPressed(sf::Keyboard::S))
	{
		player->translate(0, Time::deltaTime * speed);
	}*/

	if (player->hasComponent(ComponentType::MOVEMENT))
	{
		Movement *movement = static_cast<Movement*>(player->getComponent(ComponentType::MOVEMENT));
		bool w = Input::getKeyPressed(sf::Keyboard::W);
		bool a = Input::getKeyPressed(sf::Keyboard::A);
		bool s = Input::getKeyPressed(sf::Keyboard::S);
		bool d = Input::getKeyPressed(sf::Keyboard::D);

		bool m = true;
		float angle;

		if (w ^ s)
		{
			if (a ^ d)
			{
				if (d)
				{
					angle = s ? 45.0f : 315.0f;
				}
				else
				{
					angle = s ? 135.0f : 225.0f;
				}
			}
			else
			{
				angle = s ? 90.0f : 270.0f;
			}
		}
		else
		{
			if (a ^ d)
			{
				angle = d ? 0.0f : 180.0f;
			}
			else
			{
				m = false;
			}
		}

		if (m)
		{
			movement->setDesiredDirection(angle);
		}
		else
		{
			movement->desireStop();
		}

	}
	World::camera.setPosition(glm::clamp(player->getPosition().x, World::getLeftBorder(static_cast<float>(Core::windowSize.x)), World::getRightBorder(static_cast<float>(Core::windowSize.x))),
		glm::clamp(player->getPosition().y, World::getBottomBorder(static_cast<float>(Core::windowSize.y)), World::getTopBorder(static_cast<float>(Core::windowSize.y))));

	std::cout << "x: " << player->getPosition().x << " y: " << player->getPosition().y << "\n";
}

void SceneGame::inputUpdate()
{

}
