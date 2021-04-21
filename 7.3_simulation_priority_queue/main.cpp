#include <iostream>
#include "Priority_queue.h"
#include "Link_queue.h"

class simulator{
    int noOfServer; //服务台个数
    int arriveLow; //到达时间上界
    int arriveHigh; //到达时间下界
    int serviceTimeLow; //服务时间上界
    int serviceTimeHigh; //服务时间下界
    int customNum; //模拟的顾客数

    struct eventT{
        int time;
        int type; //事件发生类型：0为到达，1为离开
        bool operator<(const eventT &e)const {return time < e.time;}//运算符重载，用于优先级队列的比较中
    };

public:
    simulator();
    int avgWaitTime();

};

simulator::simulator() {
    cout << "please input the number of the servers: ";
    cin >> noOfServer;
    cout << "please input the span of the arrival time: ";
    cin >> arriveLow >> arriveHigh;
    cout << "please input the span of the service time: ";
    cin >> serviceTimeLow >> serviceTimeHigh;
    cout << "please input the number of the customers: ";
    cin >> customNum;

    srand(time(NULL));
}

int simulator::avgWaitTime() {
    int serverBusy = 0;
    int currentTime;
    int totalWaitTime;
    linkQueue<eventT> waitQueue;
    priorityQueue<eventT> eventQueue;

    eventT currentEvent;

    //生成初始的事件队列
    int i;
    currentEvent.time = 0;
    currentEvent.type = 0;
    for (i = 0; i < customNum; ++i) {
        currentEvent.time += arriveLow + (arriveHigh - arriveLow + 1) * rand() / (RAND_MAX + 1);
        eventQueue.enQueue(currentEvent);
    }

    //模拟过程
    while (!eventQueue.isEmpty()){
        currentEvent = eventQueue.deQueue();
        currentTime = currentEvent.time;
        switch (currentEvent.type) {
            // 处理到达事件
            case 0:
                if (serverBusy != noOfServer){
                    ++serverBusy;
                    currentEvent.time += serviceTimeLow+ (serviceTimeHigh - serviceTimeLow + 1) * rand() / (RAND_MAX + 1);
                    currentEvent.type = 1;
                    eventQueue.enQueue(currentEvent);
                } else waitQueue.enQueue(currentEvent);
                break;
            case 1: //处理离开事件
                if (!waitQueue.isEmpty()){
                    currentEvent = waitQueue.deQueue();
                    totalWaitTime += currentTime - currentEvent.time;
                    currentEvent.time += serviceTimeLow+ (serviceTimeHigh - serviceTimeLow + 1) * rand() / (RAND_MAX + 1);
                    currentEvent.type = 1;
                    eventQueue.enQueue(currentEvent);
                } else --serverBusy;
        }
    }
    return totalWaitTime / customNum;
}
int main() {
    simulator sim;
    int avg;
    for (int i = 0; i < 10; ++i) {
        avg += sim.avgWaitTime();
    }
    cout << "平均等待时间：" << avg / 10 << endl;
    return 0;
}
