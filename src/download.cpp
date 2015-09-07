
#include "download.h"
#include "file.h"
#include "resource_ptr.h"
#include <curl/curl.h>

namespace shake {

using curl_ptr = resource_ptr<CURL, &curl_easy_cleanup>;

void download(const std::string& url, const std::string& filename)
{
    auto curl = curl_ptr(curl_easy_init());
    if (curl != nullptr)
    {
        file fp = fopen(filename.c_str(),"wb");
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, fp.handler.get());
        CURLcode res = curl_easy_perform(curl.get());
    }
}

}
