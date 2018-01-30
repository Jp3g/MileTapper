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

		Editor(sf::RenderWindow& window);
		~Editor();

		void update(sf::Time deltaTime);
		void processEvents();
		bool processEvent(sf::Event& event);

		void draw(sf::RenderWindow& window);

		//Enitity Manager
		//High light Tile

		//Entity creation
		//Sound

		/*
		    sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos)const;
            sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos)const;

            sf::Vector2i mapCoordsToScreen(const sf::Vector2i& pos)const;
            sf::Vector2i mapScreenToCoords(const sf::Vector2i& pos)const;

            std::list<Entity*> getByCoords(const sf::Vector2i& coord);
		
		*/

		//Path...Etc
	private:
		friend class Game;

		void initGui();

		VMap* _map ;
		MapViewer _viewer;
		MenuBar _menuBar;

		//_byCoord

		//sf::ConvexShape* _mouse_light;
		//sfutils::Layer<sf::ConvexShape>* _mouseLayer;
		//sfutils::Layer<Entity*>* _entitiesLayer;

		//f::Listener _listener;								<-- ?
	};
}