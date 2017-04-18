#include <Trappist-1\scenes\SceneGame.hpp>
#include <Trappist-1\World.hpp>
#include <Trappist-1\entities\Entity.hpp>
#include <Trappist-1\entities\Player.hpp>
#include <Trappist-1\Util.hpp>

#include <Trappist-1\graphics\Renderer2D.hpp>
#include <Trappist-1\graphics\light\LightRenderer2D.hpp>

#include <Trappist-1\Core.hpp>

#include <iostream>
#include <Trappist-1\Components.hpp>

#include <Trappist-1\animation\AnimationSheetManager.hpp>
#include <Trappist-1\abilities\AbilityManager.h>

SceneGame::SceneGame()
	: lightEdges(150.0f, 200.0f), lightFactor(60.0f), lightUp(false)
{
	type = Scene::Type::GAME;

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

	Entity *e4 = new Entity;
	e4->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 2));
	e4->setPosition(100.0f, 300.0f);
	e4->setOrigin(glm::vec2(e4->getSize().x * 0.5f, e4->getSize().y * 0.75f));
	e4->setTexture(&testTexture);
	//e4->addComponent(new Collider(e4, glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT)));
	e4->addComponent(new Collider(e4, World::TILE_PIXEL_WIDTH * 0.4f));
	e4->addComponent(new Movement(e4));
	static_cast<Movement*>(e4->getComponent(ComponentType::MOVEMENT))->setDesiredDirection(200);
	static_cast<Movement*>(e4->getComponent(ComponentType::MOVEMENT))->maxSpeed = 0.2f;
	World::addEntity(e4);

	AnimationSheetManager::load(AnimationSheetManager::AnimationSheetHandles::PLAYER, TextureManager::TextureHandles::ANIMATION_SHEET_PLAYER, "res/textures/entities/player-test.asi");
	AbilityManager *manager = new AbilityManager();
	manager->setAbility(0, AbilityType::DASH);
	player = new Player(manager);
	manager->setEntity(player);
	player->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT * 1));
	//player->setTexture(&testTexture);
	player->setTexture(AnimationSheetManager::get(AnimationSheetManager::AnimationSheetHandles::PLAYER)->getTexture());
	player->setOrigin(glm::vec2(player->getSize().x * 0.5f, player->getSize().y * 0.75f));
	player->addComponent(new Collider(player, World::TILE_PIXEL_WIDTH * 0.4f));
	player->addComponent(new Movement(player));
	player->addComponent(new Animator(player, AnimationSheetManager::AnimationSheetHandles::PLAYER));
	World::addEntity(player);

	AnimationSheetManager::load(AnimationSheetManager::AnimationSheetHandles::SHADOW_SLIME, TextureManager::TextureHandles::ANIMATION_SHEET_SHADOW_SLIME, "res/textures/entities/shadow-slime.asi");
	Entity *e1 = new Entity;
	e1->setSize(glm::vec2(World::TILE_PIXEL_WIDTH, World::TILE_PIXEL_HEIGHT));
	e1->setPosition(-100.0f, -300.0f);
	e1->setOrigin(glm::vec2(e1->getSize().x * 0.5f, e1->getSize().y * 0.5f));
	e1->setTexture(AnimationSheetManager::get(AnimationSheetManager::AnimationSheetHandles::SHADOW_SLIME)->getTexture());
	//e1->addComponent(new Collider(e1, World::TILE_PIXEL_WIDTH * 0.4f));
	//e1->addComponent(new Movement(e1));
	e1->addComponent(new Animator(e1, AnimationSheetManager::AnimationSheetHandles::SHADOW_SLIME));
	//static_cast<Movement*>(e4->getComponent(ComponentType::MOVEMENT))->setDesiredDirection(200);
	//static_cast<Movement*>(e4->getComponent(ComponentType::MOVEMENT))->maxSpeed = 3;
	World::addEntity(e1);

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
	if (lightUp)
	{
		lightEdges.x += Time::deltaTime * lightFactor;
		if (lightEdges.x > 152.0f)
			lightUp = false;
	}
	else
	{
		lightEdges.x -= Time::deltaTime * lightFactor;
		if (lightEdges.x < 148.0f)
			lightUp = true;
	}

	inputUpdate();

	if (!paused)
	{
		playerInput();
		World::update();
	}
}

void SceneGame::renderLights(LightRenderer2D &lightRenderer2d)
{
	lightRenderer2d.setDefaultLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	lightRenderer2d.pushMatrix(glm::inverse(World::camera.getTransform()));

	// player's light
	lightRenderer2d.submitLight2D(player->getPosition(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(50.0f, 200.0f));

	// ground light
	lightRenderer2d.submitLight2D(glm::vec2(0.0f, -50.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), lightEdges);
	lightRenderer2d.submitLight2D(glm::vec2(-50.0f, 50.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), lightEdges);
	lightRenderer2d.submitLight2D(glm::vec2(50.0f, 50.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), lightEdges);

	lightRenderer2d.popMatrix();
}

void SceneGame::render(Renderer2D &renderer2d)
{
	renderer2d.pushMatrix(glm::inverse(World::camera.getTransform()));

	// Render tiles

	//Timer t;
	//Timer::time_t time = 0.0f;
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

				tileVertices[0].position.x = x * World::TILE_PIXEL_WIDTH_F - World::HALF_WIDTH_F;
				tileVertices[0].position.y = y * World::TILE_PIXEL_HEIGHT_F - World::HALF_HEIGHT_F;

				tileVertices[1].position.x = x * World::TILE_PIXEL_WIDTH_F - World::HALF_WIDTH_F;
				tileVertices[1].position.y = y * World::TILE_PIXEL_HEIGHT_F + World::TILE_PIXEL_HEIGHT_F - World::HALF_HEIGHT_F;

				tileVertices[3].position.x = x * World::TILE_PIXEL_WIDTH_F + World::TILE_PIXEL_WIDTH_F - World::HALF_WIDTH_F;
				tileVertices[3].position.y = y * World::TILE_PIXEL_HEIGHT_F - World::HALF_HEIGHT_F;

				tileVertices[2].position.x = x * World::TILE_PIXEL_WIDTH_F + World::TILE_PIXEL_WIDTH_F - World::HALF_WIDTH_F;
				tileVertices[2].position.y = y * World::TILE_PIXEL_HEIGHT_F + World::TILE_PIXEL_HEIGHT_F - World::HALF_HEIGHT_F;

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

				//Timer t2;
				renderer2d.submit4(tileVertices, TextureManager::get(TextureManager::TextureHandles::TILE_ATLAS)->getTexture(), 0.99f);
				//time += t2.elapsedSeconds();
			}
		}
	}
	//std::cout << "Timer took: " << t.elapsedSeconds()/* - time*/ << std::endl;

	for (auto it = World::entities.begin(); it != World::entities.end(); ++it)
		(*it)->render(renderer2d);

	renderer2d.popMatrix();
}

void SceneGame::onSizeChanged(unsigned int width, unsigned int height)
{
	World::camera.setOrigin(static_cast<float>(width) * 0.5f, static_cast<float>(height) * 0.5f);
}

void SceneGame::playerInput()
{
	/*static constexpr float speed = 300.0f;
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
		/*bool w = Input::getKeyPressed(sf::Keyboard::W);
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
		}*/

		glm::vec2 dir;
		if (Input::getKeyPressed(sf::Keyboard::W))
			dir.y -= 1.0f;

		if (Input::getKeyPressed(sf::Keyboard::S))
			dir.y += 1.0f;

		if (Input::getKeyPressed(sf::Keyboard::A))
			dir.x -= 1.0f;
		
		if (Input::getKeyPressed(sf::Keyboard::D))
			dir.x += 1.0f;

		if (dir.x == 0.0f && dir.y == 0.0f)
		{
				movement->desireStop();
		}
		else
			movement->setDesiredDirection(dir);

	}

	for (size_t i = 0; i < player->abilityManager->getSize() && i < 9; i++)
	{
		if (Input::getKeyDown(sf::Keyboard::Key(27 + i)))
		{
			player->abilityManager->cast(i);
		}
	}

	World::camera.setPosition(glm::clamp(player->getPosition().x, World::getLeftBorder(static_cast<float>(Core::windowSize.x)), World::getRightBorder(static_cast<float>(Core::windowSize.x))),
		glm::clamp(player->getPosition().y, World::getBottomBorder(static_cast<float>(Core::windowSize.y)), World::getTopBorder(static_cast<float>(Core::windowSize.y))));

	//std::cout << "x: " << player->getPosition().x << " y: " << player->getPosition().y << "\n";
}

void SceneGame::inputUpdate()
{
	if (Input::getKeyPressed(sf::Keyboard::Escape))
		Core::queryScene(Scene::Type::MENU);
}
