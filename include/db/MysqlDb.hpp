#ifndef _MYSQLDB_H_
#define _MYSQLDB_H_

#ifdef _WIN32
#include <winsock.h>
#endif // Win32


#include <mysql.h>
#include <string>
#include <functional>
#include <list>
#include "../Object.hpp"
#include "../StrTool.hpp"
#include <sstream>
#include"../WString.hpp"
#include"../String.hpp"
#include "../Bool.hpp"
#include "../Int8.hpp"
#include "../Int16.hpp"
#include "../Int32.hpp"
#include "../Int64.hpp"
#include "../UInt8.hpp"
#include "../UInt16.hpp"
#include "../UInt32.hpp"
#include "../UInt64.hpp"
#include "../Float.hpp"
#include "../Double.hpp"
#include "../KeyMap.hpp"

using namespace object;
namespace database {
	class MysqlDb
	{
		class my_field {
		public:
			size_t index;
			std::string name;
			object::DataType type;
			Field *field;
		};
		inline bool equal(const std::string &str1, const std::string &str2) noexcept {
			return str1.size() == str2.size() &&
				std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
				return tolower(a) == tolower(b);
			});
		}
	public:
		

		//inline bool equal(const std::string str1, const std::string str2) noexcept {
		//	return str1.size() == str2.size() &&
		//		std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
		//		return tolower(a) == tolower(b);
		//	});
		//}


		MysqlDb(
			std::string host,
			std::string user,
			std::string passwd,
			std::string db,
			unsigned int port = 3306,
			std::string utf8 = "utf8"
		) :host(host), user(user), passwd(passwd), db(db), port(port),
			encode(utf8) {
			mysql_init(&mysql);                          //连接之前必须使用这个函数来初始化
			autoCommit = true;
		}
		~MysqlDb() {
			if (this->sock) {
				mysql_close(sock);
			}
		}
		std::string error_msg() {
			return std::string(mysql_error(&mysql));
		}

		bool open() {
			sock = mysql_real_connect(&mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, unix_socket, client_flag);

			if (!sock) {

				return false;
			}

			return true;
		}

		template<class T>
		bool query(std::string sql, std::list<T> & data,std::string encoding="") {
			auto query = "SET CHARACTER SET " + (encoding.empty()?encode:encoding); //设置编码
			auto txx = mysql_query(&mysql, query.c_str());

			if (txx)

			{
				return false;

			}
			if (mysql_query(&mysql, sql.c_str()) != 0) {
				return false;
			}



			MYSQL_RES * result = mysql_store_result(&mysql); //保存查询的结果

			if (result == nullptr) {

				return false;
			}

			T t;
			auto d =object::cast< object::Type>( t.getType());

			std::list<my_field> indexs;
			{
				MYSQL_FIELD* cc = mysql_fetch_fields(result);
				int num_fields = mysql_num_fields(result);


				//获取模型的字段名列表
				//auto fields = d->getFieldNames();
				auto fields = d->getFields();
				///标志字段在数据表中的位置

				for (size_t i = 0; i < num_fields; i++) {
					/*if(this->equal())
					indexs.push_back(i);*/
					auto b = fields->begin();
					auto e = fields->end();
					for (; b != e; b++) {
						if (this->equal(b->first, cc[i].name)) {
							my_field f;
							f.index = i;
							f.name = b->first;
							f.field = b->second;
							f.type = d->dateType(b->first);
							indexs.push_back(f);
							break;
						}
					}
				}

				//mysql_field
			}
			try {
				MYSQL_ROW row;
				while ((row = mysql_fetch_row(result)) != nullptr) //读取结果集中的数据，返回的是下一行。因为保存结果集时，当前的游标在第一行【之前】
				{
					//printf("name is %s\t", row[0]);               //打印当前行的第一列的数据
					//printf("age is %s\t\n", row[1]);              //打印当前行的第二列的数据
					T t1;
					//d=t1.getType();
					d->setObject(&t1);
					auto b = indexs.begin();
					auto e = indexs.end();

					for (; b != e; b++) {

						switch ((*b).type)
						{
						case DataType::Bool_H:
							d->set(b->field, row[b->index] == nullptr ? (bool)0 : (bool)std::atoi(row[b->index]));
							break;
						case DataType::Double_H:
							d->set(b->field, row[b->index] == nullptr ? (double)0 : std::atof(row[b->index]));
							break;
						case DataType::Float_H:
							d->set(b->field, row[b->index] == nullptr ? (float)0 : (float)std::atof(row[b->index]));
							break;

						case DataType::Int8_H:
							d->set(b->field, row[b->index] == nullptr ? (int8_t)0 : (int8_t)std::atoi(row[b->index]));
							break;
						case DataType::Int16_H:
							d->set(b->field, row[b->index] == nullptr ? (int16_t)0 : (int16_t)std::atoll(row[b->index]));
							break;
						case DataType::Int32_H:
							d->set(b->field, row[b->index] == nullptr ? (int32_t)0 : (int32_t)std::atoll(row[b->index]));
							break;
						case DataType::Int64_H:
							d->set(b->field, row[b->index] == nullptr ? (int64_t)0 : (int64_t)std::atoll(row[b->index]));
							break;
						case DataType::UInt8_H:
							d->set(b->field, row[b->index] == nullptr ? (uint8_t)0 : (uint8_t)std::atoll(row[b->index]));
							break;
						case DataType::UInt16_H:
							d->set(b->field, row[b->index] == nullptr ? (uint16_t)0 : (uint16_t)std::atoll(row[b->index]));
							break;
						case DataType::UInt32_H:
							d->set(b->field, row[b->index] == nullptr ? (uint32_t)0 : (uint32_t)std::atoll(row[b->index]));
							break;
						case DataType::UInt64_H:
							d->set(b->field, row[b->index] == nullptr ? (uint64_t)0 : (uint64_t)std::atoll(row[b->index]));
							break;
						case DataType::STRING_H:
							d->set(b->field, row[b->index] == nullptr ? std::string() : std::string(row[b->index]));
							break;
						case DataType::WSTRING_H:
							d->set(b->field, row[b->index] == nullptr ? std::string() : std::string(row[b->index]));
							break;

							///////////////////////////
						case DataType::OBool_H:
							d->set(b->field, row[b->index] == nullptr ? (Bool)0 : (Bool)std::atoi(row[b->index]));
							break;
						case DataType::ODouble_H:
							d->set(b->field, row[b->index] == nullptr ? (Double)0 : (Double)std::atof(row[b->index]));
							break;
						case DataType::OFloat_H:
							d->set(b->field, row[b->index] == nullptr ? (Float)0 : (Float)std::atof(row[b->index]));
							break;

						case DataType::OInt8_H:
							d->set(b->field, row[b->index] == nullptr ? (Int8)0 : (Int8)std::atoi(row[b->index]));
							break;
						case DataType::OInt16_H:
							d->set(b->field, row[b->index] == nullptr ? (Int16)0 : (Int16)std::atoll(row[b->index]));
							break;
						case DataType::OInt32_H:
							d->set(b->field, row[b->index] == nullptr ? (Int32)0 : (Int32)std::atoll(row[b->index]));
							break;
						case DataType::OInt64_H:
							d->set(b->field, row[b->index] == nullptr ? (Int64)0 : (Int64)std::atoll(row[b->index]));
							break;
						case DataType::OUInt8_H:
							d->set(b->field, row[b->index] == nullptr ? (UInt8)0 : (UInt8)std::atoll(row[b->index]));
							break;
						case DataType::OUInt16_H:
							d->set(b->field, row[b->index] == nullptr ? (UInt16)0 : (UInt16)std::atoll(row[b->index]));
							break;
						case DataType::OUInt32_H:
							d->set(b->field, row[b->index] == nullptr ? (UInt32)0 : (UInt32)std::atoll(row[b->index]));
							break;
						case DataType::OUInt64_H:
							d->set(b->field, row[b->index] == nullptr ? (UInt64)0 : (UInt64)std::atoll(row[b->index]));
							break;
						case DataType::OSTRING_H:
							d->set(b->field, row[b->index] == nullptr ? String() : String(row[b->index]));
							break;
						case DataType::OWSTRING_H:
							if (row[b->index]) {
								auto w=	StrTool::UTF82Wide(row[b->index]);
								d->set(b->field,object::WString(w));
							}
							else {
								d->set(b->field, object::WString());
							}
							break;
						default:
							break;
						}
					}
					data.push_back(t1);
				}

				mysql_free_result(result);
			}
			catch (std::exception e) {
				mysql_free_result(result);
				return false;
			}
			return true;
		}


		bool query(std::list<object::KeyMap> & data, std::string sql, std::string encoding = "") {
			auto query = "SET CHARACTER SET " + (encoding.empty() ? encode : encoding); //设置编码
			auto txx = mysql_query(&mysql, query.c_str());

			if (txx)
			{
				return false;
			}

			if (mysql_query(&mysql, sql.c_str()) != 0) {
				return false;
			}

			MYSQL_RES * result = mysql_store_result(&mysql); //保存查询的结果

			if (result == nullptr) {

				return false;
			}

			//多少列
			int num_fields = mysql_num_fields(result);
		
			MYSQL_FIELD* cc = mysql_fetch_fields(result);
			try {
				MYSQL_ROW row;
				while ((row = mysql_fetch_row(result)) != nullptr) //读取结果集中的数据，返回的是下一行。因为保存结果集时，当前的游标在第一行【之前】
				{

					object::KeyMap mp;

					//printf("name is %s\t", row[0]);               //打印当前行的第一列的数据
					//printf("age is %s\t\n", row[1]);              //打印当前行的第二列的数据
					for (int col = 0; col < num_fields; col++) {

						if (row[col]) {
							mp.set(cc[col].name, std::make_shared<String>(row[col]));
						}
						else {
							mp.set(cc[col].name, std::make_shared<String>(""));
						}
					}

					data.push_back(mp);
				}


				mysql_free_result(result);
			}
			catch (std::exception e) {
				mysql_free_result(result);
				return false;
			}
			return true;
		}

		template<class T>
		bool query(Object & model, std::list<T> & data, std::string where = "",std::string encoding="") {

			std::ostringstream sql;

			this->querySQL(model, model.identify(), sql);

			sql << where;

			return this->query(sql.str(), data,encoding);
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

		int del(std::string & sql) {
			return this->executeSQL(sql);
		}

		int update(std::string & sql) {
			return this->executeSQL(sql);
		}

		void commit() {
			mysql_commit(&this->mysql);
			mysql_autocommit(&mysql, true);
		}

		void begin() {
			mysql_autocommit(&mysql, false);
		}

		void rollback() {
			mysql_rollback(&mysql);
			mysql_autocommit(&mysql, true);
		}

		int insert(Object &model) {
			std::string sql = this->insertSQL(model, model.identify());

			//object::Util::log("F:\\222.log", sql);
			return this->insert(sql);
		}

		int64_t getId() {
			return mysql_insert_id(this->sock);
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

			if (!this->setCharset()) {
				return -1;
			}

			if (mysql_query(&mysql, sql.c_str()) != 0) {
				return -1;
			}
			
			return mysql_affected_rows(&mysql);
		}


		void query(std::string sql, std::function<void(MYSQL_ROW)> each_rows, std::function<void(std::string msg)> failCb = nullptr) {
			if (mysql_query(&mysql, sql.c_str()) != 0) {
				if (failCb) {
					failCb(this->error_msg());
				}
				return;
			}

			MYSQL_RES * result = mysql_store_result(&mysql); //保存查询的结果
			if (result == nullptr) {
				failCb(this->error_msg());

				return;
			}

			MYSQL_ROW row;
			if (each_rows)
				while ((row = mysql_fetch_row(result)) != nullptr) //读取结果集中的数据，返回的是下一行。因为保存结果集时，当前的游标在第一行【之前】
				{
					//printf("name is %s\t", row[0]);               //打印当前行的第一列的数据
					//printf("age is %s\t\n", row[1]);              //打印当前行的第二列的数据
					each_rows(row);
				}

			//mysql_fetch_row()
		}

	protected:
		void sqlValue(object::Type& d, object::Field* field, std::ostringstream & ostr) {
			switch (field->type)
			{
			case DataType::Bool_H:
			{
				bool b;
				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::Double_H:

			{
				double b;

				d.get(field->field, b);
				ostr << b;
			}

			break;
			case DataType::Float_H:
			{
				float b;

				d.get(field->field, b);
				ostr << b;
			}
			break;

			case DataType::Int8_H:
			{
				int8_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::Int16_H:
			{
				int16_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::Int32_H:
			{
				int32_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::Int64_H:
			{
				int64_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::UInt8_H:
			{
				uint8_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::UInt16_H:
			{
				uint16_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::UInt32_H:
			{
				uint32_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::UInt64_H:
			{
				uint64_t b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::STRING_H:
			{
				std::string b;

				d.get(field->field, b);
				ostr << '\'';
				ostr << b;				
				ostr << '\'';
			}
			break;
			case DataType::WSTRING_H:
			{
				std::wstring b;

				d.get(field->field, b);
				ostr << '\'';
				ostr << StrTool::Wide2UTF8( b);
				ostr << '\'';
			}
			break;
			case DataType::WCHARPTR_H:
			{
				wchar_t* b;

				d.get(field->field, b);
				ostr << '\'';
				ostr << StrTool::Wide2UTF8(b);
				ostr << '\'';
			}
			break;
			case DataType::CHARPTR_H:
			{
				char* b;

				d.get(field->field, b);
				ostr << '\'';
				ostr << b;
				ostr << '\'';
			}
			break;
			//////////////////////////
			case DataType::OBool_H:
			{
				object::Bool b;
				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::ODouble_H:

			{
				Double b;

				d.get(field->field, b);
				ostr << b;
			}

			break;
			case DataType::OFloat_H:
			{
				Float b;

				d.get(field->field, b);
				ostr << b;
			}
			break;

			case DataType::OInt8_H:
			{
				Int8 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OInt16_H:
			{
				Int16 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OInt32_H:
			{
				Int32 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OInt64_H:
			{
				Int64 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt8_H:
			{
				UInt8 b;
				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt16_H:
			{
				UInt16 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt32_H:
			{
				UInt32 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OUInt64_H:
			{
				UInt64 b;

				d.get(field->field, b);
				ostr << b;
			}
			break;
			case DataType::OSTRING_H:
			{
				String b;

				d.get(field->field, b);
				ostr << '\'';
				ostr << b.toString();
				ostr << '\'';
			}
			break;
			case DataType::OWSTRING_H:
			{
				WString b;
				d.get(field->field, b);
				ostr << '\'';
				ostr << b.toString();
				ostr << '\'';
			}
			break;
			default:
				break;
			}
		}


		///
		///author:huangguoheng
		///date:2019-01-30
		///description:created insert sql
		std::string insertSQL(Object& model, std::string tableName) {
			std::ostringstream sql;

			std::ostringstream sqlEnd;

			sql << "insert into ";
			sql << tableName;
			sql << "(";
			auto type =object::cast<object::Type>( model.getType());
			auto fields = type->getFields();

			auto  b = fields->begin();
			auto b1 = b;
			auto e = fields->end();

			//探测下是否醉后面的字段为id
			e--;
			if (fields->size() > 0 && !equal(e->first, "id")) {
				e++;
			}

			for (; b != e; b++) {
				b1++;

				if (equal(b->first, "id"))
					continue;
				if (equal(b->first, "_value")) {
					continue;
				}

				if (b1 == e) {
					sql<<"`" << b->first;
					sql << "`) values(";

					this->sqlValue(*type, b->second, sqlEnd);
					sqlEnd << ")";

				}
				else {
					sql <<"`"<< b->first;
					sql << "`,";
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
			for (; b != e; b++) {
				b1++;
				if (equal(b->first, "id"))
					continue;
				if (equal(b->first, "_value")) {
					continue;
				}
				if (b1 == e) {
					sql <<"`"<< b->first;
					sql << "`=";

					this->sqlValue(*type, b->second, sql);

				}
				else {
					sql <<"`"<< b->first;
					sql << "`=";
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

			for (; b != e; b++) {
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

		bool setCharset() {
			auto query = "SET  names " + this->encode; //设置编码
			auto txx = mysql_query(&mysql, query.c_str());
			return !txx;
		}

	private:
		MYSQL mysql, *sock;   //声明MySQL的句柄
		std::string host;  //因为是作为本机测试，所以填写的是本地IP
		std::string user;       //这里改为你的用户名，即连接MySQL的用户名
		std::string passwd; //这里改为你的用户密码
		std::string db;      //这里改为你要连接的数据库的名字
		unsigned int port = 3306;           //这是MySQL的服务器的端口，如果你没有修改过的话就是3306。
		const char * unix_socket = NULL;    //unix_socket这是unix下的，我在Windows下，所以就把它设置为NULL
		unsigned long client_flag = 0;      //

		std::string encode;

		bool autoCommit;

	};

}
#endif