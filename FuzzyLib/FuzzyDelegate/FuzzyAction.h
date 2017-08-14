#pragma once
#include <iostream>
#include "..\FuzzyList\FuzzyList.h"
#include "..\Utils\IFuzzyDebug.h"
#include <functional>
#include "..\FuzzyDelegate\FuzzyDelegateBase.h"
#include "..\FuzzyDelegate\FuzzyDelegate.h"

namespace FuzzyLib
{

#pragma region Interface for a Fuzzy Action

	///Interface to a single action, an action can only be called via this interface
	template<typename T1> class IFuzzyAction;

	template <typename T_RET_TYPE, typename ...T_ARGS>
	class IFuzzyAction<T_RET_TYPE(T_ARGS...)>
	{
		public :

			///Calls the function with arguements
			virtual T_RET_TYPE Invoke(T_ARGS... a_Args) const = 0;

			virtual ~IFuzzyAction()
			{
			}
	};
#pragma endregion Interface for a Fuzzy Action




#pragma region Fuzzy Action

	template<typename T1> class FuzzyAction;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class FuzzyAction <T_RET_TYPE(T_ARGS...)> : public IFuzzyAction<T_RET_TYPE(T_ARGS...)>
	{

	///PRIVATE VARIABLES
	private:
		///Function template
		using FUNC_STUB = T_RET_TYPE(*)(void*, T_ARGS...);

		///Function pointer of the delegate type to be called
		FUNC_STUB m_pFuncStub = nullptr;

		///Pointer to the object which cointains the function to be called
		void* m_pObjectPtr = nullptr;

	///PRIVATE SOURCE
	private:

		///Constructor
		FuzzyAction(void* a_pObj , FUNC_STUB a_pFuncStub)
		{
			m_pObjectPtr = a_pObj;
			m_pFuncStub = a_pFuncStub;
		}

	public:

		///Constructor
		FuzzyAction() = delete;

		///Return an Action of member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
		static FuzzyAction<T_RET_TYPE(T_ARGS...)>* GetFuzzyAction(T_CLASS_TYPE*& a_pInstance)
		{
			return new FuzzyAction<T_RET_TYPE(T_ARGS...)>(a_pInstance, FunctionBlueprint<T_CLASS_TYPE, T_METHOD>);
		}

		///Return an Action of const member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)const>
		static FuzzyAction<T_RET_TYPE(T_ARGS...)>* GetFuzzyAction(T_CLASS_TYPE* const a_pInstance)
		{
			return new FuzzyAction<T_RET_TYPE(T_ARGS...)>(a_pInstance, FunctionBlueprint<T_CLASS_TYPE, T_METHOD>);
		}

		///Return an Action of static / global type 
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		static FuzzyAction<T_RET_TYPE(T_ARGS...)>* GetFuzzyAction()
		{
			return new FuzzyAction<T_RET_TYPE(T_ARGS...)>(nullptr, FunctionBlueprint<T_METHOD>);
		}

		///Acts as a member function template
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
		static T_RET_TYPE FunctionBlueprint(void* a_pObj, T_ARGS... a_Args )
		{
			T_CLASS_TYPE* l_Obj = static_cast<T_CLASS_TYPE*>(a_pObj);
			return (l_Obj->*T_METHOD)(a_Args...);
		}

		///Acts as a const member function template
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...) const>
		static T_RET_TYPE FunctionBlueprint(void* a_pObj, T_ARGS... a_Args)
		{
			T_CLASS_TYPE* l_Obj = static_cast<T_CLASS_TYPE*>(a_pObj);
			return (l_Obj->*T_METHOD)(a_Args...);
		}

		///Acts as a static function template
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		static T_RET_TYPE FunctionBlueprint(void* a_pObj, T_ARGS... a_Args)
		{
			return (*T_METHOD)(a_Args...);
		}
		
	protected:

		///Calls the function
		virtual T_RET_TYPE Invoke(T_ARGS... a_Args) const override
		{
			return (*m_pFuncStub)(m_pObjectPtr ,a_Args...);
		}
	};

	#pragma endregion Fuzzy Action

}