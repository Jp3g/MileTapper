#include "VMap.hpp"
#include "Map.hpp"

#include <iostream>
#include "SquareIso.hpp"
//#include "HexaIso.hpp" - Excluded from project
//#include "Square.hpp" - Excluded from project
#include <algorithm>

namespace MileTapper {

	VMap::VMap(float size) : _tileSize(size) {

	}

	VMap::~VMap() {
		clear();
	}

	bool VMap::loadFromFile(const std::string& filename)
	{

		//utils::json::Value* value = utils::json::Driver::parse_file(filename).get();
		//if (value)
		//{
		//	utils::json::Object& root = value->asObject();

		//	loadFromJson(root);
		//}
		//return value != nullptr;

		return false;
	}

	bool VMap::loadFromStream(std::istream& in)
	{
		//utils::json::Value* value = utils::json::Driver::parse(in).get();
		//if (value)
		//{
		//	utils::json::Object& root = value->asObject();

		//	loadFromJson(root);
		//}
		//return value != nullptr;

		return false;
	}

	void VMap::add(VLayer* layer, bool sort) {
		_layers.emplace_back(layer);

		if (sort)
			sortLayers();
	}

	void VMap::remove(size_t index) {
		delete _layers.at(index);
		_layers.erase(_layers.begin() + index);
	}

	void VMap::remove(VLayer* layer) {
		auto it = std::find(_layers.begin(), _layers.end(), layer);
		if (it != _layers.end()) {
			delete *it;
			_layers.erase(it);
		}
	}

	size_t VMap::size() const {
		return _layers.size();
	}

	VLayer* VMap::at(size_t index) const {
		return _layers.at(index);
	}

	void VMap::clear() {
		const size_t size = _layers.size();
		for (size_t i = 0; i < size; ++i)
			delete(_layers[i]);

		_layers.clear();
		_textures.clear();
	}

	float VMap::getTileSize() const {
		return _tileSize;
	}

	sf::Vector2i VMap::mapPixelToCoords(const sf::Vector2f& pos) const {
		return mapPixelToCoords(pos.x, pos.y);
	}

	sf::Vector2f VMap::mapCoordsToPixel(const sf::Vector2i& pos) const {
		return mapCoordsToPixel(pos.x, pos.y);
	}

	void VMap::sortLayers() {
		std::sort(_layers.begin(), _layers.end(), [](const VLayer* a, const VLayer* b) -> bool {
			return a->z() < b->z();
		});

		const size_t size = _layers.size();

		for (size_t i = 0; i < size; ++i)
			_layers[i]->sort();
	}

	//void VMap::processEvent(const sf::Event& event ) {
	//	const size_t size = _layers.size();

	//	for (size_t i = 0; i < size; ++i)
	//		_layers[i]->processEvent(event); // Process only visible tile ?

	//}

	void VMap::draw(sf::RenderTarget& target, sf::RenderStates states, const sf::FloatRect& viewport) const{
		sf::FloatRect delta_viewport(viewport.left - _tileSize,
			viewport.top - _tileSize,
			viewport.width + _tileSize * 2,
			viewport.height + _tileSize * 2);

		const size_t size = _layers.size();

		for (size_t i = 0; i < size; ++i)
			_layers[i]->draw(target, states, delta_viewport);

	}


	VMap* VMap::createMapFromFile(const char* filename) {
		VMap* res = nullptr;

		FILE* fp = fopen(filename, "rb");

		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		rapidjson::Document* document = new rapidjson::Document();
		document->ParseStream(is);

		if (!document->IsNull())
		{
			res = createMapFromJson(*document);
			delete document;
		}

		return res;
	}

	VMap* VMap::createMapFromStream(std::istream& in){
		VMap* res = nullptr;

		//utils::json::Value* value = utils::json::Driver::parse(in).get();
		//if (value)
		//{
		//	res = createMapFromJson(value->asObject());
		//	delete value;
		//}

		return res;
	}


	VMap* VMap::createMapFromJson(rapidjson::Document& root)
	{
		VMap* res = nullptr;

		rapidjson::Value& geometry = root["geometry"];
		std::string geometry_name = geometry["name"].GetString();
		float size = geometry["size"].GetFloat();

		//if (geometry_name == "Hexa")
		//{
		//	res = new Map<geometry::Hexa>(size);
		//	res->loadFromJson(root);
		//}
		//if (geometry_name == "HexaIso")
		//{
		//	res = new Map<MileTapper::HexaIso>(size);
		//	res->loadFromJson(root);
		//}
		//else if (geometry_name == "Square")
		//{
		//	res = new Map<MileTapper::Square>(size);
		//	res->loadFromJson(root);
		//}

		/*else*/ if (geometry_name == "SquareIso") {
			res = new Map<MileTapper::SquareIso>(size);
			res->loadFromJson(root);
		}else{
			std::cerr << "Unknow geometry '" << geometry_name << "'" << std::endl;
		}

		return res;
	}






}