#ifndef JOB_H
#define JOB_H

#include <QAbstractTableModel>
#include <QHash>

class Job
{
public:
    Job();
    Job(const QString &label,
        const quint32 &arrivalTime,
        const quint32 &duration,
        const quint32 &priority);

    quint32 id() const;

    QString label() const;
    void setLabel(const QString &label);

    quint32 arrivalTime() const;
    void setArrivalTime(const quint32 &arrivalTime);

    quint32 duration() const;
    void setDuration(const quint32 &duration);

    quint32 priority() const;
    void setPriority(const quint32 &priority);

    quint32 startTime() const;
    void setStartTime(const quint32 &startTime);

    quint32 endTime() const;
    friend std::ostream &operator<<(std::ostream &os, const Job &j);

    quint32 quantumPriority() const;
    void setQuantumPriority(const quint32 &quantumPriority);

private:
    static quint32 m_globalId;

    quint32 m_id;
    QString m_label;
    quint32 m_arrivalTime;
    quint32 m_duration;
    quint32 m_priority;
    quint32 m_startTime;
    quint32 m_quantumPriority;
};

class JobModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum JobRoles {
        LabelRole = Qt::UserRole + 1,
        StartTimeRole,
        DurationRole,
        PriorityRole
    };

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addJob(const Job &job);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Job> m_jobs;
};

#endif // JOB_H
