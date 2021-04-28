#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QDebug>

#include "controller/jobcontroller.h"
#include "model/jobmodel.h"
#include "scheduler.h"

void test_algorthim() {
    Scheduler sc;

    Job j1("A", 1, 7,  0);
    Job j3("B", 2, 4,  0);
    Job j4("C", 3, 1,  0);
    Job j2("D", 4, 2,  0);

    QList<Job> input = {j1, j2, j3, j4};
    sc.add_job(j1).add_job(j2).add_job(j3).add_job(j4);

    QList<Job> output = sc.fcfs();

    std::cout << "Input Jobs\n";
    for(Job& j : input)
        std::cout << j << std::endl;

    std::cout << "Output Jobs\n";
    for(Job& j : output)
        std::cout << j << std::endl;
    std::cout << sc.average_waiting_time(output) << std::endl;
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    //    test_algorthim();

    QApplication app(argc, argv);
    QQuickView view;
    JobController controller;

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setInitialProperties({
                                  {"timelineModel", QVariant::fromValue(controller.timelineModel())},
                                  {"jobModel", QVariant::fromValue(controller.jobModel())}
                              });
    view.setSource(QUrl(QStringLiteral("qrc:main.qml")));

    Job j1("A", 1, 7, 0);
    Job j2("B", 2, 4, 0);
    j1.setStartTime(j1.arrivalTime());
    j2.setStartTime(j2.arrivalTime());
    controller.timelineModel()->addJobs({j1, j2});

    QObject *item = view.rootObject();
    QObject::connect(item, SIGNAL(visualize()),
                     &controller, SLOT(visualize()));

    view.show();
    return app.exec();
}
