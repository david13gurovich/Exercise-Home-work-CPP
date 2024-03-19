#ifndef H_TCP_SERVER_ 
#define H_TCP_SERVER_
/**************************************************/
/* this file define server tcp */
/**************************************************/

#include "reactor_inc.hpp"

int CreateTcpServerAndBind(ilrd::Logger *log, int *tcp_socket, 
                            struct sockaddr_in *server_addr);
int HandleNewConnection(struct sockaddr_in *server_addr,
                        int *client_socket, int master_socket);
class FunctorToPassReactor
{
public:
    FunctorToPassReactor(struct sockaddr_in *server_addr, 
                                        int master_socket, 
                                    ilrd::Reactor *reactor);
	void operator()(int fd);
    void RecieveAndSend(int socket_descriptor);

private:
    struct sockaddr_in *m_server_addr;
    int m_master_socket;
    ilrd::Reactor *m_reactor;
};


#endif