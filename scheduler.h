#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "model/job.h"

#include <algorithm>
#include <iostream>

class Scheduler
{
public:
    Scheduler();

    Scheduler& add_job(const Job &j);
    QList<Job> sjf_nonpreemptive();
    QList<Job> sjf_preemptive();
    QList<Job> priority_preemptive();
    QList<Job> priority_nonpreemptive();
    QList<Job> fcfs();
    QList<Job> round_robin(double quantum);
    double average_waiting_time(const QList<Job>& jobs);

private:

    QList<Job> schedule_preemptive(std::function<bool(Job&, Job&)> comp_func);
    QList<Job> schedule_nonpreemptive(std::function<bool(Job&, Job&)> comp_func);

    QList<Job> wait_queue;

    static constexpr auto comp_arrival_func = [](Job &p1, Job &p2) {
        if(p1.arrivalTime() == p2.arrivalTime())
            return p1.duration() < p2.duration();
        return p1.arrivalTime() < p2.arrivalTime();
    };

    static constexpr auto comp_durtion_func = [](Job &p1, Job &p2) {
        if(p1.duration() == p2.duration())
            return p1.arrivalTime() > p2.arrivalTime();
        return p1.duration() > p2.duration();
    };

    static constexpr auto comp_priority_func = [](Job &p1, Job &p2) {
        if(p1.priority() == p2.priority())
            return p1.arrivalTime() > p2.arrivalTime();
        return p1.priority() > p2.priority();
    };

    static constexpr auto comp_quantum_func = [](Job &p1, Job &p2) {
        if(p1.quantumPriority() == p2.quantumPriority())
            return p1.arrivalTime() > p2.arrivalTime();
        return p1.quantumPriority() > p2.quantumPriority();
    };

};

#endif // SCHEDULER_H
