#pragma once
#include <string>

const std::string HTTPMETHOD_GET = "GET";
const std::string HTTPMETHOD_POST = "POST";
const std::string HTTPMETHOD_PULL = "PULL";
const std::string HTTPMETHOD_DELETE = "DELETE";

const std::string HTTP_DOMAIN = "localhost";
const std::string HTTP_GET_USERS = "http://" + HTTP_DOMAIN + ":2211/FV/DBService/ReadRecord/userlist/1/100000000";
const std::string HTTP_GET_USER = "http://" + HTTP_DOMAIN + ":2211/FV/DBService/ReadRecord_information/{}";
const std::string HTTP_ADD_USER = "http://" + HTTP_DOMAIN + ":2211/FV/DBService/AddRecord/ww";
const std::string HTTP_READ_FACE = "http://" + HTTP_DOMAIN + ":2211/FV/DBService/ReadRecord_faces/{}";

const std::string HEADER_JSONTYPE = "Content-Type: application/json";
const float MIN_COMPARE_THRESHOLD = 0.72;

const std::string SOCKET_ACTION_REGISTER = "register";
const std::string SOCKET_ACTION_DETECTION = "detect";
