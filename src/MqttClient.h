#pragma once

#include <string>
#include <mosquittopp.h>

class MqttClient: public mosqpp::mosquittopp
{
public:
    MqttClient(const std::string& host, int port);
    ~MqttClient();

    void on_connect(int rc) override;
    void on_message(const struct mosquitto_message *message) override;
    void on_subscribe(int mid, int qos_count, const int *granted_qos) override;
};
