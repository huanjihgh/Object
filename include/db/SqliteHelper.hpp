#ifndef _SQLLIte_Helper_H_
#define _SQLLIte_Helper_H_



#include <string>
#include <functional>
#include <list>
#include "../Object.hpp"
#include <sstream>
#include <algorithm>
#include<vector>
#include"../KeyMap.hpp"
#include"../String.hpp"


namespace database {

	using namespace object;

	typedef int(*Sqlite3_Callback)(void*, int, char**, char**);

	typedef int(__cdecl* Sqlite3_exec)(
		intptr_t,                /* The database on which the SQL executes */
		const char *,             /* The SQL to be executed */
		Sqlite3_Callback,          /* Invoke this callback routine */
		void *,                  /* First argument to xCallback() */
		char **                  /* Write error messages here */
		);


	///这个是用来逆向的函数
	
	class SqliteHelper
	{
		class my_sqlite_field {
		public:
			size_t index;
			std::string name;
			object::DataType type;
		};

		intptr_t db;

		Sqlite3_exec sqlite_exec;

	public:

		SqliteHelper(intptr_t dbhande, intptr_t sqlite3_exec_addr) {
			this->sqlite_exec = (Sqlite3_exec)sqlite3_exec_addr;
			this->db = dbhande;
		}

		static bool equal(const std::string &str1, const std::string &str2) noexcept {
			return str1.size() == str2.size() &&
				std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
				return tolower(a) == tolower(b);
			});
		}

	
		template<class T>
		bool query(Object & model, std::list<T> & data, std::string where = "") {

			std::ostringstream sql;

			this->querySQL(model, model.identify(), sql);

			sql << where;

			return this->query(sql.str(), data);
		}

		template<class T>
		bool find(T& model, std::string where) {

			std::ostringstream sql;

			this->querySQL(model, model.identify(), sql);

			sql << where;
			std::list<T> data;
			bool ok = this->query(sql.str(), data);

			if (ok && data.size() > 0)
				model = *data.begin();

			return ok && data.size() > 0;

		}

		struct temp_1 {
			bool hasRow;
			Array* ds;
		};

	
		//删除数据返回-1失败
		int del(std::string & sql) {

			return this->executeSQL(sql);
		}

		int update(std::string & sql) {
			return this->executeSQL(sql);
		}

	
		int insert(Object &model) {
			std::string sql= this->insertSQL(model, model.identify());
		

			return this->insert(sql);
		}

		int update(Object &model, std::string where = " where 1=2") {
			std::ostringstream ostr;
			this->updateSQL(model, model.identify(), ostr);

			ostr << where;
			std::string sql = ostr.str();

			return this->update(sql);
		}

		int insert(std::string & sql) {

			return this->executeSQL(sql);
		}


		///author:huangguoheng
		///date:2019-01-30
		///执行一条sql语句
		int executeSQL(const std::string& sql) {
			char *zErrMsg = 0;
			if (this->sqlite_exec(this->db, sql.c_str(), NULL, 0, &zErrMsg) != 0) {
				this->errormsg = std::string(zErrMsg);
				return -1;
			}
			return 0;
		}
		template<typename T>
		struct temp_0 {
			std::list<T> *data;
			std::shared_ptr<object::Type> d;
			std::vector<my_sqlite_field> *indexs;
		};
		///author:huangguoheng
		///date:2019-01-30
		///执行一条sql语句
		int executeSQL(const std::string& sql,Sqlite3_Callback callback,void* dataPtr) {
		
			char *zErrMsg = 0;
			if (this->sqlite_exec(this->db, sql.c_str(), callback,dataPtr, &zErrMsg) != 0) {
				if(zErrMsg)
				this->errormsg = std::string(zErrMsg);
				return -1;
			}
			return 0;
		}

		
		bool query(const std::string& sql, std::list<object::KeyMap> & data) {

			std::vector<my_sqlite_field> indexs;

			

			temp_0<object::KeyMap> x;
			x.data = &data;
			x.indexs = &indexs;

			return this->executeSQL(sql,
				[](void *dx, int argc, char** row, char** azColName) {
				if (argc < 1)
					return 1;
			
				temp_0<object::KeyMap> *x = (temp_0<object::KeyMap>*)dx;
				auto data = x->data;
				object::KeyMap km;
				for (int i = 0; i < argc; i++) {
					char* col = azColName[i];
					char *val = row[i];
					if (!val) {
						km.set(col, std::make_shared<object::String>(""));
					}else
						km.set(col, std::make_shared<object::String>(val));
				}

				data->push_back(km);
				return 0;
			}, (void*)&x
				) != -1;

		}


		template<class T>
		bool query(const std::string& sql, std::list<T> & data) {

			std::vector<my_sqlite_field> indexs;

			T t1;
			auto d = t1.getType();

			temp_0<T> x;
			x.d = d;
			x.data = &data;
			x.indexs = &indexs;

			return this->executeSQL(sql,
				[](void *dx, int argc, char** row, char** azColName) {
				if (argc < 1)
					return 1;
				T t;

				temp_0<T> *x = (temp_0<T>*)dx;
				auto d = x->d;
				auto data = x->data;
				auto indexs = x->indexs;
				if (indexs->size() < 1) {

					//获取模型的字段名列表
					auto fields = d->getFieldNames();
					//获取要映射的列名
					for (int i = 0; i < argc; i++) {
						char* col = azColName[i];
						auto b = fields->begin();
						auto e = fields->end();
						for (; b != e; b++) {
							if (equal(*b, col)) {
								my_sqlite_field f;
								/*f.index = i;
								f.field = d->GetField(*b);*/
								f.index = i;
								f.name = *b;
								f.type = d->dateType(*b);
								indexs->push_back(f);
								break;
							}
						}
					}
				}

				//这里开始填充数据
				d->setObject(&t);
				auto b = indexs->begin();
				auto e = indexs->end();

				for (; b != e; b++) {

					switch ((*b).type)
					{
					case DataType::OBool_H:
						d->set(b->name, row[b->index] == nullptr ? (bool)0 : (bool)std::atoi(row[b->index]));

						break;
					case DataType::ODouble_H:
						d->set(b->name, row[b->index] == nullptr ? (double)0 : std::atof(row[b->index]));
						break;
					case DataType::OFloat_H:
						d->set(b->name, row[b->index] == nullptr ? (float)0 : (float)std::atof(row[b->index]));
						break;

					case DataType::OInt8_H:
						d->set(b->name, row[b->index] == nullptr ? (int8_t)0 : (int8_t)std::atoi(row[b->index]));
						break;
					case DataType::OInt16_H:
						d->set(b->name, row[b->index] == nullptr ? (int16_t)0 : (int16_t)std::atoll(row[b->index]));
						break;
					case DataType::OInt32_H:
						d->set(b->name, row[b->index] == nullptr ? (int32_t)0 : (int32_t)std::atoll(row[b->index]));
						break;
					case DataType::OInt64_H:
						d->set(b->name, row[b->index] == nullptr ? (int64_t)0 : (int64_t)std::atoll(row[b->index]));
						break;
					case DataType::OUInt8_H:
						d->set(b->name, row[b->index] == nullptr ? (uint8_t)0 : (uint8_t)std::atoll(row[b->index]));
						break;
					case DataType::OUInt16_H:
						d->set(b->name, row[b->index] == nullptr ? (uint16_t)0 : (uint16_t)std::atoll(row[b->index]));
						break;
					case DataType::OUInt32_H:
						d->set(b->name, row[b->index] == nullptr ? (uint32_t)0 : (uint32_t)std::atoll(row[b->index]));
						break;
					case DataType::OUInt64_H:
						d->set(b->name, row[b->index] == nullptr ? (uint64_t)0 : (uint64_t)std::atoll(row[b->index]));
						break;
					case DataType::OSTRING_H:

						d->set(b->name, row[b->index] == nullptr ? std::string() : std::string(row[b->index]));
						break;
					default:
						break;
					}
				}
				data->push_back(t);
				return 0;
			}, (void*)&x
				) != -1;

		}


		
		int createTable(Object& o) {
			std::ostringstream sql;
			this->createTableSql(o, sql);
			return this->executeSQL(sql.str());
		}

		protected:
		std::string DataToSqlTypeString(DataType type) {
			switch (type)
			{
			case DataType::OBool_H:
				return std::string("bit");
			case DataType::ODouble_H:
			case DataType::OFloat_H:
				return std::string("float");

			case DataType::OInt8_H:
			case DataType::OUInt8_H:

			case DataType::OInt16_H:
			case DataType::OUInt16_H:

			case DataType::OInt32_H:
			case DataType::OUInt32_H:

			case DataType::OInt64_H:
			case DataType::OUInt64_H:

				return std::string("integer");
				break;

			case DataType::OSTRING_H:
				return std::string("text");

			case DataType::OBLOB_H:
				return std::string("BLOB");
			}

			return std::string("text");
		}



		void createTableSql(Object& model, std::ostringstream &sql) {
			sql << "create table if not exists ";
			sql << model.identify();
			sql << "(";
			auto type = model.getType();
			auto fields = type->getFields();

			auto  b = fields->begin();
			auto b1 = b;
			auto e = fields->end();

			for (; b != e; b++) {
				b1++;

				if (b1 == e) {
					sql << b->first << " " << this->DataToSqlTypeString(b->second->type) << ")";
				}
				else {
					sql << b->first << " " << this->DataToSqlTypeString(b->second->type);
					sql << ",";
				}

			}

		}

	
		void sqlValue(object::Type& d, object::Field* field, std::ostringstream & ostr) {
			switch (field->type)
			{
			case DataType::OBool_H:
			{
				bool b;
				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::ODouble_H:

			{
				double b;

				d.get(field->field, b);
				ostr << b;
			}

			break;
			case DataType::OFloat_H:
			{
				float b;

				d.get(field->field, b);
				ostr << b;
			}
			break;

			case DataType::OInt8_H:
			{
				int8_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OInt16_H:
			{
				int16_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OInt32_H:
			{
				int32_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OInt64_H:
			{
				int64_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt8_H:
			{
				uint8_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt16_H:
			{
				uint16_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt32_H:
			{
				uint32_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt64_H:
			{
				uint64_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OSTRING_H:
			{
				std::string b;

				d.get(field->field, b);
				ostr << '\'';
				ostr << b;
				ostr << '\'';
			}
			break;
			default:
				break;
			}
		}


		///author:huangguoheng
		///date:2019-01-30
		///description:created insert sql
		std::string 
		 insertSQL(Object& model, std::string tableName) {
			std::ostringstream sql;

			std::ostringstream sqlEnd;

			sql << "insert into ";
			sql << tableName;
			sql << "(";
			auto type = object::cast<object::Type>( model.getType());
			auto fields = type->getFields();

			auto  b = fields->begin();
			auto b1 = b;
			auto e = fields->end();

			//探测下是否醉后面的字段为id
			e--;
			if (fields->size() > 0 && !equal(e->first, "id")) {
				e++;
			}

			int index = 0;

			std::vector<int16_t> itype;

			for (;b != e;b++,index++) {
				b1++;
				
				if (equal(b->first, "id"))
					continue;
				if (equal(b->first, "_value")) {
					continue;
				}
			

				if (b1 == e) {
					sql << b->first;
					sql << ") values(";

					this->sqlValue(*type, b->second, sqlEnd);
					sqlEnd << ")";

				}
				else {
					sql << b->first;
					sql << ",";
					this->sqlValue(*type, b->second, sqlEnd);
					sqlEnd << ",";
				}

			}


			sql << sqlEnd.str();

			return sql.str();
		}



		void updateSQL(Object& model, std::string tableName, std::ostringstream& sql) {

			sql << "update ";
			sql << tableName;
			sql << " set ";
			auto type = object::cast<object::Type>(model.getType());
			auto fields = type->getFields();

			auto  b = fields->begin();
			auto b1 = b;
			auto e = fields->end();

			//探测下是否醉后面的字段为id
			e--;
			if (fields->size() > 0 && !equal(e->first, "id")) {
				e++;
			}
			for (;b != e;b++) {
				b1++;
				if (equal(b->first, "id"))
					continue;
				if (equal(b->first, "_value")) {
					continue;
				}
				if (b1 == e) {
					sql << b->first;
					sql << "=";

					this->sqlValue(*type, b->second, sql);

				}
				else {
					sql << b->first;
					sql << "=";
					this->sqlValue(*type, b->second, sql);
					sql << ",";
				}

			}
		}

		void querySQL(Object& model, std::string tableName, std::ostringstream& sql) {

			sql << "select ";
			auto type = model.getType();
			auto fields = type->getFields();

			auto  b = fields->begin();
			auto b1 = b;
			auto e = fields->end();

			for (;b != e;b++) {
				b1++;
				if (equal(b->first, "_value")) {
					continue;
				}

				if (b1 == e) {
					sql << b->first;

				}
				else {
					sql << b->first;
					sql << ",";
				}

			}

			sql << " from ";
			sql << tableName;
		}



	private:

		std::string errormsg;

	};




	//static void excuteSql(int32_t handle,int32_t sqlite3_exec_fn, std::string sql, sqlite3_callback cb= nullptr,void* data=nullptr) {
	//	Sqlite3_exec p_Sqlite3_exec = (Sqlite3_exec)sqlite3_exec_fn;
	//	char *zErrMsg = 0;
	//
	//	if (SQLITE_OK != p_Sqlite3_exec(handle, sql.c_str(), cb, data, &zErrMsg)) {
	//		object::Util::log("F:\\error_hgh.log", zErrMsg);
	//		return;
	//	}

	//}


	
}
#endif