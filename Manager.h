#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <functional>
#include <Windows.h>
#include <any>
#include <regex>
#include <ctime>
#include <thread>
#include <mutex>
#include "MyTime.h"

using namespace std;

int Int(const any& a);
float Float(const any& a);
bool Bool(const any& a);
string String(const any& a);
Time_t Time(const any& a);
Range_t Range(const any& a);

any operator+(const any& a, const any& b);
any operator-(const any& a, const any& b);
any operator*(const any& a, const any& b);
any operator/(const any& a, const any& b);
bool operator<(const any& a, const any& b);
bool operator<=(const any& a, const any& b);
bool operator>(const any& a, const any& b);
bool operator>=(const any& a, const any& b);
bool operator==(const any& a, const any& b);
bool operator!=(const any& a, const any& b);
bool operator||(const any& a, const any& b);
bool operator&&(const any& a, const any& b);

class any_vec_comp {
 public :
    bool operator()(const vector<any>& v1, const vector<any>& v2) const {
	if (v1.size() == v2.size()) {
	    for (int i = 0; i < v1.size(); i++) 
		if (v1.at(i) != v2.at(i))
		    return v1.at(i) < v2.at(i);
	    return false;
	}
	else
	    return v1.size() < v2.size();
    }
};

class AttrComp {
 public:
    bool operator()(const any& a1, const any& a2) const { return a1 < a2; }
};

class EventType {
 public:
    map<string, pair<string, int>> m;
    vector<pair<string, string>> v;
    string name;
 public:
    EventType(string name, const vector<pair<string, string>>& vec);
    int attr_cnt();
    int getIdx(string attr_name);
	string getName();
};


class Event {
 public:
    vector<any> cols;
    EventType * event_type;
	int time_idx;
 public:
    Event(EventType * event_type, const vector<any>& attrs);
    Event(EventType * event_type, const vector<pair<string, any>>& attrs);
    any& at(string attr_name);
    any& at(int idx);
	any& getTime() { return cols.at(time_idx); }
    int getIdx(string attr_name);
};


class Stream {
public:
	list<Event> li;
	int length;
	EventType * event_type;
	string stream_name;
	list<pair<string, function<void(Event)>>> action_list;
	mutex mtx;
public:
	Stream(string stream_name, string event_type_name, int length);
	void add(Event event);
	void addAction(string name, function<void(Event)> action);
	void deleteAction(string name);
};


class Parser {
 private:
    stack<string> parse_q;
    stack<string> parse_stack;
    map<string, int> priority_map;
    regex tok_exp;
    regex attr_exp;
    regex oper_exp;
    regex bool_exp;
    regex int_exp;
    regex float_exp;
    regex string_exp;
    regex var_exp;
    regex group_var_exp;
 public:
    Parser();
    bool convertMedianToAfter(string s);
    function<any(Event&)> parseAttr(string s);
    function<any(any, any)> parseOper(string s);
    function<any(Event&)> parseQueueFilter();
    function<any(Event&)> getWhere(string s, bool * result);
    function<any(Event&)> getSelect(string s, bool * result);

    function<any(list<Event>&)> getSelectGroup(string s, bool * result);
    function<any(list<Event>&)> getHaving(string s, bool * result);
    function<any(list<Event>&)> parseQueueGroup();
    function<any(list<Event>&)> parseAttrGroup(string s);
};

typedef enum {none_a, filter_type, group_type}query_type_a;
typedef enum {none_b, time_window, count_window}query_type_b;

class QueryType {
public :
	query_type_a type_a;
	query_type_b type_b;
	QueryType() : type_a(none_a), type_b(none_b) {};
	QueryType(query_type_a a, query_type_b b) : type_a(a), type_b(b) {};
};

class Query {
 public:
	 string query_name;
	 QueryType query_type;
	 Stream * in_stream;
	 Stream * out_stream;
	 EventType * in_event_type;
	 EventType * out_event_type;
	 vector<string> select_strings;
	 string where_string;
	 function<any(Event&)> where_func;
public :
	Query(string query_name,
		Stream * in_stream,
		Stream * out_stream,
		string where_string,
		function<any(Event&)> where_func,
		vector<string> select_exprs);
	 virtual ~Query() {};
	 virtual void updateEvent(Event& event) = 0;
	 virtual string getQueryType() = 0;
};
class FilterQuery : public Query {
public :
    vector<function<any(Event&)>> select_funcs;
	list<pair<string, function<void(Event&)>>> action_func_list;
 public:
	 FilterQuery(string query_name,
		 Stream * in_stream,
		 Stream * out_stream,
		 string where_string,
		 function<any(Event&)> where_func,
		 vector<string> select_strings,
		 vector<function<any(Event&)>>& select_funcs);
	 ~FilterQuery();
    virtual void updateEvent(Event& event);
    virtual string getQueryType() { return "Filter"; }
	void addAction(string action_name);
	void deleteAction(string action_name);
};
typedef map<vector<any>, list<Event>, any_vec_comp> GroupMap;
class GroupQuery : public Query {
public :
    Time_t current_time;
    thread query_thread;
    bool query_running;
    mutex mtx;
	int seconds;

	vector<string> group_attr_strings;
    vector<int> group_attr_idxs;
    GroupMap group_map;
	string having_string;
    function<any(list<Event>&)> having_func;
    vector<function<any(list<Event>&)>> select_funcs;
	list<pair<string, function<void(vector<list<Event>*>)>>> action_func_list;
public :
	GroupQuery(string query_name,
		Stream * in_stream,
		Stream * out_stream,
		string where_string,
		function<any(Event&)> where_func,
		vector<string> group_attr_strings,
		string having_string,
		function<any(list<Event>&)> having_func,
		vector<string> select_strings,
		vector<function<any(list<Event>&)>> select_funcs,
		int seconds);
	virtual void Update() = 0;
    void stopThread();
	void addAction(string action_name);
	void deleteAction(string action_name);
};
class TimeGroupQuery : public GroupQuery {
public:
	Range_t range;
	Time_t min_time;
public:
	TimeGroupQuery(string query_name,
		Range_t range,
		Stream * in_stream,
		Stream * out_stream,
		vector<string> group_attr_strings,
		string where_string,
		function<any(Event&)> where_func,
		string having_string,
		function<any(list<Event>&)> having_func,
		vector<string> select_strings,
		vector<function<any(list<Event>&)>> select_funcs,
		int seconds);
	 ~TimeGroupQuery();
    virtual string getQueryType(){ return "Time Group"; }
    virtual void updateEvent(Event& event);
    virtual void Update();
};
class CountGroupQuery : public GroupQuery {
public:
	int count;
public:
	CountGroupQuery(string query_name,
		int count,
		Stream * in_stream,
		Stream * out_stream,
		vector<string> group_attr_strings,
		string where_string,
		function<any(Event&)> where_func,
		string having_string,
		function<any(list<Event>&)> having_func,
		vector<string> select_strings,
		vector<function<any(list<Event>&)>> select_funcs,
		int seconds);
	~CountGroupQuery();
	virtual string getQueryType() { return "Count Group"; }
	virtual void updateEvent(Event& event);
	virtual void Update();
};

//Storage
class EventTypeStorage {
 public:
    static map<string, EventType *> m;
 public:
    static void addEventType(string event_type_name, const vector<pair<string, string>>& vec);
    static EventType * getEventType(string event_type_name);
};
class StreamStorage {
 public:
    static map<string, Stream*> m;
    static void addStream(string stream_name, string event_type_name, int length);
    static Stream * getStream(string stream_name);
};
class QueryStorage {
 public:
    static map<string, Query *> query_map;
 public:
	 static void addQuery(string query_name, Query * query);
	 static Query * getQuery(string query_name);
	 static FilterQuery * getFilterQuery(string query_name);
	 static GroupQuery * getGroupQuery(string query_name);
	 static void deleteQuery(string query_name);
};
class ActionStorage {
public :
	static map<string, function<void(Event&)>> filter_action_map;
	static map<string, function<void(vector<list<Event>*>)>> group_action_map;
public :
	static void addFilterAction(string action_name, function<void(Event&)> action);
	static void addGroupAction(string action_name, function<void(vector<list<Event>*>)> action);
	static function<void(Event&)> getFilterAction(string action_name);
	static function<void(vector<list<Event>*>)> getGroupAction(string action_name);
};
class AggregationStorage {
 public:
    static map<string, function<any(string, list<Event>&)>> m;
 public:
    static function<any(string, list<Event>&)> getAggregation(string func_name);
    static void addAggregation(string func_name, function<any(string, list<Event>&)> func);
};