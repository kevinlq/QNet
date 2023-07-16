
#pragma once


#include <QObject>
#include <QtTest/QTest>
#include <QDebug>


class TestHttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit TestHttpRequest(QObject *parent = nullptr);

private Q_SLOTS:
    void tst_get();
    void tst_get_async();
    void tst_get_callback();

    void tst_post();
    void tst_post_async();
    void tst_post_callback();
};

