#include "machineserver.h"
#include <QDebug>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

machineServer::machineServer(QObject * parent): QThread(parent)
{
    struct sockaddr receive_data;
    this->server_socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
    char path[] = "./machine";
    strncpy(this->server_socket_name,path,strlen(path)+1);

    receive_data.sa_family = AF_LOCAL;
    strncpy(receive_data.sa_data, this->server_socket_name,strlen(this->server_socket_name)+1);

    uint8_t socket_size = strlen(receive_data.sa_data) + sizeof(receive_data.sa_family);

    if(bind(this->server_socket_id, &receive_data, socket_size)!=0)
    {
        qDebug () << "Error no bind do server socket id: " << strerror(errno);
        this->errorOccurred=1;
        return;
    }

    //qDebug() << "Nome do socket = " << receive_data.sa_data;
    if(listen(this->server_socket_id,2)!=0)
    {
        qDebug () << "Error in server listen: " << strerror(errno);
        this->errorOccurred=1;
        return;
    }
    this->errorOccurred=0;
}


machineServer::~machineServer()
{
    qDebug() << "Fechei o servidor";
    unlink(this->server_socket_name);
    close(this->server_socket_id);
    close(this->client_socket_id);
}

void machineServer::init()
{
    // qualquer operação antes do start pode ser posta aqui
    this->start();
    if(this->isRunning())
    {
      qDebug("thread machine server iniciando ..");
    }
}

void machineServer::run()
{
    while(1){
       
        if(this->errorOccurred){
            qDebug() << "Um erro anterior impediu que o socket servidor da máquina fosse iniciado";
            qDebug() << "Por favor tente ligar o servidor novamente";
            break;
        }
        struct sockaddr clienteAddr;
        socklen_t clienteLength = sizeof(( struct sockaddr *) & clienteAddr);
        qDebug() << "Antes do accept machine";
        this->client_socket_id = accept(this->server_socket_id, &clienteAddr, &clienteLength);
        if(this->client_socket_id<0)
        {
            qDebug () << "Error no accept do servidor machine: " << strerror(errno);
            return;
        }
        qDebug() << "Depois do accept machine";
        read_interface_message();
    }
    qDebug() << "Terminou a run machine";
}

void machineServer::read_interface_message()
{
    while(1){

        int value = read(this->client_socket_id,&this->interface_message.payload,interface_payload_size);
                if(value<=0){
                    break;
        };
        // qDebug() << "Command received = " << this->interface_message.command;
        // switch (this->interface_message.command)
        // {
        //     case 1:
        //         qDebug() << "Pressure = " << this->interface_message.pressure;
        //     break;

        //     case 2:
        //         qDebug() << "Distance = " << this->interface_message.distance << "Velocity = " << this->interface_message.velocity;
        //     break;

        //     case 3:
        //         qDebug() << "Enabled = " << this->interface_message.enabled << "Sample Period= " << this->interface_message.sample_period;

        //     default:
        //         break;
        // }
    }
}
