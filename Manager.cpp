#include "stdafx.h"
#include "Manager.h"

int Int(const any& a) {
	if (a.type() == typeid(int))
		return any_cast<int>(a);
	else if (a.type() == typeid(unsigned int))
		return (int)any_cast<unsigned int>(a);
}
float Float(const any& a) {
	return any_cast<float>(a);
}
bool Bool(const any& a) {
	return any_cast<bool>(a);
}
Time_t Time(const any& a) {
	return any_cast<Time_t>(a);
}
Range_t Range(const any& a) {
	return any_cast<Range_t>(a);
}
string String(const any& a) {
	if (a.type() == typeid(int) || a.type() == typeid(unsigned int))
		return to_string(Int(a));
	else if (a.type() == typeid(float))
		return to_string(Float(a));
	else if (a.type() == typeid(bool))
		return Bool(a) ? string("true") : string("false");
	else if (a.type() == typeid(string))
		return any_cast<string>(a);
	else if (a.type() == typeid(Time_t)) {
		char str[64];
		time_t t = chrono::system_clock::to_time_t(any_cast<Time_t>(a));
		ctime_s(str, sizeof(str), &t); 
		string s = str;
		s.pop_back();
		return s;
	}
	else if (a.type() == typeid(Range_t))
		return to_string(any_cast<Range_t>(a).count());
	else {
		AfxMessageBox(__T("can't convert any to string"));
		exit(1);
	}
}

any operator+(const any& a, const any& b) {
	if (a.type() == b.type()) {
		if (a.type() == typeid(int)) {
			return any(Int(a) + Int(b));
		}
		else if (a.type() == typeid(float)) {
			return any(Float(a) + Float(b));
		}
		else if (a.type() == typeid(string)) {
			return any(String(a) + String(b));
		}
		else if (a.type() == typeid(Range_t)) {
			return any(Range(a) + Range(b));
		}
	}
	else {
		if (a.type() == typeid(string) || b.type() == typeid(string)) {
			return any(String(a) + String(b));
		}
		else if (a.type() == typeid(Time_t) && b.type() == typeid(Range_t)) {
			return any(Time(a) + Range(b));
		}
		else if (a.type() == typeid(Range_t) && b.type() == typeid(Time_t)) {
			return any(Range(a) + Time(b));
		}
		else if (a.type() == typeid(int) && b.type() == typeid(float)) {
			return any(Int(a) + Float(b));
		}
		else if (a.type() == typeid(float) && b.type() == typeid(int)) {
			return any(Float(a) + Int(b));
		}
	}
	AfxMessageBox(__T("invalid operand on + operator"));
	exit(1);
}
any operator-(const any& a, const any& b) {
	if (a.type() == b.type()) {
		if (a.type() == typeid(int)) {
			return any(Int(a) - Int(b));
		}
		else if (a.type() == typeid(float)) {
			return any(Float(a) - Float(b));
		}
		else if (a.type() == typeid(Time_t)) {
			return any(Time(a) - Time(b));
		}
		else if (a.type() == typeid(Range_t)) {
			return any(Range(a) - Range(b));
		}
	}
	else {
		if (a.type() == typeid(Time_t) && b.type() == typeid(Range_t)) {
			return any(Time(a) - Range(b));
		}
		else if (a.type() == typeid(int) && b.type() == typeid(float)) {
			return any(Int(a) - Float(b));
		}
		else if (a.type() == typeid(float) && b.type() == typeid(int)) {
			return any(Float(a) - Int(b));
		}
	}
	AfxMessageBox(__T("invalid operand on - operator"));
	exit(1);
}
any operator*(const any& a, const any& b) {
	if (a.type() == typeid(int) && b.type() == typeid(int)) {
		return any(Int(a) * Int(b));
	}
	else if (a.type() == typeid(float) && b.type() == typeid(float)) {
		return any(Float(a) * Float(b));
	}
	else if (a.type() == typeid(int) && b.type() == typeid(float)) {
		return any(Int(a) * Float(b));
	}
	else if (a.type() == typeid(float) && b.type() == typeid(int)) {
		return any(Float(a) * Int(b));
	}
	else {
		AfxMessageBox(__T("invalid type on * operator"));
		exit(1);
	}
}
any operator/(const any& a, const any& b) {
	if (a.type() == typeid(int) && b.type() == typeid(int)) {
		return any(Int(a) / Int(b));
	}
	else if (a.type() == typeid(float) && b.type() == typeid(float)) {
		return any(Float(a) / Float(b));
	}
	else if (a.type() == typeid(int) && b.type() == typeid(float)) {
		return any(Int(a) / Float(b));
	}
	else if (a.type() == typeid(float) && b.type() == typeid(int)) {
		return any(Float(a) / Int(b));
	}
	else {
		AfxMessageBox(__T("invalid type on / operator"));
		exit(1);
	}
}
bool operator<(const any& a, const any& b) {
	if (a.type() == b.type()) {
		if (a.type() == typeid(int)) return (any_cast<int>(a) < any_cast<int>(b));
		else if (a.type() == typeid(float)) return (any_cast<float>(a) < any_cast<float>(b));
		else if (a.type() == typeid(bool)) return (any_cast<bool>(a) < any_cast<bool>(b));
		else if (a.type() == typeid(string)) return (any_cast<string>(a) < any_cast<string>(b));
		else if (a.type() == typeid(Range_t)) return (any_cast<Range_t>(a) < any_cast<Range_t>(b));
		else if (a.type() == typeid(Time_t)) {
			//0.1초 단위로 계산
			auto t1 = any_cast<Time_t>(a).time_since_epoch().count() / 1000000;
			auto t2 = any_cast<Time_t>(b).time_since_epoch().count() / 1000000;
			return (t1 < t2);
		}
		else {
			AfxMessageBox(__T("compare operator not supported for that types"));
			exit(1);
		}
	}
	else {
		if (a.type() == typeid(float) && b.type() == typeid(int)) 
			return Float(a) < Int(a);
		else if (a.type() == typeid(int) && b.type() == typeid(float)) 
			return Int(a) < Float(a);
		else {
			AfxMessageBox(__T("compare operator not supported for other types"));
			exit(1);
		}
	}
}
bool operator==(const any& a, const any& b) {
	if (a.type() == b.type()) {
		if (a.type() == typeid(int)) return (any_cast<int>(a) == any_cast<int>(b));
		else if (a.type() == typeid(float)) return (any_cast<float>(a) == any_cast<float>(b));
		else if (a.type() == typeid(bool)) return (any_cast<bool>(a) == any_cast<bool>(b));
		else if (a.type() == typeid(string)) return (any_cast<string>(a) == any_cast<string>(b));
		else if (a.type() == typeid(Time_t)) return (any_cast<Time_t>(a) == any_cast<Time_t>(b));
		else if (a.type() == typeid(Range_t)) return (any_cast<Range_t>(a) == any_cast<Range_t>(b));
		else {
			AfxMessageBox(__T("invalid type on == operator"));
			exit(1);
		}
	}
	else {
		if (a.type() == typeid(float) && b.type() == typeid(int)) 
			return Float(a) == Int(a);
		else if (a.type() == typeid(int) && b.type() == typeid(float)) 
			return Int(a) == Float(a);
		else {
			AfxMessageBox(__T("compare operator not supported for other types"));
			exit(1);
		}
	}
}
bool operator!=(const any& a, const any& b) {
	return !(operator==(a, b));
}
bool operator<=(const any& a, const any& b) {
	return (operator==(a, b) | operator<(a, b));
}
bool operator>=(const any& a, const any& b) {
	return !operator<(a, b);
}
bool operator>(const any& a, const any& b) {
	return !operator<=(a, b);
}
bool operator||(const any& a, const any& b) {
	if (a.type() == b.type() && a.type() == typeid(bool))
		return any_cast<bool>(a) || any_cast<bool>(b);
	else {
		AfxMessageBox(__T("invalid type on || operator"));
		exit(1);
	}
}
bool operator&&(const any& a, const any& b) {
	if (a.type() == b.type() && a.type() == typeid(bool))
		return any_cast<bool>(a) && any_cast<bool>(b);
	else {
		AfxMessageBox(__T("invalid type on && operator"));
		exit(1);
	}
}

//EventType
EventType::EventType(string name, const vector<pair<string, string>>& vec) {
	this->name = name;
	int idx = 0;
	for (auto p : vec) {
		string attr_type = p.first;
		string attr_name = p.second;
		m.emplace(attr_name, pair<string, int>(attr_type, idx++));
	}
	v = vec;
}
int EventType::attr_cnt() {
	return v.size();
}
int EventType::getIdx(string attr_name) {
	return m.at(attr_name).second;
}
string EventType::getName() { 
	return name; 
}

//Event
Event::Event(EventType * event_type, const vector<any>& attrs) {
	this->event_type = event_type;
	cols = attrs;
	time_idx = event_type->getIdx("time");
}
Event::Event(EventType * event_type, const vector<pair<string, any>>& attrs) {
	this->event_type = event_type;
	cols.resize(event_type->attr_cnt());
	for (auto p : attrs) {
		int idx = event_type->getIdx(p.first);
		cols[idx] = p.second;
	}
	time_idx = event_type->getIdx("time");
}
any& Event::at(int idx) {
	return cols.at(idx);
}
any& Event::at(string attr_name) {
	int idx = event_type->getIdx(attr_name);
	return cols.at(idx);
}
int Event::getIdx(string attr_name) {
	return event_type->getIdx(attr_name);
}

//Stream
Stream::Stream(string stream_name, string event_type, int length) {
	this->stream_name = stream_name;
	this->event_type = EventTypeStorage::getEventType(event_type);
	this->length = length;
}
void Stream::add(Event event) {
	mtx.lock();

	if (li.size() >= length) {
		auto del_time = (*li.begin()).at("time");
		while (li.begin() != li.end() && (*li.begin()).at("time") == del_time)
			li.pop_front();
	}

	auto time = event.at("time");
	auto it = li.end();
	while (it != li.begin() && time < (*prev(it)).at("time"))
		it--;
	li.emplace(it, event);

	mtx.unlock();

	for (auto p : action_list) 
		p.second(event);
}
void Stream::addAction(string name, function<void(Event)> action) {
	action_list.emplace_back(pair<string, function<void(Event)>>(name , action));
}
void Stream::deleteAction(string name) {
	auto it = action_list.begin();
	while (it != action_list.end()) {
		if (it->first == name) {
			action_list.erase(it);
			break;
		}
		it++;
	}
}
//Parser
Parser::Parser() {
	priority_map = { {"&&", 4},
			 {"||", 4},
			 {"<=", 3},
			 {"<", 3},
			 {">=", 3},
			 {">", 3},
			 {"==", 3},
			 {"!=", 3},
			 {"+", 2},
			 {"-", 2},
			 {"*", 1},
			 {"/", 1} };
	string var_str = "(?:[a-zA-Z][a-zA-Z0-9_]*)";
	string group_var_str = "(?:[a-zA-Z][a-zA-Z0-9_]*\\([a-zA-Z][a-zA-Z0-9]*\\))";
	string int_str = "(?:[0-9]+)";
	string float_str = "(?:[0-9]+\\.[0-9]+)";
	string bool_str = "(?:true|false)";
	string string_str = "(?:\"[^\"]*\")";
	string attr_str = string("(?:") + bool_str
		+ "|" + group_var_str
		+ "|" + float_str
		+ "|" + var_str
		+ "|" + int_str
		+ "|" + bool_str
		+ "|" + string_str
		+ ")";
	string oper_str = string("(?:") + string("\\+")
		+ "|" + string("\\-")
		+ "|" + string("\\*")
		+ "|" + string("/")
		+ "|" + string("<=")
		+ "|" + string("<")
		+ "|" + string(">=")
		+ "|" + string(">")
		+ "|" + string("!=")
		+ "|" + string("==")
		+ "|" + string("&&")
		+ "|" + string("\\|\\|")
		+ ")";
	string tok_str = attr_str
		+ "|" + oper_str
		+ "|" + string("\\(")
		+ "|" + string("\\)");
	bool_exp = regex(bool_str);
	int_exp = regex(int_str);
	float_exp = regex(float_str);
	string_exp = regex(string_str);
	var_exp = regex(var_str);
	group_var_exp = regex(group_var_str);

	attr_exp = regex(attr_str);
	oper_exp = regex(oper_str);
	tok_exp = regex(tok_str);
}
function<any(Event&)> Parser::parseAttr(string s) {
	if (regex_match(s, bool_exp)) {
		any a = (s == "true" ? true : false);
		return [a](Event& e)->any { return a; };
	}
	else if (regex_match(s, float_exp)) {
		any a = stof(s);
		return [a](Event& e)->any { return a; };
	}
	else if (regex_match(s, int_exp)) {
		any a = stoi(s);
		return [a](Event& e)->any { return a; };
	}
	else if (regex_match(s, string_exp)) {
		s.pop_back();
		s.erase(0, 1);
		any a = s;
		return [a](Event& e)->any { return a; };
	}
	else if (regex_match(s, var_exp)) { //인덱스로 접근하는 최적화 필요
		//int i = event_type->getIdx(s);
		return[s](Event& e)->any { return e.at(s); };
	}
	else {
		AfxMessageBox(__T("can't parse attr on filter query"));
		exit(1);
	}
}
function<any(any, any)> Parser::parseOper(string s) {
	if (s == "+")
		return [](any a1, any a2)->any { return a1 + a2; };
	else if (s == "-")
		return [](any a1, any a2)->any { return a1 - a2; };
	else if (s == "*")
		return [](any a1, any a2)->any { return a1 * a2; };
	else if (s == "/")
		return [](any a1, any a2)->any { return a1 / a2; };
	else if (s == "<")
		return [](any a1, any a2)->any { return a1 < a2; };
	else if (s == "<=")
		return [](any a1, any a2)->any { return a1 <= a2; };
	else if (s == ">")
		return [](any a1, any a2)->any { return a1 > a2; };
	else if (s == ">=")
		return [](any a1, any a2)->any { return a1 >= a2; };
	else if (s == "==")
		return [](any a1, any a2)->any { return a1 == a2; };
	else if (s == "!=")
		return [](any a1, any a2)->any { return a1 != a2; };
	else if (s == "||")
		return [](any a1, any a2)->any { return a1 || a2; };
	else if (s == "&&")
		return [](any a1, any a2)->any { return a1 && a2; };
	else {
		AfxMessageBox(__T("can't parse operator"));
		exit(1);
	}
}
bool Parser::convertMedianToAfter(string s) {
	auto begin = sregex_iterator(s.begin(), s.end(), tok_exp);
	auto end = sregex_iterator();

	for (auto it = begin; it != end; it++) {
		string tok = (*it).str();
		if (tok == "(") {
			parse_stack.emplace(tok);
		}
		else if (tok == ")") {
			while (1) {
				string tmp_s = parse_stack.top();
				parse_stack.pop();

				if (regex_match(tmp_s, oper_exp))
					parse_q.emplace(tmp_s);
				else if (tmp_s == "(")
					break;
			}
		}
		else if (regex_match(tok, oper_exp)) {
			while (!parse_stack.empty()) {
				string tmp_s = parse_stack.top();
				if (regex_match(tmp_s, oper_exp) && priority_map.at(tmp_s) <= priority_map.at(tok)) {
					parse_stack.pop();
					parse_q.emplace(tmp_s);
				}
				else
					break;
			}
			parse_stack.emplace(tok);
		}
		else if (regex_match(tok, attr_exp)) {
			parse_q.emplace(tok);
		}
		else {
			return false;
		}
	}
	while (!parse_stack.empty()) {
		parse_q.emplace(parse_stack.top());
		parse_stack.pop();
	}
	return true;
}
function<any(Event&)> Parser::parseQueueFilter() {
	string s = parse_q.top();
	parse_q.pop();
	if (regex_match(s, oper_exp)) {
		auto oper_func = parseOper(s);
		auto right_func = parseQueueFilter();
		auto left_func = parseQueueFilter();
		return [oper_func, right_func, left_func](Event& e)->any {return oper_func(left_func(e), right_func(e)); };
	}
	else if (regex_match(s, attr_exp)) {
		return parseAttr(s);
	}
	else {
		AfxMessageBox(__T("invalid queue item on filter query")); 
		exit(1);
	}
}
function<any(Event&)> Parser::getWhere(string s, bool * result) {
	while (!parse_stack.empty()) parse_stack.pop();
	while (!parse_q.empty()) parse_q.pop();

	if (s.empty())
		return [](Event& e)->any {return any(true); };

	convertMedianToAfter(s);
	auto where_func = parseQueueFilter();


	*result = parse_q.empty();
	return where_func;
}
function<any(Event&)> Parser::getSelect(string s, bool * result) {
	while (!parse_stack.empty()) parse_stack.pop();
	while (!parse_q.empty()) parse_q.pop();

	convertMedianToAfter(s);
	auto select_func = parseQueueFilter();

	*result = parse_q.empty();
	return select_func;
}
function<any(list<Event>&)> Parser::getHaving(string s, bool * result) {
	while (!parse_stack.empty()) parse_stack.pop();
	while (!parse_q.empty()) parse_q.pop();

	if (s.empty())
		return [](list<Event>& li)->any {return any(true); };

	convertMedianToAfter(s);
	auto having_func = parseQueueGroup();
	*result = parse_q.empty();
	return having_func;
}
function<any(list<Event>&)> Parser::parseAttrGroup(string s) {
	if (regex_match(s, bool_exp)) {
		any a = (s == "true" ? true : false);
		return [a](list<Event>& e)->any { return a; };
	}
	else if (regex_match(s, float_exp)) {
		any a = stof(s);
		return [a](list<Event>& e)->any { return a; };
	}
	else if (regex_match(s, int_exp)) {
		any a = stoi(s);
		return [a](list<Event>& e)->any { return a; };
	}
	else if (regex_match(s, string_exp)) {
		s.pop_back();
		s.erase(0, 1);
		any a = s;
		return [a](list<Event>& e)->any { return a; };
	}
	else if (regex_match(s, var_exp)) { //인덱스로 접근하는 최적화 필요
		//int i = event_type->getIdx(s);
		return[s](list<Event>& li)->any { return (*li.rbegin()).at(s); };
	}
	else if (regex_match(s, group_var_exp)) {
		smatch m;
		regex_match(s, m, regex("([a-zA-Z][a-zA-Z0-9_]*)\\(([a-zA-Z][a-zA-Z0-9_]*)\\)"));
		string agg_func_name = m.str(1);
		string attr_name = m.str(2);
		auto agg_func = AggregationStorage::getAggregation(agg_func_name);
		return[agg_func, attr_name](list<Event>& li)->any { return agg_func(attr_name, li); };
	}
	else {
		AfxMessageBox(__T("can't parse attr on group query"));
		exit(1);
	}
}
function<any(list<Event>&)> Parser::parseQueueGroup() {
	string s = parse_q.top();
	parse_q.pop();

	if (regex_match(s, oper_exp)) {
		auto oper_func = parseOper(s);
		auto right_func = parseQueueGroup();
		auto left_func = parseQueueGroup();
		return [oper_func, right_func, left_func](list<Event>& li)->any {return oper_func(left_func(li), right_func(li)); };
	}
	else if (regex_match(s, attr_exp)) {
		return parseAttrGroup(s);
	}
	else {
		AfxMessageBox(__T("invalid queue item on group query"));
		exit(1);
	}
}
function<any(list<Event>&)> Parser::getSelectGroup(string s, bool * result) {
	while (!parse_stack.empty()) parse_stack.pop();
	while (!parse_q.empty()) parse_q.pop();

	convertMedianToAfter(s);
	auto select_group_func = parseQueueGroup();
	*result = parse_q.empty();
	return select_group_func;
}

//Query
Query::Query(string query_name,
	Stream * in_stream,
	Stream * out_stream,
	string where_string,
	function<any(Event&)> where_func,
	vector<string> select_strings)
{
	this->query_name = query_name;
	this->in_stream = in_stream;
	this->out_stream = out_stream;
	this->in_event_type = in_stream->event_type;
	if (out_stream != NULL) this->out_event_type = out_stream->event_type;
	this->select_strings = select_strings;
	this->where_string = where_string;
	this->where_func = where_func;
}

//FilterQuery
FilterQuery::FilterQuery(string query_name,
	Stream * in_stream,
	Stream * out_stream,
	string where_string,
	function<any(Event&)> where_func,
	vector<string> select_strings,
	vector<function<any(Event&)>>& select_funcs)
	: Query(query_name, in_stream, out_stream, where_string, where_func, select_strings) 
{
	this->select_funcs = select_funcs;
	this->in_stream->action_list.emplace_back(pair<string, function<void(Event)>>(query_name, [this](Event e)->void {updateEvent(e);}));
	this->query_type = QueryType(filter_type, none_b);
}
FilterQuery::~FilterQuery() {
	in_stream->deleteAction(query_name);
}
void FilterQuery::updateEvent(Event& e) {
	if (Bool(where_func(e))) {
		if (out_stream != NULL) {
			vector<any> v;
			for (auto f : select_funcs)
				v.emplace_back(f(e));
			Event out_event(out_event_type, v);
			out_stream->add(out_event);
		}
		for (auto p : action_func_list)
			p.second(e);
	}
}
void FilterQuery::addAction(string action_name) {
	for (auto p : action_func_list) 
		if (p.first == action_name)
			return;
	auto action = ActionStorage::getFilterAction(action_name);
	if (action != NULL)
		action_func_list.emplace_back(action_name, action);
}
void FilterQuery::deleteAction(string action_name) {
	auto it = action_func_list.begin();
	while (it != action_func_list.end()) {
		if (it->first == action_name) {
			action_func_list.erase(it);
			break;
		}
		it++;
	}
}

//GroupQuery
GroupQuery::GroupQuery(string query_name,
	Stream * in_stream,
	Stream * out_stream,
	string where_string,
	function<any(Event&)> where_func,
	vector<string> group_attr_strings,
	string having_string,
	function<any(list<Event>&)> having_func,
	vector<string> select_strings,
	vector<function<any(list<Event>&)>> select_funcs,
	int seconds) 
	: Query(query_name, in_stream, out_stream, where_string, where_func, select_strings) 
{
	this->query_type.type_a = group_type;
	this->group_attr_strings = group_attr_strings;
	for (string attr_name : group_attr_strings)
		this->group_attr_idxs.emplace_back(in_event_type->getIdx(attr_name));
	this->having_string = having_string;
	this->having_func = having_func;
	this->select_funcs = select_funcs;
	this->seconds = seconds;
}
void GroupQuery::addAction(string action_name) {
	auto action = ActionStorage::getGroupAction(action_name);
	mtx.lock();
	for (auto p : action_func_list)
		if (p.first == action_name)
			return;
	if (action != NULL)
		action_func_list.emplace_back(action_name, action);
	mtx.unlock();
}
void GroupQuery::deleteAction(string action_name) {
	mtx.lock();
	auto it = action_func_list.begin();
	while (it != action_func_list.end()) {
		if (it->first == action_name) {
			action_func_list.erase(it);
			break;
		}
		it++;
	}
	mtx.unlock();
}
void GroupQuery::stopThread() {
	query_running = false;
	query_thread.join();
}

//TimeGroupQuery
TimeGroupQuery::TimeGroupQuery(string query_name,
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
	int seconds)
	:GroupQuery(query_name, in_stream, out_stream, where_string, where_func, group_attr_strings, having_string, having_func, select_strings, select_funcs, seconds)
{
	this->range = range;
	current_time = getCurrentTime();
	min_time = current_time - range;

	query_running = true;
	query_thread = thread([this]() {
		while (query_running) {
			Sleep(this->seconds);
			Update();
		}
	});
	this->in_stream->action_list.emplace_back(pair<string, function<void(Event)>>(query_name, [this](Event e)->void {updateEvent(e);}));
}
TimeGroupQuery::~TimeGroupQuery() {
	stopThread();
	in_stream->deleteAction(query_name);
}
void TimeGroupQuery::updateEvent(Event& event) {
	Time_t time = Time(event.getTime());

	mtx.lock();
	if (current_time < time) {
		current_time = time;
		min_time = current_time - range;
	}
	mtx.unlock();

	if (min_time <= time && Bool(where_func(event))) {
		vector<any> key;
		for (auto idx : group_attr_idxs)
			key.emplace_back(event.at(idx));

		mtx.lock();
		if (group_map.find(key) == group_map.end()) {
			group_map.emplace(key, list<Event>());
			group_map.at(key).emplace_back(event);
		}
		else {
			list<Event>& group = group_map.at(key);
			auto it = group.end();
			while (it != group.begin()) {
				if (prev(it)->getTime() <= time) 
					break;
				it--;
			}
			group.emplace(it, event);
		}
		mtx.unlock();
	}
}
void TimeGroupQuery::Update() {
	mtx.lock();
	Time_t time = getCurrentTime();
	if (current_time < time) {
		current_time = time;
		min_time = current_time - range;
	}
	vector<GroupMap::iterator> erase_iters;
	vector<any> select_attrs;

	vector<list<Event>*> v;
	auto it = group_map.begin();
	while (it != group_map.end()) {
		list<Event>& li = it->second;
		while (!li.empty() && Time(li.begin()->getTime()) < min_time) 
			li.pop_front();

		if (li.empty()) {
			erase_iters.emplace_back(it);
		}
		else if (Bool(having_func(li))) {
			if (out_stream != NULL) {
				select_attrs.clear();
				for (auto f : select_funcs)
					select_attrs.emplace_back(f(li));
				out_stream->add(Event(out_event_type, select_attrs));
			}
			v.emplace_back(&li);
		}
		it++;
	}
	for (auto erase_it : erase_iters) {
		group_map.erase(erase_it);
	}

	for (auto p : action_func_list) 
		p.second(v);

	mtx.unlock();
}


//CountGroupQuery
CountGroupQuery::CountGroupQuery(string query_name, int count,
	Stream * in_stream,
	Stream * out_stream,
	vector<string> group_attr_strings,
	string where_string,
	function<any(Event&)> where_func,
	string having_string,
	function<any(list<Event>&)> having_func,
	vector<string> select_strings,
	vector<function<any(list<Event>&)>> select_funcs,
	int seconds)
	:GroupQuery(query_name, in_stream, out_stream, where_string, where_func, group_attr_strings, having_string, having_func, select_strings, select_funcs, seconds)
{
	this->count = count;
	current_time = getCurrentTime();

	query_running = true;
	query_thread = thread([this]() {
		while (query_running) {
			Sleep(this->seconds);
			Update();
		}
	});
	this->in_stream->action_list.emplace_back(pair<string, function<void(Event)>>(query_name, [this](Event e)->void {updateEvent(e);}));
}
CountGroupQuery::~CountGroupQuery() {
	stopThread();
	in_stream->deleteAction(query_name);
}
void CountGroupQuery::updateEvent(Event& event) {
	if (Bool(where_func(event))) {
		Time_t time = Time(event.getTime());
		vector<any> key;
		for (auto idx : group_attr_idxs)
			key.emplace_back(event.at(idx));

		mtx.lock();
		if (group_map.find(key) == group_map.end()) {
			group_map.emplace(key, list<Event>());
			group_map.at(key).emplace_back(event);
		}
		else {
			list<Event>& group = group_map.at(key);
			auto it = group.end();
			while (it != group.begin()) {
				if (Time(prev(it)->getTime()) <= time) 
					break;
				it--;
			}
			group.emplace(it, event);
			if (count < group.size())
				group.pop_front();
		}
		mtx.unlock();
	}
}
void CountGroupQuery::Update() {
	mtx.lock();
	current_time = getCurrentTime();
	vector<any> select_attrs;
	vector<list<Event>*> v;
	for (auto &p : group_map) {
		list<Event>& li = p.second;
		if (Bool(having_func(li))) {
			if (out_stream != NULL) {
				select_attrs.clear();
				for (auto f : select_funcs)
					select_attrs.emplace_back(f(li));
				out_stream->add(Event(out_event_type, select_attrs));
			}
			v.emplace_back(&li);
		}
	}
	for (auto p : action_func_list) {
		p.second(v);
	}
	mtx.unlock();
}

//EventTypeStorage
void EventTypeStorage::addEventType(string event_type_name, const vector<pair<string, string>>& vec) {
	if (m.find(event_type_name) == m.end())
		m.emplace(event_type_name, new EventType(event_type_name, vec));
	else
		AfxMessageBox(__T("동일한 이름의 이벤트 타입이 이미 존재합니다."));
}
EventType * EventTypeStorage::getEventType(string event_type_name) {
	if (m.find(event_type_name) != m.end())
		return m.at(event_type_name);
	else
		return NULL;
}

//StreamStorage
void StreamStorage::addStream(string stream_name, string event_type_name, int length) {
	if (m.find(stream_name) == m.end())
		m.emplace(stream_name, new Stream(stream_name, event_type_name, length));
	else 
		AfxMessageBox(__T("동일한 이름의 스트림이 이미 존재합니다."));
}
Stream * StreamStorage::getStream(string stream_name) {
	if (m.find(stream_name) != m.end())
		return m.at(stream_name);
	else
		return NULL;
}

//QueryStorage
void QueryStorage::addQuery(string query_name, Query * query) {
	query_map.emplace(query_name, query);
}
Query * QueryStorage::getQuery(string query_name) {
	if (query_map.find(query_name) != query_map.end())
		return query_map.at(query_name);
	else
		return NULL;
}
FilterQuery * QueryStorage::getFilterQuery(string query_name) {
	if (query_map.find(query_name) != query_map.end()) {
		Query * query = query_map.at(query_name);
		if (query->query_type.type_a == filter_type)
			return (FilterQuery *)query;
		else
			return NULL;
	}
	else
		return NULL;
}
GroupQuery * QueryStorage::getGroupQuery(string query_name) {
	if (query_map.find(query_name) != query_map.end()) {
		Query * query = query_map.at(query_name);
		if (query->query_type.type_a == group_type)
			return (GroupQuery *)query;
		else
			return NULL;
	}
	else
		return NULL;
}
void QueryStorage::deleteQuery(string query_name) {
	if (query_map.find(query_name) != query_map.end()) {
		Query * query = query_map.at(query_name);
		query_map.erase(query_name);
		delete query;
	}
	else {
		AfxMessageBox(__T("해당하는 이름을 가진 쿼리가 존재하지 않습니다."));
	}
}

//ActionStorage
void ActionStorage::addFilterAction(string action_name, function<void(Event&)> action) {
	filter_action_map.emplace(action_name, action);
}
void ActionStorage::addGroupAction(string action_name, function<void(vector<list<Event>*>)> action) {
	group_action_map.emplace(action_name, action);
}
function<void(Event&)> ActionStorage::getFilterAction(string action_name) {
	if (filter_action_map.find(action_name) == filter_action_map.end())
		return NULL;
	else
		return filter_action_map.at(action_name);
}
function<void(vector<list<Event>*>)> ActionStorage::getGroupAction(string action_name) {
	if (group_action_map.find(action_name) == group_action_map.end())
		return NULL;
	else
		return group_action_map.at(action_name);
}

//AggregationStorage
function<any(string, list<Event>&)> AggregationStorage::getAggregation(string func_name) {
	if (m.find(func_name) != m.end())
		return m.at(func_name);
	else 
		return NULL;
}
void AggregationStorage::addAggregation(string func_name, function<any(string, list<Event>&)> func) {
	if (m.find(func_name) == m.end())
		m.emplace(func_name, func);
	else 
		AfxMessageBox(__T("동일한 이름의 집계함수가 이미 존재합니다."));
}

//Storage map;
map<string, EventType*> EventTypeStorage::m;
map<string, function<any(string, list<Event>&)>> AggregationStorage::m;
map<string, Stream*> StreamStorage::m;
map<string, Query *> QueryStorage::query_map;
map<string, function<void(Event&)>> ActionStorage::filter_action_map;
map<string, function<void(vector<list<Event>*>)>> ActionStorage::group_action_map;
