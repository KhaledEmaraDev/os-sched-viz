#ifndef TIMELINE_MODEL_H
#define TIMELINE_MODEL_H

#include <QAbstractListModel>

#include "model/jobmodel.h"

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int sum READ sum WRITE setSum NOTIFY sumChanged)
public:
    explicit TimelineModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addJob(const Job &job);
    void clearJobs(void);

    int sum() const;
    void setSum(const int sum);

    Q_INVOKABLE QVariant labels() const;
signals:
    void sumChanged();
private:
    QList<quint32> m_data;
    QList<QString> m_labels;
    int m_sum;
};

#endif // TIMELINE_MODEL_H
