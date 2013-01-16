#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include<boost/thread/thread.hpp>
#include<boost/asio.hpp>

#include<iostream>
#include<fstream>
#include<string>
#define ASIO boost::asio
#define BLOCK_SIZE 64
class Terminal{

public:
	static void receive()
	{
		//初始化socket
		ASIO::io_service iosev;
		ASIO::ip::tcp::acceptor acceptor(iosev, ASIO::ip::tcp::endpoint(ASIO::ip::tcp::v4(), (unsigned int)port));
		ASIO::ip::tcp::socket socket(iosev);
		acceptor.accept(socket);
		ofs.open("ofstream.log", std::ios::out);
		ofs << " client from " << socket.remote_endpoint().address() << std::endl;
		boost::system::error_code ec;
		char buf[BLOCK_SIZE];
		int step = 0;
		for (;;)
		{
			int len = socket.read_some(ASIO::buffer(buf), ec);
			if (!start)
				return ;
			if (ec)
			{
				ofs << "error"
					<<boost::system::system_error(ec).what() << std::endl;
				break;
			}
			ofs.write(buf, len);
			ofs << "len =" << len << std::endl;
			ofs <<"step"<< ++step << std::endl;
			//接收
			Sleep(1000);
		}
		ofs.close();
	}
	static void send()
	{
		ASIO::io_service iosev;
		ASIO::ip::tcp::socket socket(iosev);
		ASIO::ip::tcp::endpoint ep(ASIO::ip::address_v4::from_string(ip.c_str()), port);
		boost::system::error_code ec;
		socket.connect(ep, ec);
		if (ec)
		{
			ofs << boost::system::system_error(ec).what() << std::endl; 
			return ;
		}
		char buf[BLOCK_SIZE];
		for (int i = 0 ; i < BLOCK_SIZE; i++)
		{
			buf[i] = 'a';
		}
		for (int i = 0; i < 2; ++i)
		{
			size_t len = socket.write_some(ASIO::buffer(buf), ec);
			std::cout << "writed " << len << std::endl;
		}

	}
public:
	static void startServer()
	{
		start = true;
		boost::thread thrd(&receive);
	
	}
	static void startClient()
	{
		start = true;
		boost::thread thrd(&send);
	}
	static void stop()
	{
		start = false;
	}

	static void setPort(int p)
	{
		port = port;
	};
	static int getPort()
	{
		return port;
	}

	static void setIp(std::string p)
	{
		ip = p;
	}
	static std::string getIp()
	{
		return ip;
	}

public:
	static int port;
	static std::string ip;
	static bool start; // start : true ;   stop : false 
	static std::ofstream ofs;
};
int Terminal::port;
std::string Terminal::ip;
bool Terminal::start;
std::ofstream Terminal::ofs;