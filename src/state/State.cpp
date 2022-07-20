#include "state/State.h"
#include "state/StateController.h"

//------------------------------ CONSTRUCTOR ----------------------------------
State::State(StateController& states, sf::RenderWindow& window)
    : m_window(window), m_event(), m_stateRunning(false), m_statesControl(states), m_prevState(nullptr)
{}