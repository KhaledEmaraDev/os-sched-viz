#include "controller/jobcontroller.h"

#include <QList>
#include <QPair>

#include "scheduler.h"

JobController::JobController(QObject *parent)
    : QObject(parent)
{
}

TimelineModel *JobController::timelineModel()
{
    return &m_timeline_model;
}

TableModel *JobController::jobModel()
{
    return &m_job_model;
}

void JobController::visualize()
{
    Scheduler sc;
    QPair<algorithmInfo, QList<Job>> input = m_job_model.getJobs();
    // temp vaildation
    if(input.second.isEmpty())
        return;

    QList<Job> output;

    for (Job &job: input.second) {
        sc.add_job(job);
    }

    if (input.first.schedule_alg == "FCFS") {
        output = sc.fcfs();
    } else if (input.first.schedule_alg == "SJF") {
        if (input.first.isPreemtive) {
            output = sc.sjf_preemptive();
        } else {
            output = sc.sjf_nonpreemptive();
        }
    } else if (input.first.schedule_alg == "Priority") {
        if (input.first.isPreemtive) {
            output = sc.priority_preemptive();
        } else {
            output = sc.priority_nonpreemptive();
        }
    } else {
        output = sc.round_robin(input.first.timeSlice);
    }

    m_timeline_model.clearJobs();
    m_timeline_model.addJobs(output);
    m_timeline_model.setWaitingTime(sc.average_waiting_time(output));
}
