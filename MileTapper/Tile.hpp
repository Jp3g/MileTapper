#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "Cursor.hpp"

namespace MileTapper {
	
	template<typename GEOMETRY>
	class Tile : public sf::Drawable {
	public:
		Tile(const Tile&) = delete;
		Tile& operator=(const Tile&) = delete;

		Tile(Tile&&) = default;
		Tile& operator=(Tile&&) = default;

		static sf::Vector2i mapPixelToCoords(float x, float y, float scale);
		static sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos, float scale);

		static sf::Vector2f mapCoordsToPixel(int x, int y, float scale);
		static sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos, float scale);

		Tile(int pos_x, int pos_y, float scaler);

		template<typename ... Args>
		inline void setFillColor(Args&& ... args);

		template<typename ... Args>
		void setPosition(Args&& ... args);

		sf::Vector2f getPosition() const;

		template<typename ... Args>
		void setCoords(Args&& ... args);

		void setTexture(const sf::Texture* texture, bool resetRect = false);
		void setTextureRect(const sf::IntRect& rect);

		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBounds() const;

		void setOutlineColor(const sf::Color& color);
		virtual bool processEvent(const sf::Event& event);

	private:
		sf::ConvexShape _box;
		sf::ConvexShape _shape;

		sf::RectangleShape _trigger;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		enum Status { None = 0, Hover = 1 };
		int _status;

		virtual void onMouseEntered();
		virtual void onMouseLeft();

		sf::Color _outlineColor;

		bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox);
		bool CCW(const std::vector<sf::Vector2f>& points);
		bool doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines);
	};

	template<typename GEOMETRY>
	void Tile<GEOMETRY>::setOutlineColor(const sf::Color& color) {
		_outlineColor = color;
		_shape.setOutlineColor(_outlineColor);
	}

	template<typename GEOMETRY>
	void Tile<GEOMETRY>::onMouseEntered() {
				const float light = 2.0f;
			_shape.setOutlineColor(sf::Color(255,0,0));

			//_shape.setFillColor(sf::Color(_fillColor.r * light,
			//_fillColor.g * light,
			//_fillColor.b * light));
	}

	template<typename GEOMETRY>
	void Tile<GEOMETRY>::onMouseLeft() {
		_shape.setOutlineColor(_outlineColor);
	}

	template<typename GEOMETRY>
	bool Tile<GEOMETRY>::processEvent(const sf::Event& event) {
		bool res = false;


		////std::cout << size.x << " | " << size.y << std::endl;
		//if (event.type == sf::Event::MouseMoved) {
		//	const sf::Vector2f pos = _shape.getPosition();

		//	//std::cout << _shape.getPosition().x << " | "<< _shape.getPosition().y << std::endl;

		//	sf::FloatRect rectGB = _shape.getGlobalBounds();
		//	const sf::Vector2f size = sf::Vector2f(rectGB.width, rectGB.height);
	
		//	sf::FloatRect rect;
		//	rect.left = pos.x;
		//	rect.top = pos.y;
		//	rect.width = size.x;
		//	rect.height = size.y;
		//	int old_status = _status;

		//	_status = Status::None;

		//	const sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
		//	
		//	//std::cout << size.x << " | " << size.y << std::endl;
		//	
		//	std::vector<sf::Vector2f> points;
		//	for (size_t index = 0; index < _shape.getPointCount(); ++index) {
		//		points.push_back(sf::Vector2f(_shape.getPoint(index).x * rectGB.width,
		//			_shape.getPoint(index).y * rectGB.height));
		//	}


		//	const sf::Vector2f pos_box = _box.getPosition();
		//	const sf::Vector2i coord_box = mapPixelToCoords(pos_box.x, pos_box.y, 32);

		//	sf::FloatRect rectGB_box = _box.getGlobalBounds();
		//	const sf::Vector2f size_box = sf::Vector2f(rectGB_box.width, rectGB_box.height);

		//	sf::FloatRect rect_box;
		//	rect_box.left = coord_box.x;
		//	rect_box.top = coord_box.y;
		//	rect_box.width = size_box.x;
		//	rect_box.height = size_box.y;
		//	
		//	_trigger.setSize(sf::Vector2f(rect_box.width, rect_box.height));
		//	_trigger.setPosition(sf::Vector2f(mouse_pos.x, mouse_pos.y));
		//	_trigger.setOrigin(rect_box.width / 2, rect_box.height / 2);
		//	_trigger.setOutlineColor(sf::Color::Cyan);
		//	_trigger.setFillColor(sf::Color(0, 0, 0, 0.f));

		//	sf::Vector2i mouse_pos_converted = GEOMETRY::mapPixelToCoords(mouse_pos.x, mouse_pos.y, 32);

		//	//std::cout << "  + " << std::endl;
		//	//std::cout << " O| "  << mouse_pos.x << " | " << mouse_pos.y <<" | " << std::endl;
		//	//std::cout << " C| " << mouse_pos_converted.x << " | " << mouse_pos_converted.y << " | " << std::endl;

		//	if(rect_box.contains(mouse_pos))
		//	//	_status = Status::Hover;


		//	//if (isPointInsidePolygon(mouse_pos, points, )) {
		//	//	//std::cout << isPointInsidePolygon(mouse_pos, points, _shape.getGlobalBounds());
		//	//	const sf::Vector2f size = sf::Vector2f(rectGB.width, rectGB.height);
		//	//	_status = Status::Hover;
		//	//}
		//	
		//	//if (rect.contains(mouse_pos)) {
		//	//	const sf::Vector2f size = sf::Vector2f(rectGB.width, rectGB.height);
		//	//	_status = Status::Hover;
		//	//}

		//	if ((old_status & Status::Hover) && !(_status & Status::Hover))
		//		onMouseLeft();
		//	else if (!(old_status & Status::Hover) && (_status & Status::Hover))
		//		onMouseEntered();
		//}


		return res;
	}

	template<typename GEOMETRY>
	bool  Tile<GEOMETRY>::isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox)
	{
		if (!boundingBox.contains(point))
			return false;

		bool isInside{ false };
		sf::Vector2f pointOutsideBoundingBox{ boundingBox.left - 1, boundingBox.top - 1 };
		unsigned int v{ 0 };
		size_t s{ polygonVertices.size() - 1 };
		unsigned int w{ static_cast<unsigned int>(s) };
		for (; v < polygonVertices.size(); w = v++)
		{
			if (doLinesIntersect({ { polygonVertices[v], polygonVertices[w] },{ pointOutsideBoundingBox, point } })) {
				isInside = !isInside;
				break;
			}
		}
		return isInside;
	}
	template<typename GEOMETRY>
	bool Tile<GEOMETRY>::CCW(const std::vector<sf::Vector2f>& points)
	{
		if (points.size() != 3)
			return false;

		return (points[2].y - points[0].y) * (points[1].x - points[0].x) > (points[1].y - points[0].y) * (points[2].x - points[0].x);
	}

	// vector of (2) lines. line is a vector of (2) vector2fs (the points of the line).
	// i.e. { { line1.x, line.y }, { line2.x, line2.y } }
	template<typename GEOMETRY>
	bool Tile<GEOMETRY>::doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines)
	{
		if (lines.size() != 2)
			return false;
		if ((lines[0].size() != 2) || (lines[1].size() != 2))
			return false;

		return	(CCW({ lines[0][0], lines[1][0], lines[1][1] }) !=
				CCW({ lines[0][1], lines[1][0], lines[1][1] })) &&
				(CCW({ lines[0][0], lines[0][1], lines[1][0] }) !=
				CCW({ lines[0][0], lines[0][1], lines[1][1] }));
	}

	template<typename GEOMETRY>
	inline sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(float x, float y, float scale) {
		return GEOMETRY::mapPixelToCoords(x, y, scale);
	}

	template<typename GEOMETRY>
	inline sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(const sf::Vector2f& pos, float scale) {
		return GEOMETRY::mapPixelToCoords(pos.x, pos.y, scale);
	}

	template<typename GEOMETRY>
	inline sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(int x, int y, float scale) {
		return GEOMETRY::mapCoordsToPixel(x, y, scale);
	}

	template<typename GEOMETRY>
	inline sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(const sf::Vector2i& pos, float scale) {
		return GEOMETRY::mapCoordsToPixel(pos.x, pos.y, scale);
	}

	template<typename GEOMETRY>
	Tile<GEOMETRY>::Tile(int pos_x, int pos_y, float scale): _status(Status::None) {
		
		_shape = GEOMETRY::getShape();
		_box = GEOMETRY::getBox();
		
		//_shape.setOutlineColor(sf::Color(255, 255, 255, 75));
		_shape.setOutlineThickness(1.f / scale);
		setOutlineColor(sf::Color(200, 200, 200, 50));

		_box.setScale(scale,scale);
		_shape.setScale(scale, scale);

		_box.setOutlineThickness(1.f / scale);
		_box.setOutlineColor(sf::Color::Cyan);
		setCoords(pos_x, pos_y);
	}

	template<typename GEOMETRY>
	template< typename ...Args>
	inline void Tile<GEOMETRY>::setFillColor(Args&& ... args)
	{
		_shape.setFillColor(std::forward<Args&>(args)...);
	}

	template<typename GEOMETRY>
	template< typename ...Args>
	inline void Tile<GEOMETRY>::setPosition(Args&& ... args)
	{
		_shape.setPosition(args...);
	}

	template<typename GEOMETRY>
	template< typename ...Args>
	inline void Tile<GEOMETRY>::setCoords(Args&& ... args)
	{
		sf::Vector2f pos = mapCoordsToPixel(args..., _shape.getScale().x);
		_shape.setPosition(pos);
		_box.setPosition(pos);
	}

	template<typename GEOMETRY>
	inline sf::Vector2f Tile<GEOMETRY>::getPosition()const
	{
		return _shape.getPosition();
	}

	template<typename GEOMETRY>
	inline void Tile<GEOMETRY>::setTexture(const sf::Texture *texture, bool resetRect)
	{
		_shape.setTexture(texture, resetRect);
	}

	template<typename GEOMETRY>
	inline void Tile<GEOMETRY>::setTextureRect(const sf::IntRect& rect)
	{
		_shape.setTextureRect(rect);
	}

	template<typename GEOMETRY>
	inline sf::FloatRect Tile<GEOMETRY>::getGlobalBounds()const
	{
		return _shape.getGlobalBounds();
	}

	template<typename GEOMETRY>
	inline sf::FloatRect Tile<GEOMETRY>::getLocalBounds()const
	{
		return _shape.getLocalBounds();
	}

	template<typename GEOMETRY>
	inline void Tile<GEOMETRY>::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_shape, states);
		//target.draw(_box, states);
		//target.draw(_trigger, states);
	}


}