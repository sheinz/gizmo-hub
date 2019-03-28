cmake_minimum_required(VERSION 2.8)

project(gizmo_hub)

add_executable(gizmo_hub src/main.cpp src/MqttClient.cpp)
target_link_libraries(gizmo_hub rf24 mosquittopp)
