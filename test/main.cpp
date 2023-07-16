#include <QCoreApplication>

#include "TestHttpRequest.h"

int AssertTest(QObject* obj, int argc = 0, char **argv = nullptr)
{
    int status = QTest::qExec(obj, argc, argv);
    delete obj;

    return status;
}

int main(int argc, char *argv[])
{
    int status = 0;

    status |= AssertTest (new TestHttpRequest(), argc, argv);

    return 0;
}
