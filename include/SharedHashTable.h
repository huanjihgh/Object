#ifndef __SHARED_SharedHashTable_H__
#define __SHARED_SharedHashTable_H__
#include <stdint.h>
namespace object {
	template<class K, class V>
	class SharedHashEntry {
	public:
		SharedHashEntry(K key, V value) {
			this->key = key;
			this->value = value;
			this->fNext = NULL;
		}
		/*SharedHashEntry(){

		}

		SharedHashEntry & operator = (const SharedHashEntry & h) {
			this->fNext = this->fNext;
			this->value = this->value;
			this->key = this->key;

			return this;
		}
*/
//~SharedHashEntry(){}
		K key;
		V value;
		SharedHashEntry<K, V>* fNext;
		//~SharedHashEntry(){
		//printf("~SharedHashEntry\n");
		//}
	};

	template<class K, class V>
	class SharedHashTable {
	private:

		size_t fSize;
		size_t fMask;
		size_t fNumEntries;
		SharedHashEntry<K, V> **fSharedHashTable;
		//ToStringHandler* toString;
		bool ckey(size_t hashValue, K key);

		void AllocatMem(size_t size) {
			fSharedHashTable = new (SharedHashEntry<K, V>*[size]);
			memset(fSharedHashTable, 0, sizeof(SharedHashEntry<K, V>*) * size);
			fSize = size;

			fMask = fSize - 1;
			if ((fMask & fSize) != 0)
				fMask = 0;
			fNumEntries = 0;
		}

	public:

		

		SharedHashTable(int size);
		~SharedHashTable();

		//virtual	size_t GetHashValue(K key);
		bool Add(K key, V value);

		///
		///不存在就创建一项，否则返回一个null的
		///
		V operator [](const K & key) {
			size_t hashValue = key->GetHashCode(); // GetHashValue(key);
			size_t theIndex = this->ComputeIndex(hashValue);
			SharedHashEntry<K, V>* elem = fSharedHashTable[theIndex];
			while (elem) {
				if (*elem->key == *key)
				{
					return elem->value;
				}
				elem = elem->fNext;
			}
			SharedHashEntry<K, V> *entry = new SharedHashEntry<K, V>(key, nullptr);
			entry->fNext = fSharedHashTable[theIndex];
			fSharedHashTable[theIndex] = entry;
			fNumEntries++;
			return entry->value;
		}

		bool ContainerKey(K key) {
			//int hashValue = GetHashValue(key);
			size_t hashValue = key.GetHashCode();
			return ckey(hashValue, key);
		}

		SharedHashEntry<K, V>* Get(K key);


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
		SharedHashEntry<K, V>* GetTableEntry(int i) { return fSharedHashTable[i]; }

		void Clear() {
			for (size_t index = 0; index < fSize; index++) {
				SharedHashEntry<K, V> *pEntry = this->GetTableEntry(index);
				SharedHashEntry<K, V> *next = NULL;// pEntry;
				while (pEntry)
				{
					next = pEntry;
					//printf("%d xx\n", ++xx);
					pEntry = pEntry->fNext;
					delete next;
					//next = nullptr;
					
				}
			}

			//this->fSize = 0;
			//this->fSharedHashTable = 0;
			this->fNumEntries = 0;

			delete[] fSharedHashTable;

			this->AllocatMem(this->fSize);

		}
	};

	template<class K, class V>
	SharedHashTable<K, V>::SharedHashTable(int size) {
	/*	fSharedHashTable = new (SharedHashEntry<K, V>*[size]);
		memset(fSharedHashTable, 0, sizeof(SharedHashEntry<K, V>*) * size);
		fSize = size;

		fMask = fSize - 1;
		if ((fMask & fSize) != 0)
			fMask = 0;
		fNumEntries = 0;*/
		this->AllocatMem(size);
	}
	template<class K, class V>
	SharedHashTable<K, V>::~SharedHashTable()
	{
		//int xx = 0;
		for (size_t index = 0; index < fSize; index++) {
			SharedHashEntry<K, V> *pEntry = this->GetTableEntry(index);
			SharedHashEntry<K, V> *next = NULL;// pEntry;
			while (pEntry)
			{
				next = pEntry;
				pEntry = pEntry->fNext;
				delete next;
			}
		}
		delete[] fSharedHashTable;
		//toString = NULL;
	}


	template<class K, class V>
	bool SharedHashTable<K, V>::Add(K key, V value) {
		size_t hashValue = key->GetHashCode(); // GetHashValue(key);
		size_t theIndex = this->ComputeIndex(hashValue);
		SharedHashEntry<K, V>* elem = fSharedHashTable[theIndex];
		while (elem) {
			if (*elem->key.get() == *key.get())
			{
				//delete elem->value;
				elem->value = value;
				return true;
			}
			elem = elem->fNext;
		}
		SharedHashEntry<K, V> *entry = new SharedHashEntry<K, V>(key, value);
		entry->fNext = fSharedHashTable[theIndex];
		fSharedHashTable[theIndex] = entry;
		fNumEntries++;
		return true;
	}

	

	/* template<class K, class V>
	 size_t SharedHashTable<K, V>::GetHashValue(K key){
		 char* str = this->toString(key);
		 size_t hashValue = DJBHash(str);
		 delete[](char*)str;
		 return hashValue;
	 }*/

	template<class K, class V>
	void SharedHashTable<K, V>::RemoveEntries(K key,bool deleted) {
		//int hashValue = this->GetHashValue(key);
		size_t hashValue = key->GetHashCode();
		hashValue = this->ComputeIndex(hashValue);
		SharedHashEntry<K, V>* elem = fSharedHashTable[hashValue];
		SharedHashEntry<K, V>* last = NULL;
		while (elem && !(*elem->key == *key)) {
			last = elem;
			elem = elem->fNext;
		}
		if (elem) // sometimes remove is called 2x ( swap, then un register )
		{
			if (last) {
				last->fNext = elem->fNext;
			}
			else
				fSharedHashTable[hashValue] = elem->fNext;
			elem->fNext = NULL;
			if(deleted)
				delete elem;
			--fNumEntries;
		}
	}


	template<class K, class V>
	SharedHashEntry<K, V>* SharedHashTable<K, V>::Get(K key)
	{
		/*char* str = this->toString(key);
		int hashValue = DJBHash(str);
		delete[](char*)str;*/
		size_t hashValue = key->GetHashCode();
		size_t theIndex = ComputeIndex(hashValue);
		SharedHashEntry<K, V>* elem = fSharedHashTable[theIndex];
		while (elem) {
			if (*elem->key == *key)
				break;
			elem = elem->fNext;
		}
		return elem;
	}

	template<class K, class V>
	bool SharedHashTable<K, V>::ckey(size_t hashValue, K key) {
		size_t theIndex = ComputeIndex(hashValue);
		SharedHashEntry<K, V>* elem = fSharedHashTable[theIndex];
		while (elem) {
			if (*elem->key == *key)
				return true;
			elem = elem->fNext;
		}
		return false;
	}

	////////////////////////

	template<class K, class V>
	class SharedHashTableIter {
	public:
		SharedHashTableIter(SharedHashTable<K, V>* table)
		{
			fSharedHashTable = table;
			First();
		}

		SharedHashTableIter(const SharedHashTableIter& table)
		{
			this->fSharedHashTable = table.fSharedHashTable;
			this->fIndex = table.fIndex;
			this->fCurrent = table.fCurrent;
		}


		SharedHashTableIter &operator =(const SharedHashTableIter& table)
		{
			this->fSharedHashTable = table.fSharedHashTable;
			this->fIndex = table.fIndex;
			this->fCurrent = table.fCurrent;
			return *this;
		}



		SharedHashTableIter()
		{
			fSharedHashTable = nullptr;
			this->fCurrent = nullptr;
		}

		//const SharedHashTableShareIter& begin() {
		//	this->First();
		//	return *this;
		//}

		V operator *() {
			return this->fCurrent->value;
		}

		V operator->() {
			return this->fCurrent->value;
		}


		bool operator ==(const SharedHashTableIter &iter) {
			return (iter.fCurrent == this->fCurrent);
		}

		bool operator !=(const SharedHashTableIter &iter) {
			return (iter.fCurrent != this->fCurrent);
		}

		const SharedHashTableIter& operator++ () {
			this->Next();
			return *this;
		}

		const SharedHashTableIter& operator++ (int) {
			this->Next();
			return *this;
		}

		void First()
		{
			for (fIndex = 0; fIndex < fSharedHashTable->GetTableSize(); fIndex++) {
				fCurrent = fSharedHashTable->GetTableEntry(fIndex);
				if (fCurrent)
					break;
			}
		}
		void Next()
		{
			fCurrent = fCurrent->fNext;
			if (!fCurrent) {
				for (fIndex = fIndex + 1; fIndex < fSharedHashTable->GetTableSize(); fIndex++) {
					fCurrent = fSharedHashTable->GetTableEntry(fIndex);
					if (fCurrent)
						break;
				}
			}
		}
		bool IsDone()
		{
			return(fCurrent != NULL);
		}
		SharedHashEntry<K, V>* GetCurrent() { return fCurrent; }

	private:
		SharedHashTable<K, V>* fSharedHashTable;
		SharedHashEntry<K, V>* fCurrent;
		size_t fIndex;
	};




}

#endif