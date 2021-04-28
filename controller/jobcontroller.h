#ifndef JOB_CONTROLLER_H
#define JOB_CONTROLLER_H

#include <QObject>

#include "model/jobmodel.h"
#include "model/timelinemodel.h"

class JobController : public QObject
{
    Q_OBJECT
public:
    explicit JobController(QObject *parent = nullptr);

    TimelineModel *timelineModel();
    TableModel *jobModel();
public slots:
    void visualize();
private:
    TimelineModel m_timeline_model;
    TableModel m_job_model;
};

#endif // JOB_CONTROLLER_H
