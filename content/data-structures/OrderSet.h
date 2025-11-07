/**
 * Author: Thieu Nguyen Huy
 * Description: Ordered set.
 * Usage: 0-indexed, find_by_order(), order_of_key()
 * Time: O(\log N) for each operation
 * Status: Not tested
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;