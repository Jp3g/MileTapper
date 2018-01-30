#include "SquareIso.hpp"
#include <cmath>

namespace MileTapper {
			sf::ConvexShape SquareIso::_box;
			sf::ConvexShape SquareIso::_shape;
			SquareIso::__Initiatiser SquareIso::__initiatiser__;

			const float height = 1;
			const float width = 2;

			const sf::ConvexShape& SquareIso::getBox() {
				return _box;
			}

			const sf::ConvexShape& SquareIso::getShape() {
				return _shape;
			}

			sf::Vector2f SquareIso::mapCoordsToPixel(int x, int y, float scale) {
				return sf::Vector2f((x + y) * width / 2 * scale, (-x + y) * height / 2 * scale);
			}

			sf::Vector2i SquareIso::mapPixelToCoords(float x, float y, float scale) {
				return round((x / width - y / height) / scale, (x / width + y / height) / scale);
			}

			sf::Vector2i SquareIso::round(float x, float y) {
				return sf::Vector2i(x + 0.5, y + 0.5);
			}

			sf::IntRect SquareIso::getTextureRect(int x, int y, float scale) {
				sf::Vector2f pos = mapCoordsToPixel(x, y, scale);
				sf::IntRect res(pos.x, pos.y, width * scale, height * scale);

				return res;
			}

			int SquareIso::distance(int x1, int y1, int x2, int y2) {
				float x = x1 - x2;
				x *= x;

				float y = y1 - y2;
				y *= y;

				return ceil(sqrt(x + y));
			}

			void SquareIso::init() {

				_shape.setPointCount(4);
				_shape.setPoint(0, sf::Vector2f(width / 2, 0));
				_shape.setPoint(1, sf::Vector2f(width, height / 2));
				_shape.setPoint(2, sf::Vector2f(width / 2, height));
				_shape.setPoint(3, sf::Vector2f(0, height / 2));

				_shape.setOrigin(width / 2, height / 2);

				_box.setPointCount(4);
				_box.setPoint(0, sf::Vector2f(width, 0));
				_box.setPoint(1, sf::Vector2f(width, height));
				_box.setPoint(2, sf::Vector2f(0, height));
				_box.setPoint(3, sf::Vector2f(0, 0));

				_box.setOrigin(width / 2, height / 2);
				_box.setOutlineColor(sf::Color::Cyan);

				_box.setFillColor(sf::Color(0, 0, 0, 0));


			}
}