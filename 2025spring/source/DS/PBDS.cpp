#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

indexed_set<int> s;
s.insert(3); s.insert(2); s.insert(3); s.insert(9); s.insert(7); //2 3 7 9
s.insert(5); //2 3 5 7 9
s.erase(5); //2 3 7 9

auto x = s.find_by_order(2); // *x : 7

s.order_of_key(6) // 2
s.order_of_key(7) // 2
s.order_of_key(8) // 3

/////////////////////////////////////////////////////////////
// greater_equal <- ordered_multiset / greater <- ordered_multiset
#define oset_greater tree<ll, null_type, greater_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> 
#define oset_less tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>

void oset_m_erase(ordered_set_greater &OS, ll val){
    int index = OS.order_of_key(val);
    oset_greater::iterator it = OS.find_by_order(index);
    if(it != OS.end() && *it == val) OS.erase(it);
}


/////////////////////////////////////////////////////////////
rope<ll> r;
r.insert(r.size() - t, i); //r.size()-t번째 자리에 i를 삽입
r.substr(a, b - a + 1) // a부터 (b-a+1)개 만큼을 잘라낸다. 즉, [a, b] 선택
