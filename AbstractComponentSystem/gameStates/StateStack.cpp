//Evan Gordon

#include "StateStack.h"

StateStack::StateStack():
	window(new sf::RenderWindow(sf::VideoMode(1280, 640), "Alpha Gameu Name Here")), 
	gameEvent(new sf::Event), gameFont(new sf::Font), newState(StateType::Main)
{
	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(60);

	if(!gameFont->loadFromFile("kongtext.ttf")){throw(42);}

	//add config file at some point so settings will be saved and loaded
	Locator::init(window, gameFont);

	versionNum = sf::Text("Pre-Alpha", *gameFont, 14);
	versionNum.setRotation(45);
	versionNum.setPosition(1190, 0);
	push();
}

void StateStack::push()
{
	switch (newState)
	{
	case None:
		break; 
	case Main:
		stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new MainMenuState(window, gameEvent, gameFont))));
		stack[stack.size() - 1].second->initialize();
		break;
	case CreateMap:
		stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new MapCreatorState(window, gameEvent, gameFont, true))));
		stack[stack.size() - 1].second->initialize();
		break;
	case Edit:
	{
				 if (stack.size() > 1 && stack[stack.size() - 1].first == SelectMap)
				 {
					 auto mapState = dynamic_cast<MapSelectState*>(stack[stack.size() - 1].second.get());
					 std::string newMapName = mapState->getSelectedMapName();//get the name of map that will be switched to
					 stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new GameState(window, gameEvent, gameFont, false))));

					 if (newMapName != "")//make sure you actually have a new map name to load
					 {
						 auto mapEditor = dynamic_cast<GameState*>(stack[stack.size() - 1].second.get());
						 stack[stack.size() - 1].second->initialize();
						 mapEditor->getManager().initialize(newMapName);//initialize gamestate newState is newMap name
						 mapEditor = NULL;
						 delete mapEditor;
					 }
					 else
					 {
						 pop();//delete this later?
					 }
				 }
				 break;
	}
	case Play:
	{
				 if (stack.size() > 1 && stack[stack.size() - 1].first == SelectSave)
				 {
					 auto mapState = dynamic_cast<MapSelectState*>(stack[stack.size() - 1].second.get());
					 std::string newMapName = mapState->getSelectedMapName();//get the name of map that will be switched to
					 stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new GameState(window, gameEvent, gameFont, true))));
					 if (newMapName != "")
					 {
						 auto mapEditor = dynamic_cast<GameState*>(stack[stack.size() - 1].second.get());
						 stack[stack.size() - 1].second->initialize();
						 mapEditor->getManager().initialize(newMapName);//initialize gamestate newState is newMap name
						 mapEditor = NULL;
						 delete mapEditor;
					 }
					 else
					 {
						 pop();//delete this later?
					 }
				 }
				 break;
	}
	case SelectMap:
		stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new MapSelectState(window, gameEvent, gameFont, true))));
		stack[stack.size() - 1].second->initialize();
		break;
	case CreateSave:
		stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new MapCreatorState(window, gameEvent, gameFont, false))));//load with create save extension
		stack[stack.size() - 1].second->initialize();
		break;
	case SelectSave:
		stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new MapSelectState(window, gameEvent, gameFont, false))));
		stack[stack.size() - 1].second->initialize();
		break;
	case Settings:
		stack.push_back(std::make_pair(newState, std::shared_ptr<IsState>(new SettingsState(window, gameEvent, gameFont))));
		stack[stack.size() - 1].second->initialize();
		break;
	}
	newState = StateType::None;
}

void StateStack::pop()
{
	bool popped = false;

	if(stack.size() > 1)
	{
		stack.pop_back();
		popped = true;
	}
}

bool StateStack::handleEvents()
{
	return stack[stack.size() - 1].second->handleEvents();
}

void StateStack::update()
{
	newState = stack[stack.size() - 1].second->update();
	if (newState == StateType::Pop)
	{
		pop();
		stack[stack.size() - 1].second->initialize();
	}
	else
	{
		push();
	}
}

void StateStack::draw()
{
	window->clear();
	stack[stack.size() - 1].second->draw();
	window->draw(versionNum);
	window->display();
}

StateStack::~StateStack(){}