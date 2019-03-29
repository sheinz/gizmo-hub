# MQTT topics specification


## General information


## Relay box topics specification

Relay box update status topic: `/<gizmo_hub_name>/<relay_box_name>/status`
For example `/gizmo_hub/relay_box1/status`
Data is a text with the following format:
```
Relay1=on
Relay2=off
Led1=on
Led2=off
Voltage=na
Temperature=20.3
```

Gizmo-hub subscribes to commands topic for a registered device and transfers
notifications on this topic to the device.


