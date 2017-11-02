#pragma once
#include "HLayout.hpp"

namespace MileTapper {
	HLayout::HLayout(Widget* parent) : Layout(parent) {
		_shape.setOutlineColor(sf::Color::Red);
		_shape.setFillColor(sf::Color::Transparent);
		_shape.setOutlineThickness(1);
	}

	HLayout::~HLayout() {
		for (Widget* widget : _widgets)
			if (widget->_parent == this)
				delete widget;
	}

	void HLayout::add(Widget* widget) {
		if (!widget->_parent)
			widget->_parent = this;

		_widgets.emplace_back(widget);

		invalidate();
	}

	void HLayout::invalidate() const {
		for (Widget* widget : _widgets) {
			widget->updateShape();
		}
	}


	Widget* HLayout::at(unsigned int index) const {
		return _widgets.at(index);
	}

	sf::Vector2f HLayout::getSize()const
	{
		float max_y = 0;
		float x = 0;
		for (Widget* widget : _widgets)
		{

				sf::Vector2f size = widget->getSize();
				if (size.y > max_y)
					max_y = size.y;
				x += _space + size.x;
			
		}
		return sf::Vector2f(x + _space, max_y + _space * 2);
	}

	bool HLayout::processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) {
		for (Widget* widget : _widgets) {
			if (widget->processEvent(event, parent_pos))
				return true;
		}

		return false;
	}

	void HLayout::processEvents(const sf::Vector2f& parent_pos) {
		for (Widget* widget : _widgets)
			widget->processEvents(parent_pos);
	}

	void HLayout::updateShape()
	{
		float max_y = (_parent ? _parent->getSize().y : 0);

		for (Widget* widget : _widgets)
		{
				sf::Vector2f size = widget->getSize();
				float widget_y = size.y;

				if (widget_y > max_y)
					max_y = widget_y;
		}

		float pos_x = _space;

		if (_parent)
			pos_x = _parent->getPosition().x; /*(_parent->getSize().x - getSize().x) / 2.f;*/

		for (Widget* widget : _widgets)
		{
				sf::Vector2f size = widget->getSize();
				widget->setPosition(pos_x, _parent ? _parent->getPosition().y : (max_y - size.y) / 2.0);
				pos_x += size.x + _space;
			
		}

		_shape.setPosition(pos_x - getSize().x, _parent ? _parent->getPosition().y : (max_y - getSize().y) / 2.f);
		_shape.setSize(getSize());

		Widget::updateShape();
	}

	//_shape.setPosition((max_x - getSize().x) / 2.f, pos_y - getSize().y);
	//_shape.setSize(getSize());

	void HLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform.translate(_position);

		target.draw(_shape, states);

		for (Widget* widget : _widgets)
			target.draw(*widget, states);
	}
}