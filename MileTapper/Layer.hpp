#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <list>
#include "VLayer.hpp"

namespace MileTapper {
	template<typename CONTENT>
	class Layer : public VLayer {
	public:
		Layer(const Layer&) = delete;
		Layer& operator=(const Layer&) = delete;
		Layer(const std::string& type, int z = 0, bool isStatic = false);
		virtual ~Layer();

		CONTENT* add(const CONTENT& content, bool resort = true);
		CONTENT* add(CONTENT&& content, bool resort = true);

		std::list<CONTENT*> getByCoords(const sf::Vector2i& coords, const VMap& map);
		bool remove(const CONTENT* content_ptr, bool resort = true);
		virtual void sort() override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states, const sf::FloatRect& viewport) override;
		std::list<CONTENT> _content;
	};

	template<typename CONTENT>
	class Layer<CONTENT*> : public VLayer
	{
	public:
		Layer(const Layer&) = delete;
		Layer& operator=(const Layer&) = delete;

		Layer(const std::string& type, int z = 0, bool isStatic = false);
		virtual ~Layer();

		CONTENT* add(CONTENT* content, bool resort = true);

		std::list<CONTENT*> getByCoords(const sf::Vector2i& coords, const VMap& map);

		bool remove(const CONTENT* content_ptr, bool resort = true);

		virtual void sort() override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states, const sf::FloatRect& viewport) override;

		std::list<CONTENT*> _content;

	};

	template<typename CONTENT>
	Layer<CONTENT>::Layer(const std::string& type, int z, bool isStatic) : VLayer(type, z, isStatic) {

	}

	template<typename CONTENT>
	Layer<CONTENT>::~Layer() {

	}

	template<typename CONTENT>
	CONTENT* Layer<CONTENT>::add(const CONTENT& content, bool resort) {
		_content.emplace_back(content);
		CONTENT* res = &_content.back();

		if (resort)
			sort();

		return res;
	}

	template<typename CONTENT>
	CONTENT* Layer<CONTENT>::add(CONTENT&& content, bool resort){
		_content.emplace_back(std::move(content));
		CONTENT* res = &_content.back();

		if (resort)
			sort();

		return res;
	}

	template<typename CONTENT>
	std::list<CONTENT*> Layer<CONTENT>::getByCoords(const sf::Vector2i& coords, const VMap& map) {
		std::list<CONTENT*> res;
		const auto end = _content.end();

		for (auto it = _content.begin(); it != end; ++it) {
			auto pos = it->getPosition();
			sf::Vector2i c = map.mapToPixelToCoords(pos.x, pos.y);
			if (c == coords)
				res.emplace_back(&(*it));
		}

		return res;
	}

	template<typename CONTENT>
	bool Layer<CONTENT>::remove(const CONTENT* content_ptr, bool resort) {
		auto it = std::find_if(_content.begin(), _content.end(), [content_ptr](const CONTENT& content) -> bool {
			return &content == content_ptr;
		});

		if (it != _content.end()) {
			_content.erase(it);
			if (resort)
				sort();

			return true;
		}

		return false;
	}

	template<typename CONTENT>
	void Layer<CONTENT>::sort() {
		_content.sort([](const CONTENT& a, const CONTENT& b) -> bool {
			auto pos_a = a.getPosition();
			auto pos_b = b.getPosition();

			return (pos_a.y < pos_b.y) || (pos_a.y == pos_b.y && pos_a.x < pos_b.x);
		});
	}

	template<typename CONTENT>
	void Layer<CONTENT>::draw(sf::RenderTarget& target, sf::RenderStates states, const sf::FloatRect& viewport) {
		if (_isStatic) {
			if (_lastViewport != viewport) {
				sf::Vector2u size(viewport.width + 0.5, viewport.height + 0.5);
				
				if (_renderTexture.getSize() != size) {
					_renderTexture.create(size.x, size.y);
					_sprite.setTexture(_renderTexture.getTexture(), true);
				}

				_renderTexture.setView(sf::View(viewport));
				_renderTexture.clear();

				auto end = _content.end();
				for (auto it = _content.begin(); it != end; ++it) {
					CONTENT& content = *it;
					auto pos = content.getPosition();

					if (viewport.contains(pos.x, pos.y))
						_renderTexture.draw(content);
				}

				_renderTexture.display();
				_lastViewport = viewport;
				_sprite.setPosition(viewport.left, viewport.top);
			}

			target.draw(_sprite, states);
		}else{
			auto end = _content.end();

			for (auto it = _content.begin(); it != end; ++it) {
				const CONTENT& content = *it;
				auto pos = content.getPosition();

				if (viewport.contains(pos.x, pos.y))
					target.draw(content, states);
			}
		}
	}

	/////////////////////// LAYER PTR ////////////////////////////
	//
	template<typename CONTENT>
	Layer<CONTENT*>::Layer(const std::string& type, int z, bool isStatic) : VLayer(type, z, isStatic)
	{
	}

	template<typename CONTENT>
	Layer<CONTENT*>::~Layer()
	{
	}

	template<typename CONTENT>
	CONTENT* Layer<CONTENT*>::add(CONTENT* content, bool resort)
	{
		_content.emplace_back(content);
		CONTENT* res = _content.back();
		if (resort)
			sort();
		return res;
	}

	template<typename CONTENT>
	std::list<CONTENT*> Layer<CONTENT*>::getByCoords(const sf::Vector2i& coords, const VMap& map)
	{
		std::list<CONTENT*> res;
		const auto end = _content.end();
		for (auto it = _content.begin(); it != end; ++it)
		{
			auto pos = (*it)->getPosition();
			sf::Vector2i c = map.mapPixelToCoords(pos.x, pos.y);
			if (c == coords)
				res.emplace_back(*it);
		}
		return res;
	}

	template<typename CONTENT>
	bool Layer<CONTENT*>::remove(const CONTENT* content_ptr, bool resort)
	{
		auto it = std::find(_content.begin(), _content.end(), content_ptr);
		if (it != _content.end())
		{
			_content.erase(it);
			if (resort)
				sort();
			return true;
		}
		return false;
	}

	template<typename CONTENT>
	void Layer<CONTENT*>::sort()
	{
		_content.sort([](const CONTENT* a, const CONTENT* b)->bool {
			auto pos_a = a->getPosition();
			auto pos_b = b->getPosition();
			return (pos_a.y < pos_b.y) or (pos_a.y == pos_b.y and pos_a.x < pos_b.x);
		});
	}

	template<typename CONTENT>
	void Layer<CONTENT*>::draw(sf::RenderTarget& target, sf::RenderStates states, const sf::FloatRect& viewport)
	{
		if (_isStatic)
		{
			if (_lastViewport != viewport)
			{
				sf::Vector2u size(viewport.width + 0.5, viewport.height + 0.5);
				if (_renderTexture.getSize() != size)
				{
					_renderTexture.create(size.x, size.y);
					_sprite.setTexture(_renderTexture.getTexture(), true);
				}

				_renderTexture.setView(sf::View(viewport));

				_renderTexture.clear();
				auto end = _content.end();
				for (auto it = _content.begin(); it != end; ++it)
				{
					CONTENT& content = *(*it);
					auto pos = content.getPosition();
					if (viewport.contains(pos.x, pos.y))
					{
						_renderTexture.draw(content);
					}
				}
				_renderTexture.display();
				_lastViewport = viewport;
				_sprite.setPosition(viewport.left, viewport.top);
			}
			target.draw(_sprite, states);
		}
		else
		{
			auto end = _content.end();
			for (auto it = _content.begin(); it != end; ++it)
			{
				const CONTENT& content = *(*it);
				auto pos = content.getPosition();
				if (viewport.contains(pos.x, pos.y))
					target.draw(content, states);
			}
		}
	}
}