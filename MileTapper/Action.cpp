#include "Action.hpp"
#include <iostream>	

namespace MileTapper {

	Action::Action(const Action& other) : _type(other._type) {
		std::memcpy(&_event, &other._event, sizeof(sf::Event));
	}

	Action& Action::operator=(const Action& other) {
		std::memcpy(&_event, &other._event, sizeof(sf::Event));
		_type = other._type;

		return *this;
	}

	Action::Action(const sf::Event::EventType& event) : _type(Type::Pressed)
	{
		_event.type = event;
	}
	
	Action::Action(const sf::Keyboard::Key& key, int type) : _type(type) {
		_event.type = sf::Event::KeyPressed;
		_event.key.code = key;
	}

	Action::Action(const sf::Mouse::Button& button, int type) : _type(type) {
		_event.type = sf::Event::MouseButtonPressed;
		_event.mouseButton.button = button;
	}

	Action::Action(const sf::Mouse::Wheel& wheel, int type) : _type(type) {
		_event.type = sf::Event::MouseWheelScrolled;
		_event.mouseWheelScroll.wheel = wheel;
	}

	bool Action::test() const {
		bool res = false;

		if (_event.type == sf::Event::EventType::KeyPressed) {
			if(_type & Type::Pressed)
				res = sf::Keyboard::isKeyPressed(_event.key.code);
		} else if (_event.type == sf::Event::EventType::MouseButtonPressed) {
			if (_type & Type::Pressed)
				res = sf::Mouse::isButtonPressed(_event.mouseButton.button);
		} else if (_event.type == sf::Event::EventType::MouseWheelScrolled) {
			if (_type & Type::Scrolled)
				if (_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					res = true;
		}

		return res;
	}

	bool Action::operator==(const Action& other) const {
		return _type == other._type && other == _event;
	}

	bool Action::operator==(const sf::Event& event) const {
		bool res = false;

		switch (event.type)
		{
		case sf::Event::Resized: {
			res = event.type == _event.type;
		}break;
		case sf::Event::EventType::KeyPressed: {
			if (_type & Type::Pressed && _event.type == sf::Event::EventType::KeyPressed)
				res = event.key.code == _event.key.code;
		}break;
		case sf::Event::EventType::KeyReleased: {
			if (_type & Type::Released && _event.type == sf::Event::EventType::KeyPressed)
				res = event.key.code == _event.key.code;
		}break;
		case sf::Event::EventType::MouseButtonPressed: {
			if (_type & Type::Pressed && _event.type == sf::Event::EventType::MouseButtonPressed)
				res = event.mouseButton.button == _event.mouseButton.button;
		}break;
		case sf::Event::EventType::MouseButtonReleased: {
			if (_type & Type::Released && _event.type == sf::Event::EventType::MouseButtonPressed)
				res = event.mouseButton.button == _event.mouseButton.button;
		}break;
		case sf::Event::EventType::MouseWheelScrolled: {
			if (_type & Type::Scrolled && _event.type == sf::Event::EventType::MouseWheelScrolled)
				res = event.mouseWheelScroll.wheel == _event.mouseWheelScroll.wheel;
		}break;
		default:
			break;
		}

		return res;
	}
}