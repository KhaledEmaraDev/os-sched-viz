#ifndef JOB_MODEL_H
#define JOB_MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QPair>

class Job
{
public:
    Job();
    Job(const QString &label,
        const double &arrivalTime,
        const double &duration,
        const double &priority);

    int id() const;
    void setId(int id);

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

typedef struct{
    QString schedule_alg;
    qint32 timeSlice;
    bool isPreemtive;
} algorithmInfo;

enum JOB_PARAM{
    PROCESS_NAME,
    BURST_TIME,
    ARRIVAL_TIME,
    PRIORITY,
    TIME_SLICE,
    PREEMTION,
    ALGORITHM
};

class TableModel : public QAbstractTableModel {
    Q_OBJECT
    enum TableRoles {
        TableDataRole = Qt::UserRole + 1,
        HeadingRole
    };
    enum JOB_PREEMITION{
        NON_PREEMTIVE,
        PREEMTIVE
    };
public:
    explicit TableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void initTable(bool priority);

    Q_INVOKABLE void addProcess(QVector<QString> process);

    Q_INVOKABLE void removeProcess();

    Q_INVOKABLE void clearTable();

    QPair<algorithmInfo, QList<Job>> getJobs();

private:
    QVector<QVector<QString>> table;
    QList<Job> jobs;
    algorithmInfo s_algorithm;
};

#endif // JOB_MODEL_H





