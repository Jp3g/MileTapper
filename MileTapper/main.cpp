#include "Game.hpp"
#include <iostream>
//#include <SFGUI/SFGUI.hpp>
//#include <SFGUI/Widgets.hpp>

int main(int argc, char* argv[]) {

	/*MileTapper::Editor editor(1600, 900);*/
	MileTapper::Game mileTapper(1600, 900);
	mileTapper.load();
	mileTapper.run();

	//// Create SFML's window.
	//sf::RenderWindow render_window(sf::VideoMode(800, 600), "Hello world!");

	//// Create an SFGUI. This is required before doing anything with SFGUI.
	//sfg::SFGUI sfgui;

	//// Create the label.
	//auto label = sfg::Label::Create("Hello world!");

	//// Create a simple button and connect the click signal.
	//auto button = sfg::Button::Create("Greet SFGUI!");
	//button->GetSignal(sfg::Widget::OnLeftClick).Connect([label] { label->SetText("Hello SFGUI, pleased to meet you!"); });

	//// Create a vertical box layouter with 5 pixels spacing and add the label
	//// and button to it.
	//auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	//box->Pack(label);
	//box->Pack(button, false);

	//// Create a window and add the box layouter to it. Also set the window's title.
	//auto window = sfg::Window::Create();
	//window->SetTitle("Hello world!");
	//window->Add(box);

	//// Create a desktop and add the window to it.
	//sfg::Desktop desktop;
	//desktop.Add(window);

	//// We're not using SFML to render anything in this program, so reset OpenGL
	//// states. Otherwise we wouldn't see anything.
	//render_window.resetGLStates();

	//// Main loop!
	//sf::Event event;
	//sf::Clock clock;

	//while (render_window.isOpen()) {
	//	// Event processing.
	//	while (render_window.pollEvent(event)) {
	//		desktop.HandleEvent(event);

	//		// If window is about to be closed, leave program.
	//		if (event.type == sf::Event::Closed) {
	//			return 0;
	//		}
	//	}

	//	// Update SFGUI with elapsed seconds since last call.
	//	desktop.Update(clock.restart().asSeconds());

	//	// Rendering.
	//	render_window.clear();
	//	sfgui.Display(render_window);
	//	render_window.display();
	//}

	//return 0;


	//int stop;
	//std::cin >> stop;

	return 0;
}
//#define CANVAS 0
//
//#include <SFGUI/SFGUI.hpp>
//#include <SFGUI/Widgets.hpp>
//#include <SFML/Graphics.hpp>
//
//#ifdef SFML_SYSTEM_MACOS
//#include "ResourcePath.hpp"
//#else
//std::string resourcePath(void)
//{
//	return "Z:\\Holy Church Of Fudge\\Documents\Visual Studio 2015\\Projects\MileTapper\\MileTapper\\media\\";
//}
//#endif
//
//#include <cassert>
//
//auto const WINDOW_SIZE = sf::Vector2f(1000, 800);
//auto const SIMULATION_SIZE = sf::Vector2f(800, 600);
//
//class HelloWorld
//{
//public:
//	// Our button click handler.
//	void OnButtonClick();
//
//	void Run();
//
//private:
//	// Create an SFGUI. This is required before doing anything with SFGUI.
//	sfg::SFGUI m_sfgui;
//
//	// Create the label pointer here to reach it from OnButtonClick().
//	sfg::Label::Ptr m_label;
//	bool m_labelTogle = false;
//};
//
//void HelloWorld::OnButtonClick()
//{
//	m_labelTogle = !m_labelTogle;
//	m_label->SetText(m_labelTogle ? "Hello SFGUI, pleased to meet you!" : "Hello world!");
//}
//
//void HelloWorld::Run()
//{
//	// Create SFML's window.
//	sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Hello world!", sf::Style::Close);
//
//	// Create the label.
//	m_label = sfg::Label::Create("Hello world!");
//
//	// Create a simple button and connect the click signal.
//	auto button = sfg::Button::Create("Greet SFGUI!");
//	button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&HelloWorld::OnButtonClick, this));
//
//
//	//         WINDOW STRUCTURE
//	//
//	//
//	//           ⤹ leftBox
//	//
//	//         ---------------------
//	//         | l |               |
//	//         | e |               |
//	//         | f |   S I M       |
//	//         | t |     U L A     |
//	//         |   |       T I O N |  ⟵ upperBox
//	//         | m |               |
//	//         | e |     A R E A   |
//	//         | n |               |
//	//         | u |               |
//	//         ---------------------
//	//         |   bottom panel    |  ⟵ bottomBox
//	//         ---------------------
//
//
//	// Simulation area
//#if defined(CANVAS) && CANVAS == 1
//	auto sfmlArea = sfg::Canvas::Create();
//#else
//	auto sfmlArea = sfg::Viewport::Create();
//#endif
//	sfmlArea->SetRequisition(SIMULATION_SIZE);
//	auto simulationBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 0);
//	simulationBox->Pack(sfmlArea);
//
//
//	// Left menu
//	auto leftBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10);
//	leftBox->SetRequisition({ WINDOW_SIZE.x - SIMULATION_SIZE.x - 20, 0 });
//	leftBox->Pack(m_label, false);
//	leftBox->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false);
//	leftBox->Pack(button, false);
//
//
//	// Upper box: left menu + simulation area
//	auto upperBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
//	upperBox->Pack(leftBox);
//	upperBox->Pack(sfg::Separator::Create(sfg::Separator::Orientation::VERTICAL), false);
//	upperBox->Pack(simulationBox);
//
//	// Bottom panel: add some utilities
//	auto checkBox1 = sfg::CheckButton::Create("check me! (1)");
//	auto checkBox2 = sfg::CheckButton::Create("check me! (2)");
//	auto bottomBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10);
//	bottomBox->Pack(checkBox1, false);
//	bottomBox->Pack(checkBox2, false);
//
//	// Build the main layout
//	auto mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
//	mainBox->Pack(upperBox);
//	mainBox->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false);
//	mainBox->Pack(bottomBox);
//
//	// Create a desktop and add the main layout to it.
//	sfg::Desktop desktop;
//	desktop.Add(mainBox);
//
//	// Load some additional stuff for the simulation area
//	//auto backgroundTexture = sf::Texture();
//	//assert(backgroundTexture.loadFromFile(resourcePath() + "ground.png"));
//	//auto background = sf::Sprite(backgroundTexture);
//
//	auto square = sf::CircleShape(50);
//	square.setFillColor(sf::Color::Red);
//
//	// Main loop!
//	sf::Clock clock;
//
//	while (renderWindow.isOpen()) {
//		sf::Event event;
//		while (renderWindow.pollEvent(event)) {
//			desktop.HandleEvent(event);
//
//			if (event.type == sf::Event::Closed) {
//				renderWindow.close();
//			}
//		}
//
//		// Update SFGUI with elapsed seconds since last call.
//		desktop.Update(clock.restart().asSeconds());
//
//		// Rendering
//#if defined(CANVAS) && CANVAS == 1
//		{
//			sf::RenderTexture rt;
//			rt.create(SIMULATION_SIZE.x, SIMULATION_SIZE.y);
//			rt.clear();
//			//rt.draw(background); // ~> entity.draw(rt);
//			rt.display();
//
//			sf::Sprite s(rt.getTexture());
//
//			// Render the simulation area
//			sfmlArea->Bind();
//			sfmlArea->Clear();
//
//			// sfmlCanvas->Draw(background); // OK, but sfmlCanvas is not a render target
//			sfmlArea->Draw(s);
//
//			sfmlArea->Display();
//			sfmlArea->Unbind();
//
//			renderWindow.resetGLStates();
//			renderWindow.clear();
//			m_sfgui.Display(renderWindow);
//			renderWindow.display();
//		}
//#else
//		{
//			auto simulationTransform = sf::Transform();
//			simulationTransform.translate({ WINDOW_SIZE.x - SIMULATION_SIZE.x - 10, 0 });
//
//			renderWindow.resetGLStates();
//			renderWindow.clear();
//			m_sfgui.Display(renderWindow);
//			renderWindow.draw(square, simulationTransform);
//			renderWindow.display();
//		}
//#endif
//	}
//}
//
//int main()
//{
//	HelloWorld hello_world;
//	hello_world.Run();
//
//		//int stop;
//		//std::cin >> stop;
//
//	return 0;
//}

