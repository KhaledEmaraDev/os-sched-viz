#include "model/tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    initTable(NON_PREEMTIVE);

}

int TableModel::rowCount(const QModelIndex &) const {
    return table.size();
}

int TableModel::columnCount(const QModelIndex &) const {
    return table.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    switch (role) {
    case TableDataRole: {
        return table.at(index.row()).at(index.column());
    }
    case HeadingRole: {
        return index.row() == 0;
    }
    default: break;
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}

void TableModel::addProcess(QVector<QString> process) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    table.append(process);
    endInsertRows();

    Job j1;
    j1.setLabel(process[PROCESS_NAME]);
    j1.setArrivalTime( process[ARRIVAL_TIME].toInt());
    j1.setDuration(process[BURST_TIME].toInt());
    j1.setPriority(process[PRIORITY].toInt());
    jobs.append(j1);
    s_algorithm.schedule_alg = process[ALGORITHM];
    s_algorithm.timeSlice = process[TIME_SLICE].toInt();
    s_algorithm.isPreemtive = process[PREEMTION].toInt();

//    qDebug("%s", qUtf8Printable(j1.label()));
//    qDebug ("%i", j1.duration());
//    qDebug ("%i", j1.arrivalTime());
//    qDebug ("%i", j1.priority());
//    qDebug("%s", qUtf8Printable(s_algorithm.schedule_alg));
//    qDebug ("%i", s_algorithm.timeSlice);
//    qDebug ("%i", s_algorithm.isPreemtive);
//    qDebug ("%i", jobs.size());
}

void TableModel::removeProcess() {
    if(jobs.size() > 0)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        table.pop_back();
        endInsertRows();
        jobs.pop_back();
    }
}

void TableModel::initTable(bool priority) {
    jobs.clear();
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    table.clear();
    if(priority)
    {
        table.append({
                         "Process Name",
                         "Burst Time",
                         "Arrival Time",
                         "Priority",
                     });
    }
    else
    {
        table.append({
                         "Process Name",
                         "Burst Time",
                         "Arrival Time",
                     });
    }
    endInsertRows();
}

void TableModel::clearTable() {
    int pNum = jobs.size();
    while(pNum)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        table.pop_back();
        endInsertRows();
        pNum--;
    }
    jobs.clear();
}

QPair<algorithmInfo, QList<Job>> TableModel::getJobs()
{
    QPair<algorithmInfo, QList<Job>> pair;
    pair.first = s_algorithm;
    pair.second = jobs;

//    qDebug("%s", qUtf8Printable(pair.first.schedule_alg));
//    qDebug ("%i", pair.first.timeSlice);
//    qDebug ("%i", pair.first.isPreemtive);
//    for(int i = 0; i < pair.second.size(); i++)
//    {
//            qDebug("%s", qUtf8Printable(pair.second[i].label()));
//            qDebug ("%i", pair.second[i].duration());
//            qDebug ("%i", pair.second[i].arrivalTime());
//            qDebug ("%i", pair.second[i].priority());
//    }
    return pair;
}



