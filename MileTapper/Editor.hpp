#pragma once

#include <SFML\Graphics.hpp>


#include "VMap.hpp"
#include "MapViewer.hpp"
#include "Frame.hpp"
#include "MenuBar.hpp"

namespace MileTapper {
	class Editor {
	public:
		Editor(const Editor&) = delete;
		Editor& operator=(Editor&) = delete;

		Editor(int X = 1600, int Y = 900);
		~Editor();

		void run(int frame_per_seconds = 60);

	private:
		void processEvents();
		void update(sf::Time deltaTime);
		void render();
		void initGui();

		sf::RenderWindow _window;

		Frame _menu;
		MenuBar _menuBar;


		VMap* _map = MileTapper::VMap::createMapFromFile("media/map.json");
		MapViewer _viewer;
	};
}