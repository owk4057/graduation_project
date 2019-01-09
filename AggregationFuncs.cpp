#include "stdafx.h"
#include "AggregationFuncs.h"

any MySum(string attr_name, list<Event>& group) {
	any res = 0;
	int attr_idx = (*(group.begin())).getIdx(attr_name);
	for (auto e : group) {
		res = res + e.at(attr_idx);
	}
	return res;
}
any MyAverage(string attr_name, list<Event>& group) {
	any res = 0;
	int attr_idx = (*(group.begin())).getIdx(attr_name);
	for (auto e : group) {
		res = res + e.at(attr_idx);
	}

	if (res.type() == typeid(int))
		return res / any((int)group.size());
	else 
		return res / any((float)group.size());
}
any MyCount(string attr_name, list<Event>& group) {
    return (int)group.size();
}
any MyMax(string attr_name, list<Event>& group) {
	int attr_idx = group.begin()->getIdx(attr_name);
	any max = group.begin()->at(attr_idx);
	for (auto e : group) 
		if (max < e.at(attr_idx))
			max = e.at(attr_idx);
	return max;
}
any MyMin(string attr_name, list<Event>& group) {
	int attr_idx = group.begin()->getIdx(attr_name);
	any min = group.begin()->at(attr_idx);
	for (auto e : group) 
		if (min > e.at(attr_idx))
			min = e.at(attr_idx);
	return min;
}

void InitAggregationStorage() {
	AggregationStorage::addAggregation("sum", MySum);
	AggregationStorage::addAggregation("average", MyAverage);
	AggregationStorage::addAggregation("count", MyCount);
}
