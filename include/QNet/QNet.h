#pragma once

#include <functional>
#include <future>
#include <utility>

#include "QNet/QSession.h"

namespace QNet{

using AsyncResponse = std::future<QResponse>;

namespace priv {

template <typename T>
void setOption(KSession& session, T&& t) {
    session.setOption(std::forward<T>(t));
}

template <typename T, typename... Ts>
void setOption(KSession& session, T&& t, Ts&&... ts)
{
    setOption(session, std::forward<T>(t));
    setOption(session, std::forward<Ts>(ts)...);
}

} // namespace priv


// ====================================== Get Begin ===================================
template <typename... Ts>
QResponse Get(Ts &&... ts)
{
    KSession session;
    priv::setOption(session, std::forward<Ts>(ts)...);
    return session.get();
}
template <typename... Ts>
AsyncResponse GetAsync(Ts... ts)
{
    return std::async(std::launch::async, [](Ts... ts) { return Get(std::move(ts)...); },
        std::move(ts)...);
}
template <typename Then, typename... Ts>
auto GetCallback(Then then, Ts... ts) -> std::future<decltype(then(Get(std::move(ts)...)))> {
    return std::async(std::launch::async, [](Then then, Ts... ts) {
            return then(Get(std::move(ts)...));
        }, std::move(then), std::move(ts)...);
}
// ====================================== Get End ===================================

// ====================================== Post Begin ===================================
template <typename... Ts>
QResponse Post(Ts &&... ts)
{
    KSession session;
    priv::setOption(session, std::forward<Ts>(ts)...);
    return session.post();
}
template <typename... Ts>
AsyncResponse PostAsync(Ts... ts) {
    return std::async(std::launch::async, [](Ts... ts) { return Post(std::move(ts)...); },
        std::move(ts)...);
}
template <typename Then, typename... Ts>
auto PostCallback(Then then, Ts... ts) -> std::future<decltype(then(Post(std::move(ts)...)))> {
    return std::async(std::launch::async, [](Then then, Ts... ts) {
            return then(Post(std::move(ts)...));
        }, std::move(then), std::move(ts)...);
}
// ====================================== Post End ===================================

// ====================================== Put Begin ===================================
template <typename... Ts>
QResponse Put(Ts&&... ts) {
    KSession session;
    priv::setOption(session, std::forward<Ts>(ts)...);
    return session.put();
}
template <typename... Ts>
AsyncResponse PutAsync(Ts... ts) {
    return std::async(std::launch::async, [](Ts... ts) { return Put(std::move(ts)...); },
        std::move(ts)...);
}
template <typename Then, typename... Ts>
auto PutCallback(Then then, Ts... ts) -> std::future<decltype(then(Put(std::move(ts)...)))> {
    return std::async(std::launch::async, [](Then then, Ts... ts) {
            return then(Put(std::move(ts)...));
        }, std::move(then), std::move(ts)...);
}
// ====================================== Put End ===================================


// ====================================== Delete Begin ===================================
template <typename... Ts>
QResponse Delete(Ts&&... ts) {
    KSession session;
    priv::setOption(session, std::forward<Ts>(ts)...);
    return session.deleteFun();
}
template <typename... Ts>
AsyncResponse DeleteAsync(Ts... ts) {
    return std::async(std::launch::async, [](Ts... ts) { return Delete(std::move(ts)...); },
        std::move(ts)...);
}
template <typename Then, typename... Ts>
auto DeleteCallback(Then then, Ts... ts) -> std::future<decltype(then(Delete(std::move(ts)...)))>
{
    return std::async(std::launch::async, [](Then then, Ts... ts) {
            return then(Delete(std::move(ts)...));
        }, std::move(then), std::move(ts)...);
}
// ====================================== Delete End ===================================

// ====================================== Head Begin ===================================
template <typename... Ts>
QResponse Head(Ts&&... ts)
{
    KSession session;
    priv::setOption(session, std::forward<Ts>(ts)...);
    return session.head();
}

// Head async methods
template <typename... Ts>
AsyncResponse HeadAsync(Ts... ts)
{
    return std::async(std::launch::async, [](Ts... ts) { return Head(std::move(ts)...); },
        std::move(ts)...);
}

// Head callback methods
template <typename Then, typename... Ts>
auto HeadCallback(Then then, Ts... ts) -> std::future<decltype(then(Head(std::move(ts)...)))>
{
    return std::async(std::launch::async, [](Then then, Ts... ts) {
            return then(Head(std::move(ts)...));
        }, std::move(then), std::move(ts)...);
}
// ====================================== Head Begin ===================================

} // namespace NKet
