#include "TestHttpRequest.h"
#include "QNet/QNet.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

void debugResponse(const QNet::QResponse &response)
{
    qDebug() << "================ begin ================";

    qDebug() << "url: " << response.m_url;
    qDebug() << "elapsed:" << response.m_elapsed;
    qDebug() << "httpCode: " << response.m_statusCode ;
    qDebug() << "errorCode: " << response.m_replayError;
    qDebug() << "errorString: " << response.m_replayErrorString;
    qDebug() << "data:" << response.m_responseData;

    qDebug() << "================ end ================";
    qDebug() << "";
}

TestHttpRequest::TestHttpRequest(QObject *parent)
    : QObject{parent}
{
}

void TestHttpRequest::tst_get()
{
    auto response = QNet::Get(QNet::QQUrl{"http://www.httpbin.org/get"},
                              QNet::QHeader{{QNetworkRequest::ContentTypeHeader, "application/json"}},
                              QNet::QTimeOut{20000});
    debugResponse(response);

    //QVERIFY2(response.m_statusCode == 200, "status code error");
    QCOMPARE(response.m_statusCode, 200);
    QCOMPARE(response.m_replayError, 0);
}

void TestHttpRequest::tst_get_async()
{
    QNet::AsyncResponse fr = QNet::GetAsync(QNet::QQUrl{"http://www.httpbin.org/get"});
    fr.wait();

    auto response = fr.get();
    debugResponse(response);

    QCOMPARE(response.m_statusCode, 200);
}

void TestHttpRequest::tst_get_callback()
{
    qDebug() << "start get  callback request begin ";
    auto future_cbk = QNet::GetCallback([](const QNet::QResponse &r){
        debugResponse(r);
    }, QNet::QQUrl{"http://www.httpbin.org/get"});

    qDebug() << "start get  callback request end ";

    future_cbk.wait();
}

void TestHttpRequest::tst_post()
{
    QByteArray ba;
    {
        QJsonObject jsObj;
        jsObj.insert("name", "kevin");
        jsObj.insert("em", "kevin.123");

        ba = objToJson(jsObj);
    }
    auto response = QNet::Post(QNet::QQUrl{"http://www.httpbin.org/post"},
                          QNet::QBodyData{QNet::BodyRawJSON, ba},
                          QNet::QTimeOut{20000});
    debugResponse(response);
    QCOMPARE(response.m_statusCode, 200);
}

void TestHttpRequest::tst_post_async()
{
}

void TestHttpRequest::tst_post_callback()
{
    qDebug() << "start post  callback request begin ";
    auto future_cbk = QNet::PostCallback([](const QNet::QResponse &r){
        debugResponse(r);
    }, QNet::QQUrl{"http://www.httpbin.org/post"});

    qDebug() << "start post  callback request end ";

    future_cbk.wait();
}

QByteArray TestHttpRequest::objToJson(const QJsonObject &jsObj)
{
    QJsonDocument jsDoc(jsObj);
    return jsDoc.toJson();
}

