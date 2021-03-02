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
	bool operator==(Node<T, S> nd) const { return nd.key == key; }
};
template<typename T, typename S>
class LRUCache {
private:
	int capacity;
	list < Node<T, S> > cache;
	unordered_map<T, typename list < Node<T, S> >::iterator > map;
	void MakeRecent(T key) {
		// auto iter = map[key];
		// auto node = *iter;
		// cache.erase(iter);
		// cache.push_back(node);
		// map[key] = prev(cache.end());
		auto val = map[key]->val;
		DeleteKey(key);
		AddRecent(key, val);
	}
	void AddRecent(T key, S val) {
		cache.emplace_back(key, val);
		auto iter_last = std::prev(cache.end());
		map.emplace(key, iter_last);
	}
	void DeleteKey(T key) {
		auto iter = map[key];
		cache.erase(iter);
		map.erase(key);
	}
	void DeleteLeastRecent() {
		auto node = cache.front();
		cache.pop_front();
		map.erase(node.key);
	}
public:
	LRUCache(int cap) :capacity(cap) {}
	S get(T key) {
		if (map.find(key) == map.end())
			return S();
		MakeRecent(key);
		auto iter = map[key];
		return iter->val;
	}
	void put(T key, S val) {
		if (map.find(key) != map.end()) {
			DeleteKey(key);
			AddRecent(key, val);
		}
		else{
		        if (cache.size() == capacity)
			        DeleteLeastRecent();
			AddRecent(key, val);
		}
	}
};

// for test as follow
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
	auto l1 = lru.get(1);
	auto l2 = lru.get(2);
	auto l3 = lru.get(3);
	lru.put(9, "10");
	lru.put(10, "11");
	auto l9 = lru.get(9);

	LRUCache<int, A> lru_a(2);
	lru_a.put(1, A(3, 5));
	lru_a.put(2, A(4, 5));
	lru_a.put(3, A(5, 6));
	lru_a.get(2);
	lru_a.get(1);
	return 0;
}
