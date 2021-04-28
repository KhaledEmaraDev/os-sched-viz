#include "model/timelinemodel.h"

#include <iostream>

TimelineModel::TimelineModel(QObject *parent) :
    QAbstractListModel(parent), m_sum(0)
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

void TimelineModel::addJob(const Job &job)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << job.duration();
    m_labels << job.label();
    setSum(sum() + job.duration());
    endInsertRows();
}

void TimelineModel::clearJobs()
{
    beginResetModel();
    m_data.clear();
    m_labels.clear();
    setSum(0);
    endResetModel();
}

int TimelineModel::sum() const {
    return m_sum;
}

void TimelineModel::setSum(const int sum) {
    if (m_sum != sum) {
        m_sum = sum;
        emit sumChanged();
    }
}

Q_INVOKABLE QVariant TimelineModel::labels() const
{
    return QVariant::fromValue(m_labels);
}
