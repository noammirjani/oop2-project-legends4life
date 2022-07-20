#pragma once
#include <SFML/Graphics.hpp>
#include "gameManage/Audio.h"


class StateController;

//the State design pattern allows us to controll all the game eazily. prehaps controll the menu navigation.
//good explnations in https://www.dreamincode.net/forums/topic/118898-state-management/  (in cpp)       &&
//				   in http://sbgames.org/papers/sbgames06/6.pdf                          (book)         &&
//				   in http://blog.nuclex-games.com/tutorials/cxx/game-state-management/  (in #c)


// a state is almost like a seperate program within the game. Each state will handle its own events, has a different background,
// and draw the next frame on the screen. in this game design the controller ar ather class doesnt need to recognize all the kinds
// of the states. each one is independent. 
// 
//arcitecture: stateController is the states manager simply stores the active game state and lets us switch to another game state.
//			   state is abtract class that all the kinds of state inhirints from it. 
//examples of states:  states: intro animation, main menu, pause menu, endgame screen

//the base class for the state pattern
//Abstract class
class State
{
public:
	State(StateController&, sf::RenderWindow&);
	virtual ~State() = default;

	//virtual functions

	//setState 
	virtual void init() = 0;

	//for game loop 
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//other functionality 
	virtual void pause() {}
	virtual void resume() {}
	virtual void display(){}

	void setPtrToLastState(State* ptr) { m_prevState = ptr; }
	

protected:
	//sfml
	sf::Event         m_event;
	sf::Sprite        m_background;
	sf::RenderWindow& m_window;

	//states
	StateController& m_statesControl;
	State* m_prevState; 

private:
	bool            m_stateRunning;

};