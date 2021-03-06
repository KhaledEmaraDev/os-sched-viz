#include "model/jobmodel.h"

#include <iostream>
#include <QDebug>

int Job::m_globalId = 0;

Job::Job()
    : m_id( this->m_globalId), m_label(""), m_arrivalTime(0), m_duration(0),
      m_priority(0)
{
    this->m_startTime = 0;
    this->m_quantumPriority = 0;
    this->m_globalId++;
}

Job::Job(const QString &label,
         const double &arrivalTime,
         const double &duration,
         const double &priority)
    : m_id(this->m_globalId),
      m_label(label),
      m_arrivalTime(arrivalTime),
      m_duration(duration),
      m_priority(priority)
{
    this->m_startTime = 0;
    this->m_quantumPriority = 0;
    this->m_globalId++;
}

int Job::id() const
{
    return m_id;
}
void Job::setId(int id)
{
    m_id = id;
}

QString Job::label() const
{
    return m_label;
}
void Job::setLabel(const QString &label)
{
    m_label = label;
}

double Job::arrivalTime() const
{
    return m_arrivalTime;
}
void Job::setArrivalTime(const double &arrivalTime)
{
    m_arrivalTime = arrivalTime;
}

double Job::duration() const
{
    return m_duration;
}
void Job::setDuration(const double &duration)
{
    m_duration = duration;
}

double Job::priority() const
{
    return m_priority;
}
void Job::setPriority(const double &priority)
{
    m_priority = priority;
}

double Job::startTime() const
{
    return m_startTime;
}
void Job::setStartTime(const double &startTime)
{
    m_startTime = startTime;
}

double Job::endTime() const
{
    return m_startTime + m_duration;
}

int Job::quantumPriority() const
{
    return m_quantumPriority;
}

void Job::setQuantumPriority(const int &quantumPriority)
{
    m_quantumPriority = quantumPriority;
}

void Job::increaseQuantumPriority()
{
    m_quantumPriority++;
}

void Job::decreaseQuantumPriority()
{
    m_quantumPriority--;
}

std::ostream &operator<<(std::ostream &os, const Job &j) {
    os << "Job Id: " << j.id() << "\n"
       << "Job name: " << j.label().toStdString() << "\n"
       << "Arrival time: " << j.arrivalTime() << "\n"
       << "Start time: " << j.startTime() << "\n"
       << "Durtion: " << j.duration() << "\n";
    return os;
}

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
    QString label = process[PROCESS_NAME];
    double arrivalTime = process[ARRIVAL_TIME].toDouble();
    double durtion = process[BURST_TIME].toDouble();
    double priority = process[PRIORITY].toDouble();

    QString schedule_alg = process[ALGORITHM];
    double timeSlice = process[TIME_SLICE].toDouble();
    bool isPreemtive = process[PREEMTION].toInt();

//    qDebug() << label << "\n" << arrivalTime << "\n" << durtion << "\n"
//                << priority << "\n" << schedule_alg << "\n" << timeSlice
//                << "\n" << isPreemtive << "\n\n\n";

    if(arrivalTime < 0 || durtion <= 0)
        return;
    if(schedule_alg == "Round Robin" && timeSlice <= 0)
        return;

    jobs.append(Job(label, arrivalTime, durtion, priority));

    s_algorithm.schedule_alg = schedule_alg;
    s_algorithm.timeSlice = timeSlice;
    s_algorithm.isPreemtive = isPreemtive;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    table.append(process);
    endInsertRows();

    //    qDebug("%s", qUtf8Printable(j1.label()));
    //    qDebug ("%i", j1.duration());
    //    qDebug ("%i", j1.arrivalTime());
    //    qDebug ("%i", j1.priority());
    //    qDebug("%s", qUtf8Printable(s_algorithm.schedule_alg));
    //    qDebug ("%i", s_algorithm.timeSlice);
    //    qDebug ("%i", s_algorithm.isPreemtive);
    //    qDebug ("%i", jobs.size());
}

void TableModel::changeAlgorithm(QVector<QString> algorithm) {

    QString schedule_alg = algorithm[0];
    double timeSlice = algorithm[1].toDouble();
    bool isPreemtive = algorithm[2].toInt();

    if(schedule_alg == "Round Robin" && timeSlice <= 0)
        return;

    s_algorithm.schedule_alg = schedule_alg;
    s_algorithm.timeSlice = timeSlice;
    s_algorithm.isPreemtive = isPreemtive;
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



