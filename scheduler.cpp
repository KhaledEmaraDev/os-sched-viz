#include "scheduler.h"

Scheduler::Scheduler()
{

}

Scheduler &Scheduler::add_job(const Job &j)
{
    wait_queue.append(j);
    return *this;
}

QList<Job> Scheduler::sjf_preemptive()
{
    return schedule_preemptive(comp_durtion_func);
}

QList<Job> Scheduler::sjf_nonpreemptive()
{
    return schedule_nonpreemptive(comp_durtion_func);
}

QList<Job> Scheduler::priority_preemptive()
{
    return schedule_preemptive(comp_priority_func);
}

QList<Job> Scheduler::priority_nonpreemptive()
{
    return schedule_nonpreemptive(comp_priority_func);
}

QList<Job> Scheduler::fcfs()
{

}

QList<Job> Scheduler::round_robin(qint32 quantum)
{

}

QList<Job> Scheduler::schedule_preemptive(std::function<bool (Job &, Job &)> comp_func)
{
    std::sort(wait_queue.begin(), wait_queue.end(), comp_arrival_func);

    quint32 last_duration = 0;
    quint32 last_start_time = 0;
    quint32 current_time = 0;

    QList<Job> output_list;
    QList<Job> ready_queue;
    auto wait_it = wait_queue.begin();
    Job current_job;
    Job last_job;

    while(wait_it != wait_queue.end() ||
          ready_queue.size()) {

        if(output_list.size()) {
            last_job = output_list.back();
            if(last_job.endTime() > current_time) {
                last_job.setDuration(last_job.endTime() - current_time);
                ready_queue.append(last_job);
                std::push_heap(ready_queue.begin(), ready_queue.end(), comp_func);
                last_duration = output_list.back().duration() - last_job.duration();
                output_list.back().setDuration(last_duration);
            }
        }

        while (wait_it != wait_queue.end() &&
               wait_it->arrivalTime() <= current_time) {
            ready_queue.append(*wait_it);
            std::push_heap(ready_queue.begin(), ready_queue.end(), comp_func);
            wait_it++;
        }

        if(ready_queue.size()) {
            std::pop_heap(ready_queue.begin(), ready_queue.end(), comp_func);
            current_job = ready_queue.back();
            ready_queue.pop_back();
        }
        else {
            current_job = *wait_it;
            wait_it++;
        }

        if (output_list.size() &&
                current_job.id() == output_list.back().id()) {
            output_list.back().setDuration(
                        output_list.back().duration() + current_job.duration());
            last_start_time = output_list.back().startTime();
            last_duration = output_list.back().duration();
        }
        else {
            last_start_time =std::max(last_start_time + last_duration,
                                      current_job.arrivalTime());
            last_duration = current_job.duration();
            current_job.setStartTime(last_start_time);
            output_list.append(current_job);
        }

        current_time = wait_it != wait_queue.end() ?
                    wait_it->arrivalTime() :
                    last_start_time + last_duration;
    }
    return output_list;
}

QList<Job> Scheduler::schedule_nonpreemptive(std::function<bool (Job &, Job &)> comp_func)
{

    std::sort(wait_queue.begin(), wait_queue.end(), comp_arrival_func);

    quint32 last_duration = 0;
    quint32 last_start_time = 0;
    quint32 current_time = 0;

    QList<Job> output_list;
    QList<Job> ready_queue;
    auto wait_it = wait_queue.begin();
    Job current_job;

    while(wait_it != wait_queue.end() ||
          ready_queue.size()) {
        while (wait_it != wait_queue.end() &&
               wait_it->arrivalTime() <= current_time) {
            ready_queue.append(*wait_it);
            std::push_heap(ready_queue.begin(), ready_queue.end(), comp_func);
            wait_it++;
        }

        if(ready_queue.size()) {
            std::pop_heap(ready_queue.begin(), ready_queue.end(), comp_func);
            current_job = ready_queue.back();
            ready_queue.pop_back();
        }
        else {
            current_job = *wait_it;
            wait_it++;
        }

        last_start_time =std::max(last_start_time + last_duration,
                                  current_job.arrivalTime());
        last_duration = current_job.duration();
        current_time = last_start_time + last_duration;
        current_job.setStartTime(last_start_time);
        output_list.append(current_job);
    }
    return output_list;
}

double Scheduler::average_waiting_time(const QList<Job> &jobs)
{
    QHash<quint32, QList<Job>> jobs_map;
    for(const Job& job: jobs)
        if(jobs_map.contains(job.id()))
            jobs_map[job.id()].append(job);
        else
            jobs_map[job.id()] = QList({job});

    double waiting_time = 0;
    qint32 last_end_time = 0;
    for(const auto& jobs : qAsConst(jobs_map)) {
        waiting_time += jobs[0].startTime() - jobs[0].arrivalTime();
        last_end_time = jobs[0].endTime();
        for(int i = 1; i < jobs.size(); i++) {
            waiting_time += jobs[i].startTime() - last_end_time;
            last_end_time = jobs[i].endTime();
        }
    }
    return waiting_time / (double) jobs_map.size();
}
