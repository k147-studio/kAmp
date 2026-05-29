#pragma once

#include <atomic>
#include <memory>

class ApiClient {
public:
    using ReplyFunc = std::function<void(const String &)>;
    using LifetimeToken = std::shared_ptr<std::atomic<bool>>;

    static void runHTTP(const URL &url, const ReplyFunc &replyFunc,
                        const LifetimeToken &alive = nullptr);
};
