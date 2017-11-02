#pragma once

#include "Container.hpp"
#include "ActionTarget.hpp"

namespace MileTapper {

	class Frame : public Container, protected ActionTarget<int> {
	public:
		Frame(const Frame&) = delete;
		Frame& operator=(const Frame&) = delete;

		using ActionTarget<int>::FuncType;
		Frame(sf::RenderWindow& window, sf::Vector2f size = sf::Vector2f(0,0));
		virtual ~Frame();

		void processEvents();
		bool processEvent(sf::Event& event);

		void bind(int key, const FuncType& callback);
		void unbind(int key);

		void draw();
		virtual sf::Vector2f getSize() const override;



	private:
		sf::RenderWindow& _window;
		//sf::View _view;
		sf::Vector2f _size;

		virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) override;
		virtual void processEvents(const sf::Vector2f& parent_pos);

		//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
