#include "SocketHelper.h"
#include <iostream>

void connect_handler(const asio::error_code& ec) {
	// 如果ec返回成功我们就可以知道连接成功了
	std::cout << "SocketHelper connect " << ec.message() << std::endl;
}

std::string SocketHelper::read(const std::shared_ptr<asio::ip::tcp::socket>& socket) {
	asio::streambuf buf;

	asio::error_code ec;
	std::string data = "";

	while (asio::read(*socket, buf, ec)) {
	std::cout << "received: '" << &buf << "'\n";
	data = asio::buffer_cast<const char*>(buf.data());

		if (ec) {
		    std::cout << "status: " << ec.message() << "\n";
		    break;
		}
	}

	return data;
}

void SocketHelper::send(const std::shared_ptr<asio::ip::tcp::socket>& socket, const std::string& message) {
	const std::string msg = message + "\n";
	asio::write(*socket, asio::buffer(message));
}

asio::ip::tcp::acceptor SocketHelper::create_server(std::shared_ptr<asio::io_context>& io_context, std::shared_ptr<asio::ip::tcp::socket>& socket, int port) {
	asio::ip::tcp::acceptor acceptor_(*io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

	//waiting for connection
	acceptor_.accept(*socket);

	return acceptor_;
}

void SocketHelper::sock_accept(const std::shared_ptr<asio::ip::tcp::socket>& sockCli, void(*callback)(std::string)) {
	auto my_buffer = std::make_shared<asio::streambuf>();

	std::cout << "client ip:" << sockCli->remote_endpoint().address() << std::endl;

	sockCli->async_receive(my_buffer->prepare(1024), [this, my_buffer, sockCli, callback](const asio::error_code& error_code, const std::size_t num_bytes)
	{
		asio::streambuf::const_buffers_type bufs = my_buffer->data();

		std::string str(asio::buffers_begin(bufs),
			asio::buffers_begin(bufs) + num_bytes);

		std::cout << "SocketHelper received: '" << (str) << "'\n";

		//std::string read_data = this->read(sockCli);

		callback(str);
	});
}