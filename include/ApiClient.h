#pragma once

class ApiClient {
public:
    using ReplyFunc = std::function<void(const String &)>;

    static void runHTTP(const URL &url, const ReplyFunc &replyFunc);
};
