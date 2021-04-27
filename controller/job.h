#ifndef JOB_CONTROLLER_H
#define JOB_CONTROLLER_H

#include <QObject>

#include "model/timeline.h"
#include "model/tablemodel.h"

class JobController : public QObject
{
    Q_OBJECT
public:
    explicit JobController(QObject *parent = nullptr);

    TimelineModel *timelineModel();
    TableModel *tableModel();
public slots:
    void visualize();
private:
    TimelineModel m_timeline_model;
    TableModel m_table_model;
};

#endif // JOB_CONTROLLER_H
