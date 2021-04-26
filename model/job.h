#ifndef JOB_H
#define JOB_H

#include <QAbstractTableModel>
#include <QHash>
#include <iostream>

class Job
{
public:
    Job();
    Job(const QString &label,
        const double &arrivalTime,
        const double &duration,
        const double &priority);

    int id() const;

    QString label() const;
    void setLabel(const QString &label);

    double arrivalTime() const;
    void setArrivalTime(const double &arrivalTime);

    double duration() const;
    void setDuration(const double &duration);

    double priority() const;
    void setPriority(const double &priority);

    double startTime() const;
    void setStartTime(const double &startTime);

    double endTime() const;
    friend std::ostream &operator<<(std::ostream &os, const Job &j);

    int quantumPriority() const;
    void setQuantumPriority(const int &quantumPriority);
    void increaseQuantumPriority();
    void decreaseQuantumPriority();

private:
    static int m_globalId;

    int m_id;
    QString m_label;
    double m_arrivalTime;
    double m_duration;
    double m_priority;
    double m_startTime;
    int m_quantumPriority;
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
