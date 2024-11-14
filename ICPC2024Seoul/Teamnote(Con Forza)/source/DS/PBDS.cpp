#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

indexed_set<int> s;
s.insert(3); s.insert(2); s.insert(3);
s.insert(9); s.insert(7);
//2 3 7 9

s.insert(5); //2 3 5 7 9
s.erase(5); //2 3 7 9

auto x = s.find_by_order(2); // *x : 7

s.order_of_key(6) // 2
s.order_of_key(7) // 2
s.order_of_key(8) // 3