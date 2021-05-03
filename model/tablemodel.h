#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <iostream>
#include <QQmlApplicationEngine>

#include "model/job.h"

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


private:
    QVector<QVector<QString>> table;
    QList<Job> jobs;
    algorithmInfo s_algorithm;
};
#endif





