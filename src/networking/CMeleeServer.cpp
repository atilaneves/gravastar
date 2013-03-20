#include "CMeleeServer.hpp"
#include "CUdpServer.hpp"


CMeleeServer::CMeleeServer():
    mThread([this]() { mUdpServer.run(); }) {

}

CMeleeServer::~CMeleeServer() {
    mUdpServer.stop();
    mThread.join();
}
