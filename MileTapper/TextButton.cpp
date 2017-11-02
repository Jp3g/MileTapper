#include "TextButton.hpp"
#include <iostream>

namespace MileTapper {
	TextButton::TextButton(const std::string& text, Widget* parent) : Button(parent),
		_label(text, this) {
		setFillColor(sf::Color(200, 200, 200));
		setOutlineThickness(0);
		setOutlineColor(sf::Color(200, 200, 200));
	}

	TextButton::~TextButton() {

	}

	void TextButton::setText(const std::string& text) {
		_label.setText(text);
	}

	void TextButton::setCharaterSize(unsigned int size) {
		_label.setCharacterSize(size);
	}

	void TextButton::setTextColor(const sf::Color& color) {
		_label.setTextColor(color);
	}

	void TextButton::setFillColor(const sf::Color& color) {
		_fillColor = color;
		_shape.setFillColor(_fillColor);
	}

	void TextButton::setOutlineColor(const sf::Color& color) {
		_outlineColor = color;
		_shape.setOutlineColor(_outlineColor);
	}

	void TextButton::setOutlineThickness(float thickness) {
		_shape.setOutlineThickness(thickness);
	}

	sf::Vector2f TextButton::getSize() const {
		sf::FloatRect rect = _shape.getGlobalBounds();
		return sf::Vector2f(rect.width, rect.height);
	}

	void TextButton::updateShape() {
		sf::Vector2f label_size = _label.getSize();
		unsigned int char_size = _label.getCharacterSize();

		if (_parent) {
			//_shape.setSize(sf::Vector2f(_parent->getSize().x, label_size.y + char_size)); //Vlayout
			//_shape.setSize(sf::Vector2f( label_size.x + char_size, _parent->getSize().y)); //Hlayout
			//_shape.setSize(sf::Vector2f(_parent->getSize().x, _parent->getSize().y)); //Hlayout
			_shape.setSize(sf::Vector2f(label_size.x + char_size, label_size.y + char_size));
		}else{
			_shape.setSize(sf::Vector2f(label_size.x + char_size, label_size.y + char_size));
		}

		//_shape.setSize(sf::Vector2f(label_size.x + char_size, label_size.y + char_size));

		_label.setPosition((getSize().x - label_size.x) / 2.f , (getSize().y - label_size.y) / 2.f);

		Widget::updateShape();
	}

	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform.translate(_position);
		target.draw(_shape, states);
		target.draw(_label, states);
	}

	void TextButton::onMouseEntered() {
		const float light = 2.0f;

		//_shape.setOutlineColor(sf::Color(_outlineColor.r * light,
		//	_outlineColor.g * light,
		//	_outlineColor.b * light));

		_shape.setFillColor(sf::Color(_fillColor.r * light,
			_fillColor.g * light,
			_fillColor.b * light));
	}

	void TextButton::onMouseLeft() {
		_shape.setOutlineColor(_outlineColor);
		_shape.setFillColor(_fillColor);
	}

	void TextButton::onMousePressed() {
		const float light = 2.0f;

		//_shape.setOutlineColor(sf::Color(_fillColor.r * light,
		//	_fillColor.g * light,
		//	_fillColor.b * light));

		const float inner_light = 0.5f;

		_shape.setFillColor(sf::Color(_fillColor.r * inner_light,
			_fillColor.g * inner_light,
			_fillColor.b * inner_light));
	}

	void TextButton::onMouseReleased() {
		const float light = 2.0f;

		_shape.setOutlineColor(_outlineColor);

		_shape.setFillColor(sf::Color(_fillColor.r * light,
			_fillColor.g * light,
			_fillColor.b * light));
	}


}