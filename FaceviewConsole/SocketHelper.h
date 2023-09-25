#pragma once
#include <string>
#include "asio.hpp"

class SocketHelper
{
private:
    void data_receive(const asio::error_code& error_code, const std::size_t num_bytes);

public:
    std::string read(const std::shared_ptr<asio::ip::tcp::socket>& socket);
    void send(const std::shared_ptr<asio::ip::tcp::socket>& socket, const std::string& message);
    void sock_accept(const std::shared_ptr<asio::ip::tcp::socket>& sockCli, void(*callback)(std::string));

    asio::ip::tcp::acceptor create_server(std::shared_ptr<asio::io_context>& io_context, std::shared_ptr<asio::ip::tcp::socket>& socket, int port);
};