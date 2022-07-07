//https://github.com/semerdzhiev/sdp-2021-22/blob/main/tests/1/src/implementation.cpp
#include <iostream>
#include <cassert>
#include "interface.hpp"
#include "queue.hpp"
#include "dynamicArray.hpp"


struct ActionInStore : public ActionHandler {

	void onWorkerSend(int minute, ResourceType resource) override 
		{
			std::cout << "W " << minute << " ";

			switch(resource)
			{
				case ResourceType:: banana : std::cout << "banana" << std::endl; break;

				case ResourceType:: schweppes : std::cout << "schweppes" << std::endl; break;
			}
		}
	
		void onWorkerBack(int minute, ResourceType resource) override 
		{
			std::cout << "D " << minute << " ";

			switch(resource)
			{
				case ResourceType:: banana : std::cout << "banana" << std::endl; break;

				case ResourceType:: schweppes : std::cout << "schweppes" << std::endl; break;
			}
		}

		void onClientDepart(int index, int minute, int banana, int schweppes) override 
		{
			std::cout << index << " " << minute << " " <<banana << " " << schweppes << std::endl;
		}
};

struct Worker {
	int workerSendTime = 0;
	ResourceType type;

	Worker() = default;
	
	Worker(int _workerSendTime, ResourceType _type)
	{
		workerSendTime = _workerSendTime;
		type = _type;
	}
};

class MyStore : public Store
{
	private:
		int time = 0;

		int bananaInStore{};
		int schweppesInStore{};

		int numberOfWorkersInStore{};
		queue<Worker> workersSend;

		queue<Client> clientsComingInStore;

		DynamicArray<Client> clientsWaitingInStore;

		ActionInStore *actionHandler = nullptr;
	

	public:
		MyStore() = default;
		MyStore(const MyStore& other) = delete;
		MyStore& operator=(const MyStore& other) = delete;
		~MyStore()
		{
			clientsComingInStore.~queue();
			clientsWaitingInStore.~DynamicArray();

			workersSend.~queue();

			if(actionHandler != nullptr) 
			{
				delete actionHandler;
				actionHandler = nullptr;
			}

			time = 0;
			bananaInStore = 0;
			schweppesInStore = 0;
			numberOfWorkersInStore = 0;
		}


		int getBanana() const override { return bananaInStore; }
		int getSchweppes() const override { return schweppesInStore; }

		int getNumberOfWorkersInStore() const { return numberOfWorkersInStore; }

		void init(int workerCount, int startBanana, int startSchweppes) override 
		{
			numberOfWorkersInStore = workerCount;
			schweppesInStore = startSchweppes;
			bananaInStore = startBanana;
		}

		void addClients(const Client *clients, int count) override 
		{
			for (int i = 0; i < count; ++i)
			{
				clientsComingInStore.enqueue(clients[i]);
			}
		}

		//https://www.geeksforgeeks.org/dynamic-_cast-in-cpp/
		void setActionHandler(ActionHandler *handler) override
		{
			actionHandler = dynamic_cast<ActionInStore *>(handler);
			//actionHandler = handler;
		}

		void addWorkerInWorkerQueue(int minute, ResourceType resource)
		{
			switch(resource)
			{
				case ResourceType:: banana : {
									Worker worker(minute, ResourceType::banana);
									workersSend.enqueue(worker); break; }
				
				case ResourceType:: schweppes : {
									Worker worker(minute, ResourceType::schweppes);
									workersSend.enqueue(worker); break; }
			}
		}

		void advanceTo(int minute) override 
		{
			int clientIndex = 0;
			
			while (time != minute)
			{
				//when client arrives and the store has enough products to serve the client
				if(clientsComingInStore.front().arriveMinute == time && clientsComingInStore.front().banana <= getBanana() && clientsComingInStore.front().schweppes <= getSchweppes())
				{
					actionHandler->onClientDepart(clientIndex, time, clientsComingInStore.front().banana, clientsComingInStore.front().schweppes);

					bananaInStore -= clientsComingInStore.front().banana;
					schweppesInStore -= clientsComingInStore.front().schweppes;

					clientsComingInStore.dequeue();

					clientIndex++;
				}

				//conditions for sending worker in order to load product
				if(clientsComingInStore.front().arriveMinute == time && !workersSend.empty() && workersSend.front().workerSendTime + 60 <= clientsComingInStore.front().arriveMinute + clientsComingInStore.front().maxWaitTime)
				{
					if(clientsComingInStore.front().banana > getBanana() && clientsComingInStore.front().schweppes > getSchweppes() && getNumberOfWorkersInStore())
					{
						if(workersSend.front().type == ResourceType::banana) 
						{
							actionHandler->onWorkerSend(time, ResourceType::schweppes);
							numberOfWorkersInStore--;
							addWorkerInWorkerQueue(time, ResourceType::schweppes);
						}
						else
						{
							actionHandler->onWorkerSend(time, ResourceType::banana);
							numberOfWorkersInStore--;
							addWorkerInWorkerQueue(time, ResourceType::banana);
						}
					}
					else if(clientsComingInStore.front().banana > getBanana() && clientsComingInStore.front().schweppes <= getSchweppes() && getNumberOfWorkersInStore())
					{
						if(workersSend.front().type == ResourceType::schweppes)
						{
							actionHandler->onWorkerSend(time, ResourceType::banana);
							numberOfWorkersInStore--;
							addWorkerInWorkerQueue(time, ResourceType::banana);
						}
					}
					else if(clientsComingInStore.front().banana <= getBanana() && clientsComingInStore.front().schweppes > getSchweppes() && getNumberOfWorkersInStore())
					{
						if(workersSend.front().type == ResourceType::banana)
						{
							actionHandler->onWorkerSend(time, ResourceType::schweppes);
							numberOfWorkersInStore--;
							addWorkerInWorkerQueue(time, ResourceType::schweppes);
						}
					}
					clientsWaitingInStore.push_back(clientsComingInStore.front());
					clientsComingInStore.dequeue();

				}
				
				else 
				{
					if(clientsComingInStore.front().arriveMinute == time && clientsComingInStore.front().banana > getBanana() && clientsComingInStore.front().schweppes > getSchweppes() && getNumberOfWorkersInStore())
					{
						if(getNumberOfWorkersInStore() == 1)
						{
							if((clientsComingInStore.front().banana >= clientsComingInStore.front().schweppes))
							{
								actionHandler->onWorkerSend(time, ResourceType::banana);
								numberOfWorkersInStore--;
								addWorkerInWorkerQueue(time, ResourceType::banana);
							}
							else
							{
								actionHandler->onWorkerSend(time, ResourceType::schweppes);
								numberOfWorkersInStore--;
								addWorkerInWorkerQueue(time, ResourceType:: schweppes);
							}
						}
						
						else if(getNumberOfWorkersInStore() > 1)
						{
							actionHandler->onWorkerSend(time, ResourceType::banana);
							numberOfWorkersInStore--;
							addWorkerInWorkerQueue(time, ResourceType::banana);

							actionHandler->onWorkerSend(time, ResourceType::schweppes);
							numberOfWorkersInStore--;
							addWorkerInWorkerQueue(time, ResourceType:: schweppes);
						}

						clientsWaitingInStore.push_back(clientsComingInStore.front());
						clientsComingInStore.dequeue();
					}

					
					if(clientsComingInStore.front().arriveMinute == time && clientsComingInStore.front().banana > getBanana() && clientsComingInStore.front().schweppes <= getSchweppes() && getNumberOfWorkersInStore())
					{
						actionHandler->onWorkerSend(time, ResourceType::banana);
						numberOfWorkersInStore--;
						addWorkerInWorkerQueue(time, ResourceType:: banana);
						
						clientsWaitingInStore.push_back(clientsComingInStore.front());
						clientsComingInStore.dequeue();

					}
					if(clientsComingInStore.front().arriveMinute == time && clientsComingInStore.front().banana <= getBanana() && clientsComingInStore.front().schweppes > getSchweppes() && getNumberOfWorkersInStore())
					{
						
						actionHandler->onWorkerSend(time, ResourceType::schweppes);
						numberOfWorkersInStore--;
						addWorkerInWorkerQueue(time, ResourceType:: schweppes);
						
						clientsWaitingInStore.push_back(clientsComingInStore.front());
						clientsComingInStore.dequeue();
					}
				}

				// when there is no worker in the store and clients arrives
				if(clientsComingInStore.front().arriveMinute == time && getNumberOfWorkersInStore() == 0 && clientsComingInStore.front().banana > getBanana() && clientsComingInStore.front().schweppes > getSchweppes())
				{
					clientsWaitingInStore.push_back(clientsComingInStore.front());
					clientsComingInStore.dequeue();
				}
				
				//when worker comes back to load product
				if(!workersSend.empty() && workersSend.front().workerSendTime + 60 <= time)
				{
					if(workersSend.front().type == ResourceType::banana)
					{
						actionHandler->onWorkerBack(time, ResourceType::banana);
						numberOfWorkersInStore++;
						bananaInStore += 100;
					}
					
					else if(workersSend.front().type == ResourceType::schweppes)
					{
						actionHandler->onWorkerBack(time, ResourceType::schweppes);
						numberOfWorkersInStore++;
						schweppesInStore += 100;
					}
					workersSend.dequeue();

					if(!clientsWaitingInStore.empty() && clientsWaitingInStore.front().banana <= getBanana() && clientsWaitingInStore.front().schweppes <= getSchweppes())
					{
						actionHandler->onClientDepart(clientIndex, time, clientsWaitingInStore.front().banana, clientsWaitingInStore.front().schweppes);

						bananaInStore -= clientsComingInStore.front().banana;
						schweppesInStore -= clientsComingInStore.front().schweppes;

						clientsWaitingInStore.pop_front();
						clientIndex++;
					}
				}
				
				//when there is no worker/s in the store and client departs
				if(workersSend.empty() && !clientsWaitingInStore.empty() && clientsWaitingInStore.front().arriveMinute + clientsWaitingInStore.front().maxWaitTime == time && clientsComingInStore.front().banana > getBanana() && clientsComingInStore.front().schweppes > getSchweppes())
				{
					actionHandler->onClientDepart(clientIndex, time, bananaInStore, schweppesInStore);
					
					bananaInStore = 0;
					schweppesInStore = 0;

					clientsWaitingInStore.pop_front();
					clientIndex++;
				}

				// conditions for departing client/s
				if(!clientsWaitingInStore.empty())
				{
					if(clientsWaitingInStore.size() == 1 && clientsWaitingInStore.front().arriveMinute + clientsWaitingInStore.front().maxWaitTime == time)
					{
						if(clientsWaitingInStore.front().banana <= getBanana() && clientsWaitingInStore.front().schweppes <= getSchweppes())
						{
							actionHandler->onClientDepart(0, time, clientsWaitingInStore.front().banana, clientsWaitingInStore.front().schweppes);
							bananaInStore -= clientsWaitingInStore.front().banana;
							schweppesInStore -= clientsWaitingInStore.front().schweppes;
						}
						
						else if(clientsWaitingInStore.front().banana > getBanana() && clientsWaitingInStore.front().schweppes <= getSchweppes())
						{
							actionHandler->onClientDepart(clientIndex, time, bananaInStore, clientsWaitingInStore.front().schweppes);
							bananaInStore = 0;
							schweppesInStore -= clientsWaitingInStore.front().schweppes;
						}
						
						else if(clientsWaitingInStore.front().banana <= getBanana() && clientsWaitingInStore.front().schweppes > getSchweppes())
						{
							actionHandler->onClientDepart(clientIndex, time, clientsWaitingInStore.front().banana, schweppesInStore);
							bananaInStore -= clientsWaitingInStore.front().banana;
							schweppesInStore = 0;
						}
						
						else if(clientsWaitingInStore.front().banana > getBanana() && clientsWaitingInStore.front().schweppes > getSchweppes())
						{
							actionHandler->onClientDepart(clientIndex, time, bananaInStore, schweppesInStore);
							bananaInStore = 0;
							schweppesInStore = 0;
						}
						clientsWaitingInStore.pop_front();
						clientIndex++;
					
					}
				

					else if(clientsWaitingInStore.size() > 1)
					{
						for(int i = 0; i < clientsWaitingInStore.size() - 1; ++i)
						{
							for(int j = i + 1; j < clientsWaitingInStore.size(); ++j)
							{
								if(clientsWaitingInStore[i].arriveMinute + clientsWaitingInStore[i].maxWaitTime > clientsWaitingInStore[j].arriveMinute + clientsWaitingInStore[j].maxWaitTime
								&& clientsWaitingInStore[j].arriveMinute + clientsWaitingInStore[j].maxWaitTime == time)
								{
									if(clientsWaitingInStore[j].banana <= getBanana() && clientsWaitingInStore[j].schweppes <= getSchweppes())
									{
										actionHandler->onClientDepart(j, time, clientsWaitingInStore[j].banana, clientsWaitingInStore[j].schweppes);

										bananaInStore -= clientsWaitingInStore[j].banana;
										schweppesInStore -= clientsWaitingInStore[j].schweppes;

										clientsWaitingInStore.deleteAt(j);
									}

									else if(clientsWaitingInStore[j].banana <= getBanana() && clientsWaitingInStore[j].schweppes > getSchweppes())
									{
										actionHandler->onClientDepart(j, time, clientsWaitingInStore[j].banana, schweppesInStore);

										bananaInStore -= clientsWaitingInStore[j].banana;
										schweppesInStore = 0;

										clientsWaitingInStore.deleteAt(j);
									}

									else if(clientsWaitingInStore[j].banana > getBanana() && clientsWaitingInStore[j].schweppes <= getSchweppes())
									{
										actionHandler->onClientDepart(j, time, bananaInStore, clientsWaitingInStore[j].schweppes);

										bananaInStore = 0;
										schweppesInStore -= clientsWaitingInStore[j].schweppes;

										clientsWaitingInStore.deleteAt(j);
									}
									
									
									else if(clientsWaitingInStore[j].banana > getBanana() && clientsWaitingInStore[j].schweppes > getSchweppes())
									{
										actionHandler->onClientDepart(j, time, bananaInStore, schweppesInStore);

										bananaInStore = 0;
										schweppesInStore = 0;

										clientsWaitingInStore.deleteAt(j);
									}
								}
								
								else if(clientsWaitingInStore[i].arriveMinute + clientsWaitingInStore[i].maxWaitTime <= clientsWaitingInStore[j].arriveMinute + clientsWaitingInStore[j].maxWaitTime
								&& clientsWaitingInStore[i].arriveMinute + clientsWaitingInStore[i].maxWaitTime == time)
								{
									if(clientsWaitingInStore[i].banana <= getBanana() && clientsWaitingInStore[i].schweppes <= getSchweppes())
									{
										actionHandler->onClientDepart(i, time, clientsWaitingInStore[i].banana, clientsWaitingInStore[i].schweppes);

										bananaInStore -= clientsWaitingInStore[i].banana;
										schweppesInStore -= clientsWaitingInStore[i].schweppes;

										clientsWaitingInStore.deleteAt(i);
									}

									else if(clientsWaitingInStore[i].banana <= getBanana() && clientsWaitingInStore[i].schweppes > getSchweppes())
									{
										actionHandler->onClientDepart(i, time, clientsWaitingInStore[i].banana, schweppesInStore);

										bananaInStore -= clientsWaitingInStore[i].banana;
										schweppesInStore = 0;

										clientsWaitingInStore.deleteAt(i);
									}

									else if(clientsWaitingInStore[i].banana > getBanana() && clientsWaitingInStore[i].schweppes <= getSchweppes())
									{
										actionHandler->onClientDepart(i, time, bananaInStore, clientsWaitingInStore[i].schweppes);

										bananaInStore = 0;
										schweppesInStore -= clientsWaitingInStore[i].schweppes;

										clientsWaitingInStore.deleteAt(i);
									}
									
									// може и само else
									else if(clientsWaitingInStore[i].banana > getBanana() && clientsWaitingInStore[i].schweppes > getSchweppes())
									{
										actionHandler->onClientDepart(i, time, bananaInStore, schweppesInStore);

										bananaInStore = 0;
										schweppesInStore = 0;

										clientsWaitingInStore.deleteAt(i);
									}
								}
							}
						}
					}
				}

				time++;
			}
		}
};

Store *createStore() 
{
	return new MyStore();
}


int main()
{
	Store* mrazMag = createStore();
	ActionInStore* action = new ActionInStore();
	mrazMag->setActionHandler(action);

	int workersCount, clientsCount;

	std::cout << "Workers: ";
	std::cin >> workersCount;
	
	std::cout << "ClientsCount: ";
	std::cin >> clientsCount;

	std::cout<< std::endl;

	mrazMag->init(workersCount, 0, 0);  //at the beginning the store's products are 0.
	Client* clientsInStore = new Client[clientsCount];

	for (int i = 0; i < clientsCount; ++i)
	{
		std::cout << "Client: " << i << std::endl;

		int clientArriveMinute, clientBanana, clientSchweppes, clientMaxWaitTime;

		std::cout << "clientArriveMinute: ";
		std::cin >> clientArriveMinute;

		std::cout << "clientBanana: ";
		std::cin >> clientBanana;
		
		std::cout<<"clientSchweppes: ";
		std::cin >> clientSchweppes;
		
		std::cout<<"clientMaxWaitTime: ";
		std::cin >> clientMaxWaitTime;

		std::cout << std::endl;

		Client cl{clientArriveMinute, clientBanana, clientSchweppes, clientMaxWaitTime};
		clientsInStore[i] = cl;
	}
	mrazMag->addClients(clientsInStore, clientsCount);
	mrazMag->advanceTo(500);

	return 0;
}