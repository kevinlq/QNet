#pragma once
#include <QString>
#include <QPair>
#include <QVariant>
#include <QUrlQuery>
#include <QNetworkRequest>

#include <chrono>
#include <cstdint>

namespace QNet{

using QHeader = QMap<quint32, QVariant>;
using QRawHeader = QMap<QByteArray,QByteArray>;
using QQueryParam = QMap<QString, QString>;
using QQUrl = QString;
using QTimeOut = qint32;
using QVerifySsl = bool;

enum BodyType
{
    BodyFormData        = 1,
    BodyFormUrlencoded  = 1 << 1,
    BodyRawJSON         = 1 << 2,
    BodyRawText         = 1 << 3,
    BodyRawXML          = 1 << 4,
    BodyBinary          = 1 << 5
};

class QBodyData
{
public:
    QBodyData() = default;
    QBodyData(BodyType type, const QByteArray &data);
    QBodyData(BodyType type , const QQueryParam &queryParam);

    QByteArray queryToByteArray();

    BodyType m_bodyType = BodyRawJSON;
    QByteArray m_data = QByteArray();
    QQueryParam m_queryParam;
};

class QResponse
{
public:
    typedef QPair<QByteArray, QByteArray> RawHeaderPair;
    QResponse() = default;

    template <typename HeaderType>
    QResponse(const qint32 &httpCode,const qint32 &statusCode, const QString &errorString, HeaderType &&header,
              const QString &url, const double& elapsed, const QByteArray &data)
        : m_statusCode (httpCode),m_replayError(statusCode), m_replayErrorString(errorString), m_rawHeader(header),
        m_url(url), m_elapsed(elapsed),m_responseData(data) {}

    //QResponse(const QResponse& other) = default;
    //QResponse(QResponse&& old) noexcept = default;
    ~QResponse() noexcept = default;

    qint32                  m_statusCode  = 0;
    qint32                  m_replayError = 0;
    QString                 m_replayErrorString = "";
    QList<RawHeaderPair>    m_rawHeader;
    QString                 m_url = "";
    double                  m_elapsed = 0.0;
    QByteArray              m_responseData;
};

}   // namespace KNet
