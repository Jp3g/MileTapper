#include "MenuBar.hpp"
#include "Configuration.hpp"
#include "HLayout.hpp"
#include "Button.hpp"

namespace MileTapper {
	MenuBar::MenuBar(sf::RenderWindow& window) : Container(nullptr), ActionTarget(Configuration::gui_inputs), _window(window), _size(_window.getSize().x , 50) {
		Container::setLayout(new HLayout);
		Container::getLayout()->setSpace(0);

		ActionTarget::bind(Action(sf::Event::Resized), [this](const sf::Event& event) {

			if (Layout* layout = getLayout())
				layout->invalidate();
		});
	}

	MenuBar::~MenuBar() {

	}

	void MenuBar::draw() {
		_window.draw(*this);
	}

	void MenuBar::addButton(Button* button) {
		Container::getLayout()->add(button);
	}

	void MenuBar::bind(int key, const FuncType& callback) {
		ActionTarget::bind(key, callback);
	}

	void MenuBar::unbind(int key) {
		ActionTarget::unbind(key);
	}

	sf::Vector2f MenuBar::getSize() const {
		sf::Vector2u size = _window.getSize();

		if (_size.x != 0 && _size.y != 0)
			return sf::Vector2f(_size.x, Container::getSize().y);

		return sf::Vector2f(size.x, Container::getSize().y);
	}

	void MenuBar::processEvents() {
		sf::Vector2f parent_pos(0, 0);
		processEvents(parent_pos);
	}

	bool MenuBar::processEvent(sf::Event& event) {
		sf::Vector2f parent_pos(_position.x, _position.y);
		return processEvent(event, parent_pos);
	}

	void MenuBar::processEvents(const sf::Vector2f& parent_pos) {
		ActionTarget::processEvents();
		Container::processEvents(parent_pos);

		sf::Event event;

		while (_window.pollEvent(event))
			Container::processEvent(event, parent_pos);
	}

	bool MenuBar::processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) {
		bool res = ActionTarget::processEvent(event);

		if (!res)
			res = Container::processEvent(event, parent_pos);

		return res;
	}
}