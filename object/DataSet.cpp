//#include "../include/DataSet.hpp"
//
//namespace object {
//
//	inline bool InsensitivityStringKey::equal(const std::string &str1, const std::string &str2) noexcept {
//		return str1.size() == str2.size() &&
//			std::equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
//			return tolower(a) == tolower(b);
//		});
//	}
//	InsensitivityStringKey::InsensitivityStringKey() {
//		this->value = "";
//	}
//	InsensitivityStringKey::InsensitivityStringKey(const std::string& value) {
//		this->value = value;
//	}
//
//	InsensitivityStringKey::InsensitivityStringKey(const char* value) {
//		this->value = value;
//	}
//
//	bool const InsensitivityStringKey::operator ==(const object::InsensitivityStringKey & x) {
//		return equal(this->value, x.value);
//	}
//
//	const size_t InsensitivityStringKey::GetHashCode() {
//		std::hash<std::string> h;
//		std::string xx = this->value;
//		std::transform(xx.begin(), xx.end(), xx.begin(), toupper);
//		return h(xx);
//	}
//
//	Column::Column() :index(-1), name(""), alias(""), type(DataType::UNKOWN) {  }
//	Column::Column(int16_t index, const std::string& name) : index(index), name(name) {}
//
//	Column::Column(const Column& col) {
//		this->index = col.index;
//		this->name = col.name;
//		this->type = col.type;
//		this->alias = col.alias;
//	}
//
//
//	ColHashKey::ColHashKey(const std::string& key) {
//		this->key = key;
//	}
//
//	ColHashKey::ColHashKey(const ColHashKey& key) {
//		this->key = key.key;
//	}
//
//	ColHashKey& ColHashKey::operator=(const ColHashKey& key) {
//		this->key = key.key;
//		return *this;
//	}
//
//	ColHashKey::ColHashKey() :key("") {
//	}
//
//	const bool ColHashKey::operator ==(const ColHashKey &o) {
//		return (o.key == this->key);
//	}
//
//	/*operator size_t() {
//		return this->key;
//	}*/
//
//	const size_t ColHashKey::GetHashCode() {
//		return std::hash<std::string>{}(key);
//	}
//
//
//
//	Row::Row() :_row(), _cols(nullptr) {
//	}
//
//	Row::Row(Columns *_cols) : _row(), _cols(_cols) {
//	}
//
//	ColValue* Row::Col(int16_t index) {
//		//this->_cols.
//		ColIter iter(_cols);
//		ColValue* v = 0;
//		for (; iter.IsDone(); iter.Next()) {
//			v = iter.GetCurrent();
//			if (v&& v->value.index == index) {
//				return v;
//			}
//		}
//		return v;
//
//	}
//
//	size_t Row::size() {
//		return this->_row.size();
//	}
//
//	std::vector<ObjectPtr>::iterator Row::begin() {
//		return this->_row.begin();
//	}
//
//	std::vector<ObjectPtr>::iterator Row::end() {
//		return this->_row.end();
//	}
//
//	ColValue* Row::Col(const std::string &colName) {
//		//this->_cols.
//		return _cols->Get(object::InsensitivityStringKey(colName));
//	}
//
//	std::shared_ptr<Object> Row::operator [](const std::string &colName) {
//		ColValue * v = _cols->Get(object::InsensitivityStringKey(colName));
//		if (v) {
//			return this->_row[v->value.index];
//		}
//
//		return nullptr;
//	}
//
//	std::shared_ptr<Object> Row::operator [](int16_t index) {
//		return _row[index];
//	}
//
//	void Row::Add(std::shared_ptr<Object> data) {
//		this->_row.push_back(data);
//	}
//
//
//
//
//
//	std::shared_ptr<Columns> DataSet::GetColumns() {
//		return _cols;
//	}
//
//	DataSet::DataSet() :_rows(), _cols(std::make_shared<Columns>(5)) {
//
//	}
//
//	size_t DataSet::GetColumnSize() {
//		return this->_cols->GetNumEntries();
//	}
//
//	// <summary>
//	// author:huangguoheng
//	// email:470136534@qq.com
//	// date:2020-09-14
//	// description:·µ»ØÁÐÖµ
//	// </summary>
//	ColValue*  DataSet::Index(int i) {
//		ColIter iter(_cols.get());
//		ColValue* v = 0;
//		for (; iter.IsDone(); iter.Next()) {
//			v = iter.GetCurrent();
//			if (v&& v->value.index == i) {
//				return v;
//			}
//		}
//		return v;
//	}
//
//	Row& DataSet::operator [](uint16_t row) {
//		return *this->_rows[row].get();
//	}
//
//	std::shared_ptr<Row> DataSet::NewRow() {
//		return std::make_shared<Row>(this->_cols.get());
//	}
//
//	void DataSet::Add(std::shared_ptr<Row> row) {
//		this->_rows.push_back(row);
//	}
//
//	void DataSet::RemoveAt(size_t row) {
//		auto at = this->_rows.begin() + row;
//		this->_rows.erase(at);
//	}
//
//
//	std::vector<std::shared_ptr<Row>>::iterator DataSet::begin() {
//		return this->_rows.begin();
//	}
//
//	std::vector<std::shared_ptr<Row>>::iterator DataSet::end() {
//		return this->_rows.end();
//	}
//	DataType DataSet::getDataType() {
//		return object::DataType::DATASET_H;
//	}
//
//	size_t DataSet::size() {
//		return this->_rows.size();
//	}
//}
