#pragma once 

#include "Widget.hpp"

namespace MileTapper {
	class Layout : public Widget {
	public:
		Layout(const Layout&) = delete;
		Layout& operator=(const Layout&) = delete;

		Layout(Widget* parent = nullptr);
		virtual ~Layout();

		void setSpace(float pixels);
		virtual void add(Widget* widget) = 0;

	protected:
		friend class Container;
		friend class Frame;
		float _space;
	};
}