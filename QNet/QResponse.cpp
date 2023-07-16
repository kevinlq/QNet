#include "QNet/QResponse.h"

QNet::QBodyData::QBodyData(BodyType type, const QByteArray &data)
    : m_bodyType(type), m_data(data)
{
}

QNet::QBodyData::QBodyData(BodyType type, const QQueryParam &queryParam)
    : m_bodyType(type), m_queryParam(queryParam)
{
}

QByteArray QNet::QBodyData::queryToByteArray()
{
    QUrlQuery _urlQuery;
    auto keys = m_queryParam.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        auto key = keys[i];
        _urlQuery.addQueryItem(key, m_queryParam.value(key));
    }
    return _urlQuery.toString(QUrl::FullyEncoded).toUtf8();
}
