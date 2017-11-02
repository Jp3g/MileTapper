#pragma once

#include "Container.hpp"
#include "ActionTarget.hpp"
#include "Button.hpp"

namespace MileTapper {

	class MenuBar : private Container, protected ActionTarget<int> {
	public:
		MenuBar(const MenuBar&) = delete;
		MenuBar& operator=(const MenuBar&) = delete;

		using ActionTarget<int>::FuncType;
		MenuBar(sf::RenderWindow& window);
		virtual ~MenuBar();

		void processEvents();
		bool processEvent(sf::Event& event);

		void bind(int key, const FuncType& callback);
		void unbind(int key);

		void draw();
		void addButton(Button* button);
		virtual sf::Vector2f getSize() const override;

	private:
		sf::RenderWindow& _window;
		sf::Vector2f _size;

		virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) override;
		virtual void processEvents(const sf::Vector2f& parent_pos);

	};
}
