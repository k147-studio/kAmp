#include <JuceHeader.h>
#include "ApiClient.h"

using ReplyFunc = std::function<void(const String &)>;

void ApiClient::runHTTP(const URL &url, const ReplyFunc &replyFunc) {
    auto req = [url, replyFunc] {
        const auto options = URL::InputStreamOptions(URL::ParameterHandling::inAddress);
        if (const auto stream = url.createInputStream(options); stream != nullptr) {
            auto content = stream->readString();
            MessageManager::callAsync([replyFunc, content] {
                replyFunc(content);
            });
        } else {
            MessageManager::callAsync([replyFunc] {
                replyFunc("Error connecting to server");
            });
        }
    };

    Thread::launch(req);
}
