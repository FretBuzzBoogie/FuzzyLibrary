#pragma once
#include <iostream>
#include <initializer_list>
#include "..\Base\IFuzzyBase.h"
#include <vector>
#include <array>
#include <cassert>

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
			//Called on creating a list in the constructor.
			void InitList(const std::initializer_list<T>& a_initList)
			{
				int l_initListSize = a_initList.size();
				AllocateMemory(l_initListSize);

				int l_iInializerIndex = 0;
				for (T l_Obj : a_initList)
				{
					*m_List[l_iInializerIndex] = l_Obj;
					l_iInializerIndex++;
				}
				m_iCount = l_initListSize;
			}

			//Conditionally allocates memory to the list
			//If capacity to allocate is less than double current capacity,
			////sets capacity as double the current capacity
			//Else sets the capacity to the arguement.
			void AllocateMemory(const int& a_iCapacity)
			{
				if (a_iCapacity <= m_iCapacity)
				{
					std::cout << "FuzzyList::AllocateMemory:: Allocation of memory is less than already allocated memory.\n";
					return;
				}

				int l_iDoubleCapacity = 2 * m_iCapacity;
				int l_iMemoryToAllocate = a_iCapacity <= l_iDoubleCapacity ? l_iDoubleCapacity : a_iCapacity;
				ResizeList(l_iMemoryToAllocate);
			}


			//Resizes the capacity of the list
			//If list is empty then do not copy contents of list before resize.
			void ResizeList(const int& a_iMemoryToAllocate)
			{
				T** tempList = nullptr;
				bool l_bIsListEmpty = m_List == nullptr;

				if (!l_bIsListEmpty)
				{
					tempList = new T*[m_iCount];
					for (int l_iTempListIndex = 0; l_iTempListIndex < m_iCount; l_iTempListIndex++)
					{
						tempList[l_iTempListIndex] = m_List[l_iTempListIndex];
					}
				}

				delete[] m_List;
				m_List = new T*[a_iMemoryToAllocate];
				m_iCapacity = a_iMemoryToAllocate;

				if (l_bIsListEmpty)
				{
					for (int l_iTempListIndex = 0; l_iTempListIndex < m_iCapacity; l_iTempListIndex++)
					{
						m_List[l_iTempListIndex] = new T();
					}
				}
				else
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

			// Get the variable stored at index by reference.
			T& GetAtIndex(const int& a_iIndex) throw(std::out_of_range)
			{
				try
				{
					CheckForOutOfRange(a_iIndex);
				}
				catch (std::out_of_range& a_Exception)
				{
					throw;
				}
				return *(m_List[a_iIndex]);
			}

			//Checks if index is out of the internal array range
			void CheckForOutOfRange(const int &a_iIndex) throw(std::out_of_range)
			{
				try
				{
					if (a_iIndex >= m_iCount || a_iIndex < 0)
					{
						char* l_Error = "Arguement is out of range of internal FuzzyList.\n";
						throw std::out_of_range(l_Error);
					}
				}
				catch (std::out_of_range& a_Exception)
				{
					throw;
				}
			}

		///PUBLIC SOURCE
		public:

	#pragma region Constructor/Destructor
			
			//Constructor to initialize a list.
			FuzzyList(const std::initializer_list<T>& a_initList)
			{
				InitList(a_initList);
			}

			//Constructor to initialize with input capacity.
			FuzzyList(const int& a_iInitCapacity = DEFAULT_CAPACITY)
			{
				AllocateMemory(a_iInitCapacity);
			}

			//Destructor.
			~FuzzyList()
			{
				for (int l_iListIndex = 0; l_iListIndex < m_iCapacity; l_iListIndex++)
				{
					T*& refListIndex = m_List[l_iListIndex];
					delete refListIndex;
					refListIndex = nullptr;
				}

				delete[] m_List;
				m_List = nullptr;
			}

	#pragma endregion Constructor/Destructor

	#pragma region List Manipulation Functions

			//Adds the object at the end of the List.
			void Add(T& a_Obj)
			{
				AllocateMemory(m_iCount + 1);
				*m_List[m_iCount] = a_Obj;
				m_iCount++;
			}

			//Adds a range of Objects at the end of the list.
			void AddRange(FuzzyList<T>& a_List)
			{
				int l_iCountBeforeAdd = m_iCount;
				int l_iNewCount = m_iCount + a_List.GetCount();

				AllocateMemory(l_iNewCount);
				m_iCount = l_iNewCount;

				for (int l_iCountIndex = 0; (l_iCountIndex + l_iCountBeforeAdd) < m_iCount; l_iCountIndex++)
				{
					*m_List[l_iCountIndex + l_iCountBeforeAdd] = a_List[l_iCountIndex];
				}
			}

			//Clears the contents of the list.
			void Clear()
			{
				m_iCount = EMPTY_LIST_SIZE;
			}

			//Removes the object in the list at index.
			void Remove(const int& a_iRemoveObjAtIndex) throw(std::exception)
			{
				try
				{
					CheckForOutOfRange(a_iRemoveObjAtIndex);
				}
				catch (std::exception& a_Exception)
				{
					std::cerr <<"FuzzyList::Remove:: "<< a_Exception.what();
					return;
				}

				int l_iCountAfterRemoval = m_iCount - 1;
				for (int l_iListIndex = a_iRemoveObjAtIndex; l_iListIndex < l_iCountAfterRemoval; l_iListIndex++)
				{
					*m_List[l_iListIndex] = *m_List[l_iListIndex + 1];
				}
				m_iCount = l_iCountAfterRemoval;
			}

	#pragma endregion List Manipulation Functions

	#pragma region Getters
		
			//Gets the count of the the elements of type T in the internal array.
			const int& GetCount() const
			{
				return m_iCount;
			}
			 
			//Gets the capacity of the internal array with elements of type T.
			const int& GetCapacity() const
			{
				return m_iCapacity;
			}

	#pragma endregion Getters

	#pragma region operator overloading

			//[] operator to return object at given index of list.
			T& operator[](const int& a_iListIndex)
			{
				try
				{
					return GetAtIndex(a_iListIndex);
				}
				catch (std::out_of_range& a_Exception)
				{
					std::cerr << "FuzzyList::GetAtIndex:: "<<a_Exception.what();
				}
			}

	#pragma endregion operator overloading

			//Logs the contents of the List.
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