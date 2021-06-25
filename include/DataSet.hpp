//#ifndef _DATASET_H
//#define _DATASET_H
//#include "Object.hpp"
//#include <string>
//#include <vector>
//
//namespace object {
//
//	class  InsensitivityStringKey {
//		inline bool equal(const std::string &str1, const std::string &str2) noexcept;
//	public:
//		std::string value;
//		InsensitivityStringKey();
//		InsensitivityStringKey(const std::string& value);
//
//		InsensitivityStringKey(const char* value);
//
//		virtual bool const operator ==(const object::InsensitivityStringKey & x);
//
//		const size_t GetHashCode();
//
//	};
//
//
//	class HLIB_API Column {
//	public:
//		int16_t index;
//		std::string name;
//		DataType type;
//		std::string alias;
//	public:
//		Column();
//		Column(int16_t index, const std::string& name);
//
//		Column(const Column& col);
//	};
//
//
//
//
//	class HLIB_API ColHashKey {
//	public:
//		std::string key;
//
//		ColHashKey(const std::string& key);
//
//		ColHashKey(const ColHashKey& key);
//
//		ColHashKey& operator=(const ColHashKey& key);
//
//		ColHashKey();
//
//		const bool operator ==(const ColHashKey &o);
//
//		const size_t GetHashCode();
//
//	};
//
//	typedef HashTable<object::InsensitivityStringKey, Column> Columns;
//	typedef HashTable<object::Int32, Column> ColumnsInt;
//	typedef HashEntry<object::InsensitivityStringKey, Column> ColValue;
//	typedef HashTableIter<InsensitivityStringKey, Column> ColIter;
//
//	class HLIB_API Row {
//		std::vector< std::shared_ptr<Object>> _row;
//		Columns *_cols;
//		ColumnsInt * _colsInt;
//	public:
//		Row();
//
//		Row(Columns *_cols);
//
//		ColValue* Col(int16_t index);
//
//		size_t size();
//		std::vector<ObjectPtr>::iterator begin();
//		std::vector<ObjectPtr>::iterator end();
//
//		ColValue* Col(const std::string &colName);
//
//		std::shared_ptr<Object> operator [](const std::string &colName);
//
//		std::shared_ptr<Object> operator [](int16_t index);
//
//		void Add(std::shared_ptr<Object> data);
//
//
//	};
//
//
//
//
//	class HLIB_API DataSet :public Object {
//		std::shared_ptr<Columns> _cols;
//		std::vector<std::shared_ptr<Row>> _rows;
//	public:
//
//		std::shared_ptr<Columns> GetColumns();
//
//		DataSet();
//
//		size_t GetColumnSize();
//
//		// <summary>
//		// author:huangguoheng
//		// email:470136534@qq.com
//		// date:2020-09-14
//		// description:·µ»ØÁÐÖµ
//		// </summary>
//		ColValue*  Index(int i);
//
//		Row& operator [](uint16_t row);
//
//		std::shared_ptr<Row> NewRow();
//		void Add(std::shared_ptr<Row> row);
//
//		void RemoveAt(size_t row);
//
//
//		std::vector<std::shared_ptr<Row>>::iterator begin();
//
//		std::vector<std::shared_ptr<Row>>::iterator end();
//		virtual DataType getDataType();
//
//		size_t size();
//		/*{
//		columns:[
//
//			],
//			datas : [
//
//			]
//		}*/
//	};
//
//}
//#endif // _OBJECT_H_
