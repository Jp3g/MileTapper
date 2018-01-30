#pragma once

#include <SFML\Graphics.hpp>
#include "ActionTarget.hpp"
#include "VMap.hpp"
#include "Cursor.hpp"


namespace MileTapper {

	class VMap;
	class MapViewer : public sf::Drawable, protected ActionTarget<int>{
	public:
		MapViewer(const MapViewer&) = delete;
		MapViewer& operator=(const MapViewer&) = delete;

		MapViewer(sf::RenderWindow& window, VMap& map);
		MapViewer(sf::RenderWindow& window, VMap& map, const ActionMap<int>& action_map);

		using ActionTarget::bind;
		using ActionTarget::unbind;
		using ActionTarget::processEvents;

		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f& offset);

		void setPosition(float posX, float posY);
		void setPosition(const sf::Vector2f& pos);

		sf::Vector2f getPosition()const;

		void zoom(float factor);
		float getZoom()const;
		void drag(const bool isDragging);
		bool isDragging()const;

		void setSize(float width, float height);
		void setSize(const sf::Vector2f& size);

		void update(sf::Time deltaTime);

		void setSpeed(float speed);

		void draw(sf::RenderStates states = sf::RenderStates::Default) const;

		sf::Vector2i mapScreenToCoords(int x, int y)const;
		sf::Vector2i mapScreenToCoords(const sf::Vector2i& pos)const;

		sf::Vector2i mapCoordsToScreen(int x, int y) const;
		sf::Vector2i mapCoordsToScreen(const sf::Vector2i& pos) const;

		sf::Vector2i mapPixelToCoords(float x, float y) const;
		sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const;

		sf::Vector2f mapCoordsToPixel(int x, int y) const;
		sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos) const;

		VMap& getVMap();
		Cursor& getCursor();

		float _mouseX;
		float _mouseY;

	protected:

	private:
		friend class Editor;

		VMap& _map;
		sf::View _view;
		float _zoom;
		bool _isDragging = false;

		int _moveX, _moveY;
		float _movementSpeed;
		sf::RenderWindow& _window;
		Cursor _cursor;

		virtual bool processEvent(const sf::Event& event);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};

}