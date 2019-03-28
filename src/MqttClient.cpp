#include "MqttClient.h"
#include <iostream>

#define DEFAULT_KEEP_ALIVE 60

MqttClient::MqttClient(const std::string& host, int port)
    : mosquittopp("ClientID")
{
    connect(host.c_str(), port, DEFAULT_KEEP_ALIVE);
}

MqttClient::~MqttClient()
{

}

void MqttClient::on_connect(int rc)
{
    std::cout << "on connect" << std::endl;
}

void MqttClient::on_message(const struct mosquitto_message *message)
{
    std::cout << "on message" << std::endl;
}

void MqttClient::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    std::cout << "on subscribe" << std::endl;
}
