#pragma once

#include <SFML\Graphics.hpp>
#include "ActionTarget.hpp"

namespace MileTapper {

	//crée un template comme Tile. Permet l'usage d'un curseur
	//sur n'importe quel forme géometric IsometricCursor<GEOMETRY>
	class Cursor : public sf::Drawable {
	public:
		Cursor(const Cursor&) = delete;
		Cursor& operator=(const Cursor&) = delete;

		Cursor(sf::RenderWindow& window, sf::ConvexShape cursor);
		void setPosition(const sf::Vector2f pos);
		void setCoord(const sf::Vector2i coord);
		sf::Vector2i getCoord() const;

		void update(sf::Time deltaTime);
	private:
		friend class MapViewer;

		sf::RenderWindow& _window;
		sf::ConvexShape _cursor;
		sf::Text _text;

		sf::Vector2i _coord;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}