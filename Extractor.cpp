#include "stdafx.h"
#include "Extractor.h"

Extractor::Extractor(Stream * out_stream,
	queue<Data> * q,
	mutex * q_mtx,
	function<Event(Data&)> trans_func,
	int period) {
	this->out_stream = out_stream;
	this->out_event_type = out_stream->event_type;
	this->q = q;
	this->q_mtx = q_mtx;
	this->trans_func = trans_func;
	this->period = period;
}

void Extractor::start() {
	running = true;
	extracting_thread = thread([this]() {
		while (running) {
			Sleep(this->period);
			if (!this->q->empty()) {
				this->q_mtx->lock();
				while (!this->q->empty()) {
					Data d = this->q->front();
					this->q->pop();
					Event e = trans_func(d);
					this->out_stream->add(e);
				}
				this->q_mtx->unlock();
			}
		}
	});
}
void Extractor::stop() {
	running = false;
	extracting_thread.join();
}
void Extractor::clear() {
	stop();
}


Event convertDataToEvent(Data& data) {
	EventType * event_type = EventTypeStorage::getEventType("Target");
	vector<any> v;
	v.emplace_back(data.time);
	v.emplace_back(data.id);
	v.emplace_back(getTypeName(data.type));
	v.emplace_back(data.loc.x);
	v.emplace_back(data.loc.y);
	v.emplace_back(data.loc.z);
	v.emplace_back(data.dir);
	v.emplace_back(data.vel);
	return Event(event_type, v);
}
