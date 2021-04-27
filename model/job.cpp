#include <model/job.h>

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
