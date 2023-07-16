
#include "QNet/QSession.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QEventLoop>
#include <QTimer>
#include <QElapsedTimer>

namespace QNet{

class KSession::Impl
{
public:
    Impl();
    ~Impl();

    QResponse head();
    QResponse get();
    QResponse post();
    QResponse deleteFun();
    QResponse put();

private:
    std::unique_ptr<QNetworkAccessManager> m_pAccessManager;

    QResponse makeRequest(int operation);

    QByteArray getRequestData(int operation);

public:
    QNetworkRequest m_request;
    QBodyData m_body;
    qint32 m_timeOut;
};

KSession::Impl::Impl()
    : m_pAccessManager(new QNetworkAccessManager)
{
    m_timeOut = 10000;

    m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_request.setRawHeader("Accept", "*/*");
}

KSession::Impl::~Impl()
{
}

QResponse KSession::Impl::head()
{
    return makeRequest(QNetworkAccessManager::HeadOperation);
}

QResponse KSession::Impl::get()
{
    return makeRequest(QNetworkAccessManager::GetOperation);
}

QResponse KSession::Impl::post()
{
    return makeRequest(QNetworkAccessManager::PostOperation);
}

QResponse KSession::Impl::deleteFun()
{
    return makeRequest(QNetworkAccessManager::DeleteOperation);
}

QResponse KSession::Impl::put()
{
    return makeRequest(QNetworkAccessManager::PutOperation);
}

QResponse KSession::Impl::makeRequest(int operation)
{
    QNetworkReply    *reply = nullptr;

    switch(operation)
    {
    case QNetworkAccessManager::HeadOperation:
        reply = m_pAccessManager->head(m_request);
        break;
    case QNetworkAccessManager::GetOperation:
        reply = m_pAccessManager->get(m_request);
        break;
    case QNetworkAccessManager::PutOperation:
        reply = m_pAccessManager->put(m_request, getRequestData(operation));
        break;
    case QNetworkAccessManager::PostOperation:
        reply = m_pAccessManager->post(m_request, getRequestData(operation));
        break;
    case QNetworkAccessManager::DeleteOperation:
        reply = m_pAccessManager->deleteResource(m_request);
    default:
        break;
    }

    QEventLoop loop;
    QTimer timerOut;
    QElapsedTimer time;
    timerOut.setSingleShot(true);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timerOut, &QTimer::timeout, &loop, &QEventLoop::quit);

    time.start();
    timerOut.start(m_timeOut);
    loop.exec();

    qint32 errorCode = 0;
    qint32 httpCode = 0;
    QByteArray baResponse;
    QString errorString = "";
    double elapsed = 0;
    QList<QResponse::RawHeaderPair> header = reply->rawHeaderPairs();
    QString url = reply->url().toString();

    if(!timerOut.isActive())
    {
        errorCode = QNetworkReply::TimeoutError;
        errorString = QString("request timeOut %1").arg(m_timeOut);
        qWarning().noquote() << errorString;
    }
    else
    {
        timerOut.stop();

        errorCode = reply->error();
        if(QNetworkReply::NoError == errorCode)
        {
            baResponse = reply->readAll();
        }
        else
        {
            errorString = reply->errorString();
            qCritical().noquote() << "request Finish: fail." << errorCode << errorString;
        }
    }

    httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
    elapsed = time.elapsed();
    reply->deleteLater();

    return QResponse(httpCode, errorCode, errorString,  header, url, elapsed, baResponse);
}

QByteArray KSession::Impl::getRequestData(int operation)
{
    if (QNetworkAccessManager::PostOperation == operation)
    {
        if(m_body.m_bodyType & BodyRawJSON)
        {
            return m_body.m_data;
        }
        else if (m_body.m_bodyType & BodyFormData)
        {
            return m_body.queryToByteArray();
        }
    }
    return QByteArray();
}

}

QNet::KSession::KSession()
    : pimpl(new Impl)
{
}

QNet::KSession::~KSession()
{
}

void QNet::KSession::setOption(const QQUrl &url)
{
    setUrl(url);
}

void QNet::KSession::setOption(const QHeader &header)
{
    setHeader(header);
}

void QNet::KSession::setOption(const QRawHeader &rawHeader)
{
    setRawHeader(rawHeader);
}

void QNet::KSession::setOption(const QQueryParam &param)
{
    setParameters(param);
}

void QNet::KSession::setOption(const QBodyData &body)
{
    setBody(body);
}

void QNet::KSession::setOption(const QTimeOut &timeOut)
{
    setTimeOut(timeOut);
}

void QNet::KSession::setOption(const QVerifySsl &verify)
{
    setVerifySsl(verify);
}

void QNet::KSession::setUrl(const QQUrl &url)
{
    QUrl _utl = pimpl->m_request.url();
    _utl.setUrl(url);

    pimpl->m_request.setUrl(_utl);
}

void QNet::KSession::setHeader(const QHeader &header)
{
    auto headerList = header.keys();
    for(int i = 0; i < headerList.size(); i++)
    {
        auto key = headerList[i];
        pimpl->m_request.setHeader(static_cast<QNetworkRequest::KnownHeaders>(key), header.value(key));
    }
}

void QNet::KSession::setRawHeader(const QRawHeader &rawHeader)
{
    auto headerList = rawHeader.keys();
    for(int i = 0; i < headerList.size(); i++)
    {
        auto key = headerList[i];
        pimpl->m_request.setRawHeader(key, rawHeader.value(key));
    }
}

void QNet::KSession::setParameters(const QQueryParam &parameter)
{
    QUrl _utl = pimpl->m_request.url();
    QUrlQuery _urlQuery;
    auto keys = parameter.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        auto key = keys[i];
        _urlQuery.addQueryItem(key, parameter.value(key));
    }

    _utl.setQuery(_urlQuery);
    pimpl->m_request.setUrl(_utl);
}

void QNet::KSession::setBody(const QBodyData &body)
{
    pimpl->m_body = body;
}

void QNet::KSession::setTimeOut(QTimeOut mTime)
{
    pimpl->m_timeOut = mTime;
}

void QNet::KSession::setVerifySsl(const QVerifySsl &verify)
{
    QSslConfiguration conf = pimpl->m_request.sslConfiguration();
    conf.setPeerVerifyMode(verify ? QSslSocket::VerifyPeer : QSslSocket::VerifyNone);
    pimpl->m_request.setSslConfiguration(conf);
}

QNet::QResponse QNet::KSession::head()
{
    return pimpl->head();
}

QNet::QResponse QNet::KSession::get()
{
    return pimpl->get();
}

QNet::QResponse QNet::KSession::post()
{
    return pimpl->post();
}

QNet::QResponse QNet::KSession::deleteFun()
{
    return pimpl->deleteFun();
}

QNet::QResponse QNet::KSession::put()
{
    return pimpl->put();
}
