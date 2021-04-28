#ifndef TIMELINE_MODEL_H
#define TIMELINE_MODEL_H

#include <QAbstractListModel>

#include "model/jobmodel.h"

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimelineModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addJob(const Job &job);

    Q_INVOKABLE QVariant labels() const;
private:
    QList<quint32> m_data;
    QList<QString> m_labels;
};

#endif // TIMELINE_MODEL_H
