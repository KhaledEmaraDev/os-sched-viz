#ifndef JOB_MODEL_H
#define JOB_MODEL_H

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

#endif // JOB_MODEL_H
