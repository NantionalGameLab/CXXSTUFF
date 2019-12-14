#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <hash_map>
#include <hash_set>

struct XKey {
	std::string first;
	std::string second;
};

//! hash function
struct KeyHash {
	size_t operator()(const XKey& k)const {

		size_t t1 = std::hash<std::string>{}(k.first);

		std::hash<std::string> hash_fn;
		size_t t2 = hash_fn(k.second);
		return t1 ^ (t2  << 1);
	}
};

//! compare function--重载()运算符
struct KeyEqual {
	bool operator()(const XKey& lhs,const XKey& rhs) const{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
};


