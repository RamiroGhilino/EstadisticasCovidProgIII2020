#ifndef U05_HASH_HASHMAP_HASHENTRY_H_
#define U05_HASH_HASHMAP_HASHENTRY_H_

template<class K, class T>
class HashEntry {
private:
    K key;
    T data;
    HashEntry<K, T> *next;
public:
    HashEntry(K k, T d) : key(k), data(d) {}

    void setnext(HashEntry<K, T> *Next) {
        next = Next;
    }

    HashEntry<K, T> *getnext() {
        return next;
    }

    K getKey() {
        return key;
    }

    void setKey(K key) {
        HashEntry::key = key;
    }

    T getData() {
        return data;
    }

    void setData(T data) {
        HashEntry::data = data;
    }
};

#endif // U05_HASH_HASHMAP_HASHENTRY_H_
