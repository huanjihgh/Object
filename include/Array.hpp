#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "Object.hpp"
#include <vector>
#include "KeyMap.hpp"
#include "String.hpp"
namespace object {
	typedef std::vector<std::shared_ptr<object::Object>>  Array_List;
	/**
	**	author:huangguoheng
	**	date:2019-03-11
	**	对象数组
	**/
	class HLIB_API 	
		 Array :public object::Object {
		private:
			std::shared_ptr<Array_List> _array;
			std::function<std::shared_ptr<object::Object>()> _new;
		public:
			Array();
			Array(std::list<object::KeyMap> &data);

			Array(std::function<std::shared_ptr<object::Object>()> _new);
			std::shared_ptr<object::Object> createItem();

			Array(const Array& a);

			const Array & operator=(const Array &a);

			const std::shared_ptr<object::Object> operator[](const size_t& index);

			virtual std::string identify() const;

			virtual DataType getDataType();
			virtual std::string toString();

			void push(std::shared_ptr<object::Object> val);

			template<typename T>
			void push(std::list<T> vals);

			void push(const std::string & val);
			const size_t  size();
	

			void clear();
			const object::Array_List::iterator begin();

			const object::Array_List::iterator end();
	};


}
#endif // _OBJECT_H_
