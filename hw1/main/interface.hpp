//https://github.com/semerdzhiev/sdp-2021-22/blob/main/tests/1/src/interface.h
#pragma once


enum class ResourceType {
	banana,
	schweppes,
};

struct Client {
	int arriveMinute;
	int banana;
	int schweppes;
	int maxWaitTime;
};

struct ActionHandler {
    
	virtual void onWorkerSend(int minute, ResourceType resource) = 0;

	virtual void onWorkerBack(int minute, ResourceType resource) = 0;

	virtual void onClientDepart(int index, int minute, int banana, int schweppes) = 0;
};

struct Store {

	virtual void init(int workerCount, int startBanana, int startSchweppes) = 0;
	
	virtual void setActionHandler(ActionHandler *handler) = 0;

	virtual void addClients(const Client *clients, int count) = 0;

	virtual void advanceTo(int minute) = 0;

	virtual int getBanana() const = 0;

	virtual int getSchweppes() const = 0;

	virtual ~Store() {}
};

Store *createStore();