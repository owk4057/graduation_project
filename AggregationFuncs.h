#pragma once
#include "Manager.h"


any MySum(string attr_name, list<Event>& group);
any MyAverage(string attr_name, list<Event>& group);
any MyCount(string attr_name, list<Event>& group);
any MyMax(string attr_name, list<Event>& group);
any MyMin(string attr_name, list<Event>& group);



void InitAggregationStorage();

