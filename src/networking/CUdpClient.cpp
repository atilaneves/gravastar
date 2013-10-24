#include "CUdpClient.hpp"


CUdpClient::CUdpClient(const std::string& address, int port):
    CUdpSocket(address, port)
{

}

CUdpClient::CUdpClient(boost::asio::ip::address address, int port):
    CUdpSocket(address, port)
{
}
