#pragma once 
#include <SFML\Graphics.hpp>

namespace MileTapper {
	class Widget : public sf::Drawable {
	public:
		Widget(Widget* parent = nullptr);
		virtual ~Widget();

		void setPosition(const sf::Vector2f& pos);
	    void setPosition(float x, float y);
		const sf::Vector2f getPosition() const;
		virtual sf::Vector2f getSize() const = 0;


	protected:
		friend class Container;
		friend class MenuBar;
		friend class VLayout;
		friend class HLayout;

		virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos);
		virtual void processEvents(const sf::Vector2f& parent_pos);
		virtual void updateShape();
		virtual void invalidate() const;

		Widget* _parent;
		sf::Vector2f _position;
	};
}