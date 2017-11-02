#pragma once
#include "VLayout.hpp"

namespace MileTapper {
	VLayout::VLayout(Widget* parent) : Layout(parent) {
		_shape.setOutlineColor(sf::Color::Red);
		_shape.setFillColor(sf::Color::Transparent);
		_shape.setOutlineThickness(1);
	}

	VLayout::~VLayout() {
		for (Widget* widget : _widgets)
			if (widget->_parent == this)
				delete widget;
	}

	void VLayout::add(Widget* widget) {
		if(!widget->_parent)
			widget->_parent = this;

		_widgets.emplace_back(widget);

		invalidate();
	}

	void VLayout::invalidate() const{
		for (Widget* widget : _widgets) {
			widget->updateShape();
		}
	}


	Widget* VLayout::at(unsigned int index) const {
		return _widgets.at(index);
	}

	sf::Vector2f VLayout::getSize() const {
		float max_x = 0;
		float y = 0;

		for (Widget* widget : _widgets) {
			sf::Vector2f size = widget->getSize();
			if (size.x > max_x)
				max_x = size.x;

			y += _space + size.y;
		}

		return sf::Vector2f(max_x, y + _space);
	}

	bool VLayout::processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) {
		for (Widget* widget : _widgets) {
			if (widget->processEvent(event, parent_pos))
				return true;
		}

		return false;
	}

	void VLayout::processEvents(const sf::Vector2f& parent_pos) {
		for (Widget* widget : _widgets)
			widget->processEvents(parent_pos);
	}

	void VLayout::updateShape() {
		float max_x = (_parent ? _parent->getSize().x : 0);

		for (Widget* widget : _widgets) {
			sf::Vector2f size = widget->getSize();
			float widget_x = size.x;

			if (widget_x > max_x)
				max_x = widget_x;
		}

		float pos_y = _space;

		if (_parent)
			pos_y = _parent->getPosition().y; /*(_parent->getSize().y - getSize().y) / 2.f;*/

		for (Widget* widget : _widgets) {
			sf::Vector2f size = widget->getSize();
			//widget->setPosition(pos_x, _parent ? _parent->getPosition().y : (max_y - size.y) / 2.0);
			widget->setPosition(_parent ? _parent->getPosition().x : (max_x - size.x) / 2.0f, pos_y);

			pos_y += size.y + _space;

		}
		_shape.setPosition(_parent ? _parent->getPosition().x : (max_x - getSize().x) / 2.f, pos_y - getSize().y);
		//_shape.setPosition((max_x - getSize().x) / 2.f, pos_y - getSize().y);
		_shape.setSize(getSize());

		Widget::updateShape();
	}

	void VLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(_shape, states);

		for (Widget* widget : _widgets)
			target.draw(*widget, states);
	}
}