#include "model/timelinemodel.h"

#include <iostream>

#define EPSILON 0.01

TimelineModel::TimelineModel(QObject *parent) :
    QAbstractListModel(parent), m_max(0), m_waitingTime(0)
{
}

int TimelineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant TimelineModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Vertical)
        return QVariant();

    return m_labels[section];
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()];
    }

    return QVariant();
}

void TimelineModel::addJobs(const QList<Job> &jobs)
{
    if (jobs.isEmpty())
        return;

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + jobs.size() - 1);
    for (const Job &job: jobs) {
        if ((job.startTime() - max()) > EPSILON) {
            m_ids << -1;
            m_data << job.startTime() - max();
            m_labels << "Idle";
        }
        m_ids << job.id();
        m_data << job.duration();
        m_labels << job.label();
//        m_currentTime = job.endTime();

        setMax(job.endTime());
    }
    endInsertRows();
}

void TimelineModel::clearJobs()
{
    beginResetModel();
    m_ids.clear();
    m_data.clear();
    m_labels.clear();
    setMax(0);
    endResetModel();
}

double TimelineModel::max() const {
    return m_max;
}

void TimelineModel::setMax(const double max) {
    if (m_max != max) {
        m_max = max;
        emit maxChanged();
    }
}

double TimelineModel::waitingTime() const {
    return m_waitingTime;
}

void TimelineModel::setWaitingTime(const double waitingTime) {
    if (m_waitingTime != waitingTime) {
        m_waitingTime = waitingTime;
        emit waitingTimeChanged();
    }
}

Q_INVOKABLE QVariant TimelineModel::ids() const
{
    return QVariant::fromValue(m_ids);
}
