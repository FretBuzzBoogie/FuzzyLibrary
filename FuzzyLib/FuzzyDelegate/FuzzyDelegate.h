#pragma once
#include <iostream>
#include "..\FuzzyList\FuzzyList.h"
#include "..\Utils\IFuzzyDebug.h"
#include <functional>
#include "..\FuzzyDelegate\FuzzyDelegateBase.h"

namespace FuzzyLib
{
	template<typename T> class FuzzyDelegate;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class FuzzyDelegate <T_RET_TYPE(T_ARGS...)> : protected FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>, public IFuzzyDebug
	{
		private:

		public:
			///Add member function contained within given class type into the delagte list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
			void Add(T_CLASS_TYPE* a_TObject)
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Add<T_CLASS_TYPE, T_METHOD>(a_TObject);
			}

			///Adds const member function contained within given class type into the delagte 
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...) const>
			void Add(T_CLASS_TYPE* const a_TObject)
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Add<T_CLASS_TYPE, T_METHOD>(a_TObject);
			}

			///Adds static functionn into delegate list
			template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
			void Add()
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Add<T_METHOD>();
			}

			///Calls the function stored in the delegate list
			T_RET_TYPE Invoke(T_ARGS... a_Args) throw(std::out_of_range)
			{
				try
				{
					return FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Invoke(a_Args...);
				}
				catch (std::out_of_range& a_Exception)
				{
					std::cout << "DelegateError::Cannot invoke::" << a_Exception.what() << "\n";
				}
			}

			///Logs the contents of the List.
			virtual void DebugLog() override
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::DebugLog();
			}

			///Clears the stored actions of type withing the delegate
			void Clear()
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Clear();
			}

	};
}