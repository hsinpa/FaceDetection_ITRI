#include "HttpRequest.h"
#include <iostream>
#include "StaticText.h"

size_t HttpRequest::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string HttpRequest::Curl(const std::string& url, const std::string& method, std::vector<std::string>& header,  json& data) {
	CURL* curl_handle = curl_easy_init();

    struct curl_slist* http_header = NULL;
    auto header_lens = header.size();

    if (header_lens > 0) {
        for (uint32_t i = 0; i < header.size(); i++) {
            http_header = curl_slist_append(http_header, header[i].c_str());
        }
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, http_header);
    }

    if (method == HTTPMETHOD_POST) {
        std::string post_files_str = data.dump();

        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, post_files_str.length());
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post_files_str.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_COPYPOSTFIELDS, post_files_str.c_str());

        curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
    }

    return Curl(url, method, curl_handle);
}

std::string HttpRequest::Curl(const std::string& url, const std::string& method, CURL* p_curl = nullptr) {
    CURL* curl_handle = p_curl;
    if (curl_handle == nullptr) curl_handle = curl_easy_init();

    long httpCode(0);

    std::string readBuffer;

    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, method.c_str());

    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 5);

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(curl_handle);
    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl_handle);

    //std::cout << "Curl Code: " << httpCode << std::endl;
    //std::cout << "Curl Buffer: " << readBuffer << std::endl;

    return readBuffer;
}
