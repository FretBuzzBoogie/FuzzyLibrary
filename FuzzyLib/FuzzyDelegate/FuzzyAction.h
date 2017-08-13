#pragma once
#include <iostream>
#include "..\FuzzyList\FuzzyList.h"
#include "..\Utils\IFuzzyDebug.h"
#include <functional>
#include "..\FuzzyDelegate\FuzzyDelegateBase.h"
#include "..\FuzzyDelegate\FuzzyDelegate.h"
#include "FuzzyDelegate\FuzzyAction.h"

namespace FuzzyLib
{

	template<typename T1> class IFuzzyAction;

	template <typename T_RET_TYPE, typename ...T_ARGS>
	class IFuzzyAction<T_RET_TYPE(T_ARGS...)>
	{
		public :

			virtual T_RET_TYPE Invoke(T_ARGS... a_Args) = 0;

			virtual ~IFuzzyAction()
			{
			}
	};


	template<typename T1> class FuzzyAction;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class FuzzyAction <T_RET_TYPE(T_ARGS...)> : public IFuzzyAction<T_RET_TYPE(T_ARGS...)>
	{

	///PRIVATE VARIABLES
	private:
		using FUNC_STUB = T_RET_TYPE(*)(void* a_pThis, T_ARGS...);
		FUNC_STUB m_pFuncStub = nullptr;
		void* m_pObjectPtr = nullptr;

	///PRIVATE SOURCE
	private:

	public:
		FuzzyAction()
		{
		}

		FuzzyAction(void* a_pObj , FUNC_STUB a_pFuncStub)
		{
			m_pObjectPtr = a_pObj;
			m_pFuncStub = a_pFuncStub;
		}

		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
		static FuzzyAction<T_RET_TYPE(T_ARGS...)>* GetFuzzyAction(T_CLASS_TYPE*& a_pInstance)
		{
			std::cout << "Getting Fuzzy action\n";
			return new FuzzyAction<T_RET_TYPE(T_ARGS...)>(a_pInstance, CreateFuncStub<T_CLASS_TYPE, T_METHOD>);
		}

		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
		static T_RET_TYPE CreateFuncStub(void* a_pObj, T_ARGS... a_Args )
		{
			T_CLASS_TYPE* l_Obj = static_cast<T_CLASS_TYPE*>(a_pObj);
			return (l_Obj->*T_METHOD)(a_Args...);
		}
		
		virtual T_RET_TYPE Invoke(T_ARGS... a_Args) override
		{
			return (*m_pFuncStub)(m_pObjectPtr ,a_Args...);
		}
	};
}