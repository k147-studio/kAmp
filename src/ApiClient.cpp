#include <JuceHeader.h>
#include "ApiClient.h"

using ReplyFunc = std::function<void(const String &)>;

void ApiClient::runHTTP(const URL &url, const ReplyFunc &replyFunc, const LifetimeToken &alive) {
    auto req = [url, replyFunc, alive] {
        const auto options = URL::InputStreamOptions(URL::ParameterHandling::inAddress);
        if (const auto stream = url.createInputStream(options); stream != nullptr) {
            auto content = stream->readString();
            MessageManager::callAsync([replyFunc, content, alive] {
                if (alive == nullptr || alive->load()) {
                    replyFunc(content);
                }
            });
        } else {
            MessageManager::callAsync([replyFunc, alive] {
                if (alive == nullptr || alive->load()) {
                    replyFunc("Error connecting to server");
                }
            });
        }
    };

    Thread::launch(req);
}
