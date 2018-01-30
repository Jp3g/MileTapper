#pragma once

#include "Widget.hpp"
#include <functional>

namespace MileTapper {
	class Button : public Widget {
	public:
		using FuncType = std::function<void(const sf::Event& event, Button& self)>;
		static FuncType defaultFunc;
		FuncType onClick;

		Button(Widget* parent = nullptr);
		virtual ~Button();

	protected:
		virtual bool processEvent(const sf::Event& event, const sf::Vector2f& pos_parent) override;
		virtual void onMousePressed();
		virtual void onMouseReleased();
		virtual void onMouseEntered();
		virtual void onMouseLeft();

	private:
		enum Status { None = 0, Hover = 1 };
		int _status;

	};
}