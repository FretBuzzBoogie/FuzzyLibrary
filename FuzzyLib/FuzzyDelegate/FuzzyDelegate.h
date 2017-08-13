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

			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
			void Add(T_CLASS_TYPE* a_TObject)
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Add<T_CLASS_TYPE, T_METHOD>(a_TObject);
			}

			T_RET_TYPE Invoke(T_ARGS... a_Args)
			{
				return FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::Invoke(a_Args...);
			}

			//Logs the contents of the List.
			virtual void DebugLog() override
			{
				FuzzyDelegateBase<T_RET_TYPE(T_ARGS...)>::DebugLog();
			}

	};
}