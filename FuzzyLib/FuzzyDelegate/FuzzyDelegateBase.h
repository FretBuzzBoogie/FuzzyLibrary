#pragma once
#include <iostream>
#include "..\FuzzyList\FuzzyList.h"
#include "..\Utils\IFuzzyDebug.h"
#include "FuzzyAction.h"
#include <functional>
#include <typeinfo>

namespace FuzzyLib
{
	template<typename T> class FuzzyDelegateBase;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class FuzzyDelegateBase <T_RET_TYPE(T_ARGS...)>
	{

		private:

			using T_IFUZZY_ACTION = IFuzzyAction<T_RET_TYPE(T_ARGS...)>;

			///List to store all the FuzzyActions of the same type
			FuzzyList<T_IFUZZY_ACTION*>* m_pListActions = nullptr;

			///Deletes all actions stored in the delegate list
			void DeleteAllActions()
			{
				int l_iActionListCount = m_pListActions->GetCount();
				for (int l_iListIndex = 0; l_iListIndex < l_iActionListCount; l_iListIndex++)
				{
					delete m_pListActions->GetAtIndex(l_iListIndex);
				}
			}

		protected:
			///Constructor, Instantiates the List that stores the Actions of type T_RET_TYPE(T_ARGS...)
			FuzzyDelegateBase()
			{
				m_pListActions = new FuzzyList<T_IFUZZY_ACTION*>();
			}

			///Destructor
			virtual ~FuzzyDelegateBase()
			{
				DeleteAllActions();
				m_pListActions = nullptr;
			}

			///Adds a member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
			void Add(T_CLASS_TYPE* a_Instance)
			{
				T_IFUZZY_ACTION* l_pNewIFuzzyAction = T_IFUZZY_ACTION::GetIFuzzyAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
				m_pListActions->Add(l_pNewIFuzzyAction);
			}

			///Adds a const member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...) const>
			void Add(T_CLASS_TYPE* const a_Instance)
			{
				T_IFUZZY_ACTION* const l_pNewIFuzzyAction = T_IFUZZY_ACTION::GetIFuzzyAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
				m_pListActions->Add(const_cast<T_IFUZZY_ACTION*>(l_pNewIFuzzyAction));
			}

			///Adds an static or global action into the list
			template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
			void Add()
			{
				T_IFUZZY_ACTION* l_l_pNewIFuzzyAction = T_IFUZZY_ACTION::GetIFuzzyAction<T_METHOD>();
				m_pListActions->Add(l_l_pNewIFuzzyAction);
			}

			///Calls all the actions stored within the delegate
			T_RET_TYPE Invoke(T_ARGS... a_Args) throw(std::out_of_range)
			{
				int l_iFunListCount = m_pListActions->GetCount();
				std::cout << "Curr Count::" << l_iFunListCount << "\n";

				try
				{
					if (l_iFunListCount == 0)
					{
						char* l_Error = "Delegate is empty\n";
						throw out_of_range(l_Error);
					}

					for (int l_iFuncIndex = 0; l_iFuncIndex < l_iFunListCount - 1; l_iFuncIndex++)
					{
						m_pListActions->GetAtIndex(l_iFuncIndex)->Invoke(a_Args...);
					}

					if (typeid(T_RET_TYPE) != typeid(void))
					{
						return m_pListActions->GetAtIndex((l_iFunListCount - 1))->Invoke(a_Args...);
					}
					m_pListActions->GetAtIndex((l_iFunListCount - 1))->Invoke(a_Args...);
				}
				catch (std::out_of_range& a_Exception)
				{
					throw;
				}
			}

			///Clears the stored actions of type withing the delegate
			void Clear()
			{
				DeleteAllActions();
				m_pListActions->Clear();
			}

	public:
			
			///Logs information regarding the current Delegate
			void DebugLog()
			{
				std::cout << "\n\nDebugging FuzzyDelegate\n";

				if (m_pListActions != nullptr)
				{
					std::cout << "FuzzyDelegate storing functions of return type "<< typeid(T_RET_TYPE).name()<< "()\n\n";
				}
			}
	};

}