#include "Label.hpp"
#include "Configuration.hpp"

namespace MileTapper {
	Label::Label(const std::string& text, Widget* parent) : Widget(parent) {
		_text.setFont(Configuration::fonts.get(Configuration::Fonts::GUI));
		setText(text);
		setTextColor(sf::Color(0, 0, 0));
		setCharacterSize(12); //12
	}

	Label::~Label() {

	}

	void Label::setText(const std::string& text) {
		_text.setString(text);
		updateShape();
	}

	void Label::setCharacterSize(unsigned int size) {
		_text.setCharacterSize(size);
		Widget::updateShape();
	}

	unsigned int Label::getCharacterSize() const {
		return _text.getCharacterSize();
	}

	void Label::setTextColor(const sf::Color& color) {
		_text.setColor(color);
	}

	sf::Vector2f Label::getSize() const {
		sf::FloatRect rect = _text.getGlobalBounds();
		return sf::Vector2f(rect.width, rect.height);
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform.translate(_position);
		target.draw(_text, states);
	}
}