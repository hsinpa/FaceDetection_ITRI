#pragma once

#include <json.hpp>
#include <string>
#include <vector>
#include <curl.h>

using json = nlohmann::json;

class HttpRequest
{
private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static std::string Curl(const std::string& url, const std::string& method, CURL* p_curl);

public :
	static std::string Curl(const std::string& url, const std::string& method, std::vector<std::string>& header, json &data);
};