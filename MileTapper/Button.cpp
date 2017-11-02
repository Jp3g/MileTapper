#include "Button.hpp"

namespace MileTapper {

	Button::FuncType Button::defaultFunc = [](const sf::Event&, Button&)->void {};

	Button::Button(Widget* parent) : Widget(parent), onClick(defaultFunc), _status(Status::None) {

	}

	Button::~Button() {

	}

	bool Button::processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) {
		bool res = false;

		if (event.type == sf::Event::MouseButtonPressed && (_status & Status::Hover))
			onMousePressed();

		if (event.type == sf::Event::MouseButtonReleased) {
			if((_status & Status::Hover))
				onMouseReleased();

			const sf::Vector2f pos = _position + parent_pos;
			const sf::Vector2f size = getSize();
			sf::FloatRect rect;
			rect.left = pos.x;
			rect.top = pos.y;
			rect.width = size.x;
			rect.height = size.y;

			if (rect.contains(event.mouseButton.x, event.mouseButton.y)) {
				onClick(event, *this);
				res = true;
			}

		}else if (event.type == sf::Event::MouseMoved) {
			const sf::Vector2f pos = _position + parent_pos;
			const sf::Vector2f size = getSize();
			sf::FloatRect rect;
			rect.left = pos.x;
			rect.top = pos.y;
			rect.width = size.x;
			rect.height = size.y;
			int old_status = _status;

			_status = Status::None;

			const sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);

			if (rect.contains(mouse_pos)) {
				const sf::Vector2f size = getSize();
				_status = Status::Hover;
			}

			if ((old_status & Status::Hover) && !(_status & Status::Hover))
				onMouseLeft();
			else if (!(old_status & Status::Hover) && (_status & Status::Hover))
				onMouseEntered();

		}

		return res;
	}

	void Button::onMousePressed() {

	}

	void Button::onMouseReleased() {

	}

	void Button::onMouseEntered() {

	}

	void Button::onMouseLeft() {

	}
}