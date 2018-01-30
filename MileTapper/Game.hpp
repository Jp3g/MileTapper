#pragma once

#include <SFML\Graphics.hpp>

#include "Editor.hpp"

namespace MileTapper {
	class Game {
	public:
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		Game(int X = 1600, int Y = 900);
		~Game();

		bool load();
		void run(int frame_per_seconds = 60);
	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();

		sf::RenderWindow _window;
		
		Editor* _editor;
	};
}