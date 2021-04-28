#ifndef TIMELINE_MODEL_H
#define TIMELINE_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include "model/jobmodel.h"

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(double waitingTime READ waitingTime WRITE setWaitingTime NOTIFY waitingTimeChanged)
public:
    explicit TimelineModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addJobs(const QList<Job> &jobs);
    void clearJobs(void);

    double max() const;
    void setMax(const double max);

    double waitingTime() const;
    void setWaitingTime(const double waitingTime);

    Q_INVOKABLE QVariant ids() const;
signals:
    void maxChanged();
    void waitingTimeChanged();
private:
    QList<int> m_ids;
    QList<quint32> m_data;
    QList<QString> m_labels;
    double m_max;
    double m_waitingTime;
};

#endif // TIMELINE_MODEL_H
