#include "Frame.hpp"
#include "Configuration.hpp"

namespace MileTapper {
	Frame::Frame(sf::RenderWindow& window, sf::Vector2f size) : Container(nullptr), ActionTarget(Configuration::gui_inputs),
		_window(window), _size(size) {

		//ActionTarget::bind(Action(sf::Event::Resized), [this](const sf::Event& event) {

		//	sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		//	this->_view = sf::View(visibleArea);

		//	if (Layout* layout = getLayout())
		//		layout->updateShape();
		//});
	}

	Frame::~Frame() {

	}

	void Frame::draw() {
		_window.draw(*this);
	}

	void Frame::bind(int key, const FuncType& callback) {
		ActionTarget::bind(key, callback);
	}

	void Frame::unbind(int key) {
		ActionTarget::unbind(key);
	}

	sf::Vector2f Frame::getSize() const {
		sf::Vector2u size = _window.getSize();

		if(_size.x !=0 && _size.y !=0)
			return sf::Vector2f(_size.x, _size.y);

		return sf::Vector2f(size.x, size.y);
	}

	void Frame::processEvents() {
		sf::Vector2f parent_pos(0, 0);
		processEvents(parent_pos);
	}

	bool Frame::processEvent(sf::Event& event) {
		sf::Vector2f parent_pos(_position.x, _position.y);
		return processEvent(event, parent_pos);
	}

	void Frame::processEvents(const sf::Vector2f& parent_pos) {
		ActionTarget::processEvents();
		Container::processEvents(parent_pos);

		sf::Event event;

		while (_window.pollEvent(event))
			Container::processEvent(event, parent_pos);
	}

	bool Frame::processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) {
		bool res = ActionTarget::processEvent(event);

		if (!res)
			res = Container::processEvent(event, parent_pos);

		return res;
	}

	//void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
	//{
	//	//if (_isVisible)
	//	//{
	//		//sf::View view = target.getView();
	//		//target.setView(_view);

	//		//Container::draw(target, states);

	//		//target.setView(view);
	//	//}
	//}



}