#include "Cursor.hpp"
#include "Configuration.hpp"

#include <string> 

namespace MileTapper {

	Cursor::Cursor(sf::RenderWindow& window, sf::ConvexShape shape) : _window(window), _cursor(shape) {
		_cursor.setOutlineColor(sf::Color::Cyan);
		_cursor.setFillColor(sf::Color(255, 0, 0, 50.f));
	}

	void Cursor::setPosition(const sf::Vector2f pos) {
		_cursor.setPosition(pos);
	}

	void Cursor::setCoord(const sf::Vector2i coord) {
		_coord = coord;
	}

	sf::Vector2i Cursor::getCoord() const {
		return _coord;
	}

	void Cursor::update(sf::Time deltaTime) {
		_text.setPosition(sf::Vector2f(_cursor.getPosition().x + 50, _cursor.getPosition().y));
		
		_text.setString(/*"Xp:" + std::to_string(_cursor.getPosition().x) +
			"\n" + "Yp:" + std::to_string(_cursor.getPosition().y) +
			"\n"*/ + "Xc:" + std::to_string(_coord.x) +
			"\n" + "Yc:" + std::to_string(_coord.y));
		_text.setFont(Configuration::fonts.get(Configuration::Fonts::GUI));
		_text.setFillColor(sf::Color::Green);
		_text.setCharacterSize(10);

	}

	void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(_cursor, states);
		target.draw(_text, states);
	}
}