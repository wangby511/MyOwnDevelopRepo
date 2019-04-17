//
//  round_robin.cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>
#include <unistd.h>
#include <cassert>
using namespace std;
struct job{
    int pid;
    int arrival_time;
    int job_time;
    int execution_time;
    int stats_turnaround_time;
    int stats_waiting_time;
};

int process_run_queue(deque<job> &run_queue,
                      deque<job> &done_queue,
                      int time_quantum,
                      int &current_time){
    int time_interval = 0;
    int time1 = run_queue.front().execution_time;
    int time2 = run_queue.front().job_time;
    if(time2 - time1 <= time_quantum){
        time_interval = time2 - time1;
        current_time += time_interval;
        run_queue.front().stats_turnaround_time = current_time - run_queue.front().arrival_time;
        run_queue.front().execution_time += time_interval;
        done_queue.push_back(run_queue.front());
        run_queue.pop_front();
        for(int i = 0;i < run_queue.size();++i){
            run_queue[i].stats_waiting_time += time_interval;
        }
    }else{
        run_queue.front().execution_time += time_quantum;
        run_queue.push_back(run_queue.front());
        run_queue.pop_front();
        time_interval = time_quantum;
        for(int i = 0;i < run_queue.size() - 1;++i){
            run_queue[i].stats_waiting_time += time_interval;
        }
        current_time += time_interval;
    }
    for(int i = 0;i < run_queue.size();++i){
        run_queue[i].stats_turnaround_time = current_time - run_queue[i].arrival_time;
    }
    return time_interval;
}

int main2(){
    int time_quantum = 10;
    int current_time = 0;
    deque<job> run_queue;
    deque<job> done_queue;

    vector<int>job_times {35,25,13,22};
    int N = job_times.size();
    for(int i = 0;i < N;i++){
        job job_i;
        job_i.pid = i + 1;
        job_i.arrival_time = 0;
        job_i.job_time = job_times[i];
        job_i.execution_time = 0;
        job_i.stats_waiting_time = 0;
        job_i.stats_turnaround_time = 0;
        run_queue.push_back(job_i);
    }
    cout<<current_time<<endl;
    while(!run_queue.empty()){
        process_run_queue(run_queue,
                          done_queue,
                          time_quantum,
                          current_time);
        cout<<current_time<<endl;
    }
    for(int i = 0;i < N;i++){
        cout<<done_queue[i].pid<<","<<done_queue[i].execution_time;
        cout<<","<<done_queue[i].stats_turnaround_time<<","<<done_queue[i].stats_waiting_time<<endl;
    }
    return 0;
}
