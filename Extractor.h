#pragma once
#include "simul.h"
#include "Manager.h"


Event convertDataToEvent(Data& data);

class Extractor {
private:
	Stream * out_stream;
	EventType * out_event_type;
	queue<Data> * q;
	mutex * q_mtx;
	function<Event(Data&)> trans_func;
	thread extracting_thread;

	bool running = false;
	int period;
public:
	Extractor(Stream * out_stream, queue<Data> * q, mutex * q_mtx, function<Event(Data&)> trans_func, int period);
	void start();
	void stop();
	void clear();
};

