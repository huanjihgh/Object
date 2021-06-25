#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include <stdint.h>
#include <string>
namespace object {
	template<class K, class V>
	class HashEntry {
	public:
		HashEntry(K key, V value) {
			this->key = key;
			this->value = value;
			this->fNext = NULL;
		}
		/*HashEntry(){

		}

		HashEntry & operator = (const HashEntry & h) {
			this->fNext = this->fNext;
			this->value = this->value;
			this->key = this->key;

			return this;
		}
*/
//~HashEntry(){}
		K key;
		V value;
		HashEntry<K, V>* fNext;
		//~HashEntry(){
		//printf("~HashEntry\n");
		//}
	};

	template<class K, class V>
	class HashTable {
	public:

	private:

		size_t fSize;
		size_t fMask;
		size_t fNumEntries;
		HashEntry<K, V> **fHashTable;
		//ToStringHandler* toString;
		bool ckey(size_t hashValue, K key);
	public:

		

		HashTable(int size);
		~HashTable();

		//virtual	size_t GetHashValue(K key);
		bool Add(K key, V value);

		///
		///不存在就创建一项，否则返回一个null的
		///
		V operator [](const K & key) {
			size_t hashValue = key.GetHashCode(); // GetHashValue(key);
			size_t theIndex = this->ComputeIndex(hashValue);
			HashEntry<K, V>* elem = fHashTable[theIndex];
			while (elem) {
				if (elem->key == key)
				{
					return elem->value;
				}
				elem = elem->fNext;
			}
			HashEntry<K, V> *entry = new HashEntry<K, V>(key, nullptr);
			entry->fNext = fHashTable[theIndex];
			fHashTable[theIndex] = entry;
			fNumEntries++;
			return entry->value;
		}

		bool ContainerKey(K key) {
			//int hashValue = GetHashValue(key);
			size_t hashValue = key.GetHashCode();
			return ckey(hashValue, key);
		}

		HashEntry<K, V>* Get(K key);


		size_t ComputeIndex(int hashKey)
		{
			if (this->fMask)
				return(hashKey & fMask);
			else
				return(hashKey % fSize);
		}
		void RemoveEntries(K key, bool deleted = true);
		size_t GetNumEntries() { return fNumEntries; }

		size_t GetTableSize() { return fSize; }
		HashEntry<K, V>* GetTableEntry(int i) { return fHashTable[i]; }

		void Clear() {
			for (size_t index = 0; index < fSize; index++) {
				HashEntry<K, V> *pEntry = this->GetTableEntry(index);
				HashEntry<K, V> *next = NULL;// pEntry;
				while (pEntry)
				{
					next = pEntry;
					//printf("%d xx\n", ++xx);
					pEntry = pEntry->fNext;
					delete next;
				}
			}
			//delete[] fHashTable;
		}
	};

	template<class K, class V>
	HashTable<K, V>::HashTable(int size) {
		fHashTable = new (HashEntry<K, V>*[size]);
		memset(fHashTable, 0, sizeof(HashEntry<K, V>*) * size);
		fSize = size;

		fMask = fSize - 1;
		if ((fMask & fSize) != 0)
			fMask = 0;
		fNumEntries = 0;
	}
	template<class K, class V>
	HashTable<K, V>::~HashTable()
	{
		//int xx = 0;
		for (size_t index = 0; index < fSize; index++) {
			HashEntry<K, V> *pEntry = this->GetTableEntry(index);
			HashEntry<K, V> *next = NULL;// pEntry;
			while (pEntry)
			{
				next = pEntry;
				//printf("%d xx\n", ++xx);
				pEntry = pEntry->fNext;
				delete next;
			}
		}
		delete[] fHashTable;
		//toString = NULL;
	}


	template<class K, class V>
	bool HashTable<K, V>::Add(K key, V value) {
		size_t hashValue = key.GetHashCode(); // GetHashValue(key);
		size_t theIndex = this->ComputeIndex(hashValue);
		HashEntry<K, V>* elem = fHashTable[theIndex];
		while (elem) {
			if (elem->key == key)
			{
				//delete elem->value;
				//elem->value = value;
				return false;
			}
			elem = elem->fNext;
		}
		HashEntry<K, V> *entry = new HashEntry<K, V>(key, value);
		entry->fNext = fHashTable[theIndex];
		fHashTable[theIndex] = entry;
		fNumEntries++;
		return true;
	}

	

	/* template<class K, class V>
	 size_t HashTable<K, V>::GetHashValue(K key){
		 char* str = this->toString(key);
		 size_t hashValue = DJBHash(str);
		 delete[](char*)str;
		 return hashValue;
	 }*/

	template<class K, class V>
	void HashTable<K, V>::RemoveEntries(K key,bool deleted) {
		//int hashValue = this->GetHashValue(key);
		size_t hashValue = key.GetHashCode();
		hashValue = this->ComputeIndex(hashValue);
		HashEntry<K, V>* elem = fHashTable[hashValue];
		HashEntry<K, V>* last = NULL;
		while (elem && !(elem->key == key)) {
			last = elem;
			elem = elem->fNext;
		}
		if (elem) // sometimes remove is called 2x ( swap, then un register )
		{
			if (last) {
				last->fNext = elem->fNext;
			}
			else
				fHashTable[hashValue] = elem->fNext;
			elem->fNext = NULL;
			if(deleted)
				delete elem;
			--fNumEntries;
		}
	}


	template<class K, class V>
	HashEntry<K, V>* HashTable<K, V>::Get(K key)
	{
		/*char* str = this->toString(key);
		int hashValue = DJBHash(str);
		delete[](char*)str;*/
		size_t hashValue = key.GetHashCode();
		size_t theIndex = ComputeIndex(hashValue);
		HashEntry<K, V>* elem = fHashTable[theIndex];
		while (elem) {
			if (elem->key == key)
				break;
			elem = elem->fNext;
		}
		return elem;
	}

	template<class K, class V>
	bool HashTable<K, V>::ckey(size_t hashValue, K key) {
		size_t theIndex = ComputeIndex(hashValue);
		HashEntry<K, V>* elem = fHashTable[theIndex];
		while (elem) {
			if (elem->key == key)
				return true;
			elem = elem->fNext;
		}
		return false;
	}

	////////////////////////

	template<class K, class V>
	class HashTableIter {
	public:
		HashTableIter(HashTable<K, V>* table)
		{
			fHashTable = table;
			First();
		}
		void First()
		{
			for (fIndex = 0; fIndex < fHashTable->GetTableSize(); fIndex++) {
				fCurrent = fHashTable->GetTableEntry(fIndex);
				if (fCurrent)
					break;
			}
		}
		void Next()
		{
			fCurrent = fCurrent->fNext;
			if (!fCurrent) {
				for (fIndex = fIndex + 1; fIndex < fHashTable->GetTableSize(); fIndex++) {
					fCurrent = fHashTable->GetTableEntry(fIndex);
					if (fCurrent)
						break;
				}
			}
		}
		bool IsDone()
		{
			return(fCurrent != NULL);
		}
		HashEntry<K, V>* GetCurrent() { return fCurrent; }

	private:
		HashTable<K, V>* fHashTable;
		HashEntry<K, V>* fCurrent;
		size_t fIndex;
	};


	template<class K, class V>
	class HashTableShareIter {
	public:
		HashTableShareIter(std::shared_ptr<HashTable<K, V>> table)
		{
			fHashTable = table;
			First();
		}
		void First()
		{
			for (fIndex = 0; fIndex < fHashTable->GetTableSize(); fIndex++) {
				fCurrent = fHashTable->GetTableEntry(fIndex);
				if (fCurrent)
					break;
			}
		}
		void Next()
		{
			fCurrent = fCurrent->fNext;
			if (!fCurrent) {
				for (fIndex = fIndex + 1; fIndex < fHashTable->GetTableSize(); fIndex++) {
					fCurrent = fHashTable->GetTableEntry(fIndex);
					if (fCurrent)
						break;
				}
			}
		}
		bool IsDone()
		{
			return(fCurrent != NULL);
		}
		HashEntry<K, V>* GetCurrent() { return fCurrent; }

	private:
		std::shared_ptr<HashTable<K, V>> fHashTable;
		HashEntry<K, V>* fCurrent;
		size_t fIndex;
	};


}

#endif