#include <iostream> // for test in main
#include <string> // for test in main
#include <unordered_map> // for linked hashmap
#include <list> // for linked hashmap
using namespace std;

template<typename T, typename S>
struct Node {
	T key;
	S val;
	Node() :key(T()), val(S()) {}
	Node(T k, S v) :key(k), val(v) {}
	// for list func remove
	bool operator==(Node<T,S> nd) const { return nd.key == key; }
};

template<typename T, typename S>
class LRUCache {
private:
	int capacity;
	list < Node<T, S> > cache;
	unordered_map<T, Node<T, S> > map;
	void MakeRecent(T key) {
		auto node = map[key];
		cache.remove(node);
		cache.push_back(node);
	}
	void AddRecent(T key, S val) {
		cache.emplace_back(key, val);
		map.emplace(key, Node<T, S>(key, val));
	}
	void DeleteKey(T key) {
		auto node = map[key];
		cache.remove(node);
		map.erase(key);
	}
	void DeleteLeastRecent() {
		auto pa = cache.front();
		cache.pop_front();
		map.erase(pa.key);
	}
public:
	LRUCache(int cap) :capacity(cap) {}
	S get(T key) {
		if (map.find(key) == map.end())
			return S();
		MakeRecent(key);
		return map[key].val;
	}
	void put(T key, S val) {
		if (map.find(key) != map.end()) {
			DeleteKey(key);
			AddRecent(key, val);
		}
		if (cache.size() == capacity)
			DeleteLeastRecent();
		AddRecent(key, val);
	}
};

class A { // for test user-defined type
public:
	A() = default;
	A(int x, int y) : a(x), b(y) {}
	int a;
	double b;
};
int main() {
	LRUCache<int, string> lru(3);
	lru.put(1, "2");
	lru.put(2, "3");
	lru.put(3, "4");
	lru.put(4, "5");
	std::cout << lru.get(2) << std::endl;
	std::cout << lru.get(1) << std::endl;
	LRUCache<int, A> lru_a(2);
	lru_a.put(1, A(3, 5));
	lru_a.put(2, A(4, 5));
	lru_a.put(3, A(5, 6));
	lru_a.get(2);
	lru_a.get(1);
	return 0;
}