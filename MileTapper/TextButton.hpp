#pragma once

#include "Button.hpp"
#include "Label.hpp"

namespace MileTapper {
	class TextButton : public Button {
	public:
		TextButton(const std::string& text, Widget* parent = nullptr);
		virtual ~TextButton();

		void setText(const std::string& text);
		void setCharaterSize(unsigned int size);

		void setTextColor(const sf::Color& color);
		void setFillColor(const sf::Color& color);
		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);
		
		virtual sf::Vector2f getSize() const override;

	private:
		sf::RectangleShape _shape;
		Label _label;
		void updateShape() override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Color _fillColor;
		sf::Color _outlineColor;

		virtual void onMouseEntered();
		virtual void onMouseLeft();
		virtual void onMousePressed();
		virtual void onMouseReleased();
	};
}