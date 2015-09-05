
#include "download.h"
#include "file.h"
#include <curl/curl.h>

namespace shake {

using curl_ptr = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>;

curl_ptr make_curl()
{
    return curl_ptr(curl_easy_init(), &curl_easy_cleanup);
}

void download(const std::string& url, const std::string& filename)
{
    curl_ptr curl = make_curl();                                                                                                                                                                                                                                                           
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
