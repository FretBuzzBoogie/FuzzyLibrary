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
			///List to store all the FuzzyActions of the same type
			FuzzyList<IFuzzyAction<T_RET_TYPE(T_ARGS...)>*>* m_pListActions = nullptr;

		protected:
			FuzzyDelegateBase()
			{
				m_pListActions = new FuzzyList<IFuzzyAction<T_RET_TYPE(T_ARGS...)>*>();
			}

			virtual ~FuzzyDelegateBase()
			{
				int l_iActionListCount = m_pListActions->GetCount();
				for (int l_iListIndex = 0; l_iListIndex < l_iActionListCount; l_iListIndex++)
				{
					delete m_pListActions->GetAtIndex(l_iListIndex);
				}
				m_pListActions = nullptr;
			}

			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
			void Add(T_CLASS_TYPE* a_Instance)
			{
				FuzzyAction<T_RET_TYPE(T_ARGS...) >* l_newFuzzyAction = FuzzyAction<T_RET_TYPE(T_ARGS...) >::GetFuzzyAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
				IFuzzyAction<T_RET_TYPE(T_ARGS...)>* l_newIFuzzyAction = static_cast<IFuzzyAction<T_RET_TYPE(T_ARGS...)>*>(l_newFuzzyAction);
				m_pListActions->Add(l_newIFuzzyAction);
			}

			T_RET_TYPE Invoke(T_ARGS... a_Args)
			{
				int l_iFunListCount = m_pListActions->GetCount();
				T_RET_TYPE l_Return{};
				for (int l_iFuncIndex = 0; l_iFuncIndex < l_iFunListCount; l_iFuncIndex++)
				{
					l_Return += m_pListActions->GetAtIndex(l_iFuncIndex)->Invoke(a_Args...);
				}

				return l_Return;
			}

	public:
			
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