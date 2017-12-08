#pragma once

namespace FuzzyLib
{
	class IEventListener
	{
	private:

	public:
		virtual ~IEventListener() {};
	};

	template<typename T>
	class FuzzyEventListener : virtual public IEventListener
	{
	private:

	public:
		FuzzyEventListener()
		{
			
		}

		virtual ~FuzzyEventListener(){}

		void AddEventListener()
		{
			
		}

		virtual void Dispatch() = 0
		{
		
		}
	};

	class InputListener : public FuzzyEventListener<InputListener>
	{
	public:
		InputListener()
		{
			
		}

		virtual ~InputListener()
		{
			
		}

		virtual void Dispatch() override
		{

		}
	};
}