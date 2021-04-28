#ifndef TIMELINE_MODEL_H
#define TIMELINE_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include "model/jobmodel.h"

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)
public:
    explicit TimelineModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addJobs(const QList<Job> &jobs);
    void clearJobs(void);

    double min() const;
    void setMin(const double min);

    double max() const;
    void setMax(const double max);

    Q_INVOKABLE QVariant labels() const;
signals:
    void minChanged();
    void maxChanged();
private:
    QList<quint32> m_data;
    QList<QString> m_labels;
    double m_min;
    double m_max;
    double m_currentTime;
};

#endif // TIMELINE_MODEL_H
