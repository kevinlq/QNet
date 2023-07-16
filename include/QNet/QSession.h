#pragma once

#include <cstdint>
#include <memory>
#include <QUrl>

#include "QNet/QResponse.h"

namespace QNet{

class KSession
{
public:
    KSession();
    ~KSession();

    void setOption(const QQUrl &url);
    void setOption(const QHeader &header);
    void setOption(const QRawHeader &rawHeader);
    void setOption(const QQueryParam &param);
    void setOption(const QBodyData &body);
    void setOption(const QTimeOut &timeOut);
    void setOption(const QVerifySsl &verify);

    void setUrl(const QQUrl &url);
    void setHeader(const QHeader &header);
    void setRawHeader(const QRawHeader &rawHeader);
    void setParameters(const QQueryParam &parameter);
    void setBody(const QBodyData &body);
    void setTimeOut(QTimeOut mTime);
    void setVerifySsl(const QVerifySsl &verify);

    QResponse head();
    QResponse get();
    QResponse post();
    QResponse deleteFun();
    QResponse put();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};

} // namespace KNet

