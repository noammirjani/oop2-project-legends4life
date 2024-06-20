#include "state/StateController.h"


//----------------------------------- changeState -----------------------------
//will remove the current state from the stack and add a new state to the end of
//the stack.
void StateController::changeState(std::unique_ptr<State> state)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.pop();
	}

	state->init();
	m_gameStates.push(std::move(state));
}


//------------------------------- push ----------------------------------------
//will pause the current stateand add a new state to the end of the stack.
void StateController::pushState(std::unique_ptr<State> stateToEnter)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.top()->pause();
		stateToEnter->setPtrToLastState(m_gameStates.top().get());
	}


	stateToEnter->init();
	m_gameStates.push(std::move(stateToEnter));
}


//------------------------------- pop -----------------------------------------
// will remove the last state on the stackand set the current state to the previous state on the stack.
void StateController::popState()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.pop();
	}

	if (m_gameStates.empty()) m_window.close();
	else m_gameStates.top()->resume();
}


//---------------------------------- render -----------------------------------
void StateController::render()
{
	//Render items
	if (!m_gameStates.empty())
	{
		m_gameStates.top()->render();
	}
}


//----------------------------------- update ----------------------------------
void StateController::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.top()->update();
	}
}


//----------------------------------- handleEvents ----------------------------
void StateController::handleEvents()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.top()->handleEvents();
	}
	if (m_gameStates.empty()) m_window.close();
}


//----------------------------------- clearToStart ----------------------------
void StateController::clearToStart()
{
	std::unique_ptr<State> statePtr;

	while (!m_gameStates.empty())
	{
		statePtr = std::move(m_gameStates.top());
		m_gameStates.pop();
	}

	m_gameStates.push(std::move(statePtr));
	m_gameStates.top()->resume();
}


//------------------------------ double ---------------------------------------
void StateController::changeDoubleState(std::unique_ptr<State> state)
{
	popState();
	changeState(std::move(state)); 
}