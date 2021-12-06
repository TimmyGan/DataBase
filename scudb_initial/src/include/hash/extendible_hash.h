/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <mutex>

#include "hash/hash_table.h"
//using namespace std;

namespace scudb {

    template <typename K, typename V>
    class Bucket{
        int localDepth;
        std::map<K,V> values;
    public:
        Bucket(int LocalDepth);
        int GetLocalDepth();
        std:: map<K,V> GetValues();
        size_t GetValuesSize();
        bool find(const K &key, V &value);
        bool remove(const K &key);
        void insert(const K &key, const V &value);
        void insert(std::pair<K,V> pair);
    };

    template <typename K, typename V>
    class ExtendibleHash : public HashTable<K, V> {
    public:
        // constructor
        ExtendibleHash();
        ExtendibleHash(size_t size);
        // helper function to generate hash addressing
        size_t HashKey(const K &key);
        // helper function to get global & local depth
        int GetGlobalDepth() const;
        int GetLocalDepth(int bucket_id) const;
        int GetNumBuckets() const;
        // lookup and modifier
        bool Find(const K &key, V &value) override;
        bool Remove(const K &key) override;
        void Insert(const K &key, const V &value) override;

    private:
        // add your own member variables here
        std::mutex mutex;
        int GetTableIndex(const K &key);
        int globalDepth;
        size_t bucketSize;
        int bucketNums;
        std:: vector<std::shared_ptr<Bucket<K,V>>> bucketTable;

    };
} // namespace scudb