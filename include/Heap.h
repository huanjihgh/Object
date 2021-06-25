#ifndef __HEAP_H__
#define __HEAP_H__
#include<functional>
#include "Object.hpp"
namespace object {
	/****
	*
	*堆栈的实现
	*(std::function<bool(T&, T&)>)
	*CompareHandler 比较器函数返回true，就是大堆排序
	*返回false是小堆排序
	*/
	//namespace mylib{
	template<class T>
	class HLIB_API Heap
	{
	public:
		using CMP = std::function<bool(T&, T&)>;
		Heap(int capacity, CMP cmp) {
			this->heap = new T[capacity];
			this->capacity = capacity;
			this->size = 0;
			this->cmp = cmp;
		}
		Heap(CMP cmp) {
			this->heap = new T[_capacity];
			this->capacity = _capacity;
			this->size = 0;
			this->cmp = cmp;
		}
		~Heap() {
			delete[]heap;
		}
		void addEl(T el) {
			if (cmp == 0) {
				return;
			}
			if (this->size + 1 >= this->capacity) {
				this->capacity <<= 1;
				T *temp = new T[this->capacity];
				//std::memcpy(temp, this->heap, sizeof(T)*size); //这里拷贝只能指针会出错
				std::memset(temp, 0, sizeof(T)*this->capacity);
				for (size_t i = 0; i < size; i++)
				{
					temp[i] = this->heap[i];
				}

				delete[]this->heap;
				this->heap = temp;
			}
			this->heap[this->size] = el;
			this->size++;
			int index = this->size;
			while (index > 1) {
				int temIndex = index >> 1;
				if (!this->cmp(this->heap[temIndex - 1], el)) {
					this->heap[index - 1] = this->heap[temIndex - 1];
					this->heap[temIndex - 1] = el;
				}
				else {//2 13 12 50 99 88 44 
					break;
				}
				index = temIndex;
			}
		}
		T removeAt(int index) {

			T result;
			std::memset(&result, 0, sizeof(T));

			if (this->size <= index) {
				return result;
			}

			if (this->size < 1)
				return result;

			result = this->heap[index];
			this->size--;
			this->heap[index] = this->heap[this->size];
			T temp;
			while (index * 2 + 2 < this->size) {

				if (this->cmp(this->heap[index * 2 + 1], this->heap[index * 2 + 2])) {
					if (this->cmp(this->heap[index * 2 + 1], this->heap[index])) {
						temp = this->heap[index];
						this->heap[index] = this->heap[index * 2 + 1];
						this->heap[index * 2 + 1] = temp;
						index = index * 2 + 1;
					}
					else {
						break;
					}
				}
				else {
					if (this->cmp(this->heap[index * 2 + 2], this->heap[index])) {
						temp = this->heap[index];
						this->heap[index] = this->heap[index * 2 + 2];
						this->heap[index * 2 + 2] = temp;
						index = index * 2 + 2;
					}
					else {
						break;
					}
				}
			}
			if (this->size % 2 == 0) {
				if (index * 2 + 2 == this->size) {
					if (this->cmp(this->heap[index * 2 + 1], this->heap[index])) {
						temp = this->heap[index];
						this->heap[index] = this->heap[index * 2 + 1];
						this->heap[index * 2 + 1] = temp;
					}
				}
			}
			return result;
		} 
		bool removeEl(T el) {
			if (this->size < 1)
				return false;
			size_t k = 0;
			for (; k < this->size; k++) {
				if (el == this->heap[k]) {
					this->removeAt(k);
					return true;
				}
			}

			return false;
		}
		T peekEl(int index) {
			if (this->size > index)
				return this->heap[index];
			T result;
			std::memset(&result, 0, sizeof(T));
			return result;
		}
		int Size() {
			return this->size;
		}
	private:

		enum
		{
			_capacity = 30
		};
		int capacity;
		int size;
		T *heap;
		CMP cmp;
	};
	

}

#endif