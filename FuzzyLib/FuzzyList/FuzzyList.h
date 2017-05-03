#pragma once
#include <iostream>
#include <initializer_list>
#include "..\Base\IFuzzyBase.h"
#include <vector>
#include <array>

namespace FuzzyLib
{
		
	template <typename T>
	class FuzzyList : IFuzzyBase
	{
		///PRIVATE VARIABLES
		private:
			static constexpr int EMPTY_LIST_SIZE = 0;
			static constexpr int DEFAULT_CAPACITY = 4;
			int m_iCapacity = 0;
			int m_iCount = 0;
			T** m_List = nullptr;

		///PRIVATE SOURCE
		private:

			//Conditionally allocates memory to the list
			//If capacity to allocate is less than double current capacity,
			////sets capacity as double the current capacity
			//Else sets the capacity to the arguement 
			void AllocateMemory(const int& a_iCapacity, const bool a_bIsListEmpty = false)
			{
				if (a_iCapacity <= m_iCapacity)
				{
					std::cout << "FuzzyList::AllocateMemory:: Allocation of memory is less than already allocated memory.\n";
					return;
				}

				int l_iDoubleCapacity = 2 * m_iCapacity;
				int l_iMemoryToAllocate = a_iCapacity <= l_iDoubleCapacity ? l_iDoubleCapacity : a_iCapacity;
				ResizeList(l_iMemoryToAllocate, a_bIsListEmpty);
			}

			//Called on creating a list in the constructor
			void InitList(const std::initializer_list<T> &a_initList)
			{
				int l_initListSize = a_initList.size();
				AllocateMemory(l_initListSize, true);

				int l_iInializerIndex = 0;
				for (T l_Obj : a_initList)
				{
					m_List[l_iInializerIndex] = new T(l_Obj);
					l_iInializerIndex++;
				}
				m_iCount = l_initListSize;
			}

			//Resizes the capacity of the list
			//If list is empty then do not copy contents of list before resize
			void ResizeList(const int& a_iMemoryToAllocate, const bool a_bIsListEmpty = false)
			{
				T** tempList = nullptr;
				bool l_bIsListInitialCreated = m_List == nullptr;
	
				if (!a_bIsListEmpty)
				{
					tempList = new T*[m_iCount];
					for (int l_iTempListIndex = 0; l_iTempListIndex < m_iCount; l_iTempListIndex++)
					{
						tempList[l_iTempListIndex] = m_List[l_iTempListIndex];
					}
				}

				if (m_List != nullptr)
				{
					delete[] m_List;
				}

				m_List = new T*[a_iMemoryToAllocate];
				m_iCapacity = a_iMemoryToAllocate;

				if (!a_bIsListEmpty)
				{
					for (int l_iTempListIndex = 0; l_iTempListIndex < m_iCount; l_iTempListIndex++)
					{
						m_List[l_iTempListIndex] = tempList[l_iTempListIndex];
					}
					for (int l_iListIndex = m_iCount; l_iListIndex < m_iCapacity; l_iListIndex++)
					{
						m_List[l_iListIndex] = new T();
					}

					delete[] tempList;
					tempList = nullptr;
				}
			}

		///PUBLIC SOURCE
		public:

	#pragma region Constructor/Destructor

			//Default Constructor
			FuzzyList() : FuzzyList(EMPTY_LIST_SIZE)
			{
			}
			
			//Constructor to initialize a list
			FuzzyList(const std::initializer_list<T>& a_initList)
			{
				InitList(a_initList);
			}

			//Constructor to initialize with input capacity
			FuzzyList(const int& a_iInitCapacity)
			{
				AllocateMemory(a_iInitCapacity, true);
			}

			//Destructor
			~FuzzyList()
			{
				for (int l_iListIndex = 0; l_iListIndex < m_iCapacity; l_iListIndex++)
				{
					delete m_List[l_iListIndex];
					m_List[l_iListIndex] = nullptr;
				}
				delete[] m_List;
				m_List = nullptr;
			}

	#pragma endregion Constructor/Destructor

			//Adds the object at the end of the List
			void Add(T& a_Obj)
			{
				AllocateMemory(m_iCount + 1);
				if (m_List[m_iCount] == nullptr)
				{
					m_List[m_iCount] = new T(a_Obj);
				}
				else
				{
					*m_List[m_iCount] = a_Obj;
				}
				m_iCount++;
			}

			//Adds a range of Objects at the end of the list
			void AddRange(FuzzyList<T>& a_List)
			{
				int l_iCountBeforeAdd = m_iCount;
				int l_iNewCount = m_iCount + a_List.GetCount();

				AllocateMemory(l_iNewCount);
				m_iCount = l_iNewCount;

				for (int l_iCountIndex = 0; (l_iCountIndex + l_iCountBeforeAdd) < m_iCount; l_iCountIndex++)
				{
					if (m_List[l_iCountIndex + l_iCountBeforeAdd] == nullptr)
					{
						m_List[l_iCountIndex + l_iCountBeforeAdd] = new T(a_List[l_iCountIndex]);
					}
					else
					{
						m_List[l_iCountIndex + l_iCountBeforeAdd] = &a_List[l_iCountIndex];
					}
				}
			}

			//Clears the contents of the list
			void Clear()
			{
				m_iCount = EMPTY_LIST_SIZE;
			}

	#pragma region Getters
		
			//Gets the count of the the elements of type T in the internal array 
			const int& GetCount() const
			{
				return m_iCount;
			}

			//Gets the capacity of the internal array with elements of type T
			const int& GetCapacity() const
			{
				return m_iCapacity;
			}

			// Get the variable stored at index by reference
			T& GetAtIndex(const int& a_iIndex) const
			{
				if (a_iIndex >= m_iCount || a_iIndex < 0)
				{
					std::cout << "FuzzyList<T>::GetAtIndex:: Index " << a_iIndex << " is out of range\n";
				}
				return *(m_List[a_iIndex]);
			}

	#pragma endregion Getters

	#pragma region operator overloading

			//[] operator to return object at given index of list
			T& operator[](const int& a_iListIndex)
			{
				return GetAtIndex(a_iListIndex);
			}

	#pragma endregion operator overloading

			//Logs the contents of the List
			virtual void DebugLog() override
			{
				std::cout << "\nCount : " << m_iCount << "..... Size :: " << m_iCapacity << "\n";
				T* l_currObjPtr = nullptr;
				for (int l_iListIndex = 0; l_iListIndex < m_iCount; l_iListIndex++)
				{
					l_currObjPtr = m_List[l_iListIndex];
					if (l_currObjPtr != nullptr)
					{
						std::cout << "Index Value::" << *l_currObjPtr << "\n";
					}
				}
			}
	};

}