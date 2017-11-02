#pragma once

#include <SFML\Graphics.hpp>

namespace MileTapper {
	
	class Action {
	public:
		enum Type {
			RealTime = 1, // 0001 = 1
			Pressed = 1 << 1, // 0010 = 2
			Released = 1 << 2, // 0100 = 4
			Scrolled = 1 << 3, // 1000 = 16
		};

		Action(const Action& other);
		Action& operator=(const Action& other);

		Action(const sf::Event::EventType& event);
		Action(const sf::Keyboard::Key& key, int type = Type::RealTime | Type::Pressed);
		Action(const sf::Mouse::Button& button, int type = Type::RealTime | Type::Pressed);
		Action(const sf::Mouse::Wheel& wheel, int type = Type::RealTime | Type::Scrolled);

		bool test() const;

		bool operator==(const sf::Event& event) const;
		bool operator==(const Action& other) const;

	private:
		template<typename> friend class ActionTarget;

		sf::Event _event;
		int _type;
	};
}