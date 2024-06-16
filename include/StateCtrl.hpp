//FINISHED

#pragma once
#include <stack>
#include <memory>
#include <State.hpp>
#include <GameSnake.hpp>

namespace Engine
{
    class StateCtrl
    {
    private:
        //Pila de almacenamiento de estados
        std::stack<std::unique_ptr<State>> m_stateStack;
        //Nuevo estado a añadir a la pila
        std::unique_ptr<State> m_newState;
        //El nuevo estado se añade a la pila solo cuando el estado actual termina

        //Indicadores cambiantes segun los metodos, para modificar la pila de estados
        bool m_add;
        bool m_replace;
        bool m_remove;
        bool m_removeAll;

    public:

        //Constructor sin cambios en la pila
        StateCtrl() : m_add(false), m_replace(false), m_remove(false), m_removeAll(false)
        {
        }

        ~StateCtrl() 
        {
        }

        //Añadir un nuevo estado a la pila
        //1er parametro es el estado a añadir
        //2do parametro indica si se reemplaza el estado actual
        void Add(std::unique_ptr<State> toAdd, bool replace = false)
        {
            m_add = true;

            //Almacena el estado a añadir
            m_newState = std::move(toAdd);

            m_replace = replace;
        }

        //Eliminar el estado actual de la pila
        void PopCurrent()
        {
            m_remove = true;
        }

        void PopAll()
        {
            m_removeAll = true;
            m_remove = false;
        }

        //Modificar la pila de estados
        void ProcessStateChange()
        {   
            if (m_removeAll)
            {
                while (!m_stateStack.empty())
                {
                    m_stateStack.pop();
                }
                m_removeAll = false;
            }
            //Si m_remove es verdadero y la pila no esta vacia
            else if(m_remove && (!m_stateStack.empty()))
            {
                //Elimina el estado actual o en la cima de la pila
                m_stateStack.pop();

                if(!m_stateStack.empty())
                {
                    //Inicia el estado que este en la cima de la pila
                    m_stateStack.top()->Start();
                }

                //Regresa a false para no eliminar mas estados
                m_remove = false;
            }

            //Si m_add es verdadero
            if(m_add)
            {
                //Si m_replace es verdadero y la pila no esta vacia
                if(m_replace && (!m_stateStack.empty()))
                {
                    //Elimina el estado actual o en la cima de la pila
                    m_stateStack.pop();

                    //Regresa a false para no eliminar mas estados
                    m_replace = false;
                }
                
                if(!m_stateStack.empty())
                {
                    //Pausa el estado que este en la cima de la pila
                    m_stateStack.top()->Pause();
                }

                //Pone el nuevo estado en la cima de la pila
                m_stateStack.push(std::move(m_newState));
                //Empieza el estado en la cima de la pila
                m_stateStack.top()->Start();
                //Inicializa el estado en la cima de la pila
                m_stateStack.top()->Init();

                //Regresa a false para no añadir mas estados
                m_add = false;
            }
        }


        //Devolver el estado actual
        std::unique_ptr<Engine::State> &GetCurrent()
        {
            //Regresa el estado en la cima de la pila
            return m_stateStack.top();
        }

        bool IsEmpty() const
        {
            return m_stateStack.empty();
        }

        
    };
}