#include "CUdpClient.hpp"


CUdpClient::CUdpClient(const std::string& address, int port):
    CUdpSocket(address, port)
{

}
