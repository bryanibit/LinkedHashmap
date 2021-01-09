## What is the Project

The project is used for building linked hashmap with C++. LRU(Least Recently Used) is widely used in recent app, which is an example of linked hashmap.

## What is the point

`std::list::remove` time complexity is O(n) and `std::list::erase` is O(1). the latter's argument is iterator, instead of val itself, which is argument of the formmer. So the map's type is `unordered_map<T, list<Node<T, S>>::iterator>`.  
When applying *erase* to list, then original pointer(iterator) is out of work. For example, in `MakeRecent`, we should update `map[key]` because original node is erased. All in all, we should make sure both is consistent.
