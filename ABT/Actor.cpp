#include "stdafx.h"
#include "Actor.h"
#include "ABT.h"
ABT::SignaleId::SignaleId(int id)
{
  m_id = id;
}

ABT::State::State(Actor* actor)
  : m_currentSignale(-1)
{
  m_actor = actor;
}

ABT::State::~State()
{
  SafeDel(m_currentAnim);
}

ABT::StateMachine::~StateMachine()
{
  for (auto& state : m_states)
    SafeDel(state.second);
}

void ABT::StateMachine::Signale(SignaleId signale)
{
  State* nextState = m_currentState->Signaled(signale);
  
  if (nextState == nullptr)
    return;

  m_currentState->TransitionOut(nextState);
  nextState->TransitionIn(m_currentState);
  m_currentState = nextState;
}

bool ABT::StateMachine::QueryState(std::string stateName)
{
  return m_states.find(stateName) != m_states.end();
}

ABT::Actor::Actor()
{
  m_stateMachine = new StateMachine();
}

ABT::Actor::~Actor()
{
  SafeDel(m_stateMachine);
}

ABT::EntityType ABT::Actor::GetType()
{
  return EntityType::Entity_Actor;
}
