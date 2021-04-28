#include "model/timelinemodel.h"

#include <iostream>

TimelineModel::TimelineModel(QObject *parent) :
    QAbstractListModel(parent), m_min(0), m_max(0), m_currentTime(0)
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

    if (rowCount() == 0)
        setMin(jobs[0].startTime());

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + jobs.size() - 1);
    for (const Job &job: jobs) {
        if (m_currentTime < job.startTime()) {
            m_data << job.startTime() - m_currentTime;
            m_labels << "Idle";
        }
        m_data << job.duration();
        m_labels << job.label();
        m_currentTime = job.endTime();

        setMax(m_currentTime);
    }
    endInsertRows();
}

void TimelineModel::clearJobs()
{
    beginResetModel();
    m_data.clear();
    m_labels.clear();
    setMax(0);
    endResetModel();
}

double TimelineModel::min() const {
    return m_max;
}

void TimelineModel::setMin(const double min) {
    if (m_max != min) {
        m_max = min;
        emit maxChanged();
    }
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

Q_INVOKABLE QVariant TimelineModel::labels() const
{
    return QVariant::fromValue(m_labels);
}
