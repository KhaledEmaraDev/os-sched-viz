#include "model/timeline.h"

#include <QRandomGenerator>

TimelineModel::TimelineModel(QObject *parent) :
    QAbstractListModel(parent)
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
    endInsertRows();
}

Q_INVOKABLE QVariant TimelineModel::labels() const
{
    return QVariant::fromValue(m_labels);
}
