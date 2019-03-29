# gizmo-hub to devices communication protocol

## General information
Communication between devices and hub is done using radio modules.
It can be nrf24l01 or RFM69.
The data size should be minimal to fit inside a single packet of RFM69.

## Protocol

### Naming
Each device has a unique name. Which a string. (e.g. "kitchen_thermo_valve")
Gizmo-hub keeps a table of device names and its network addresses.

### Status
Each device sends its status periodically within specified time period.
If the status update is not received by gizmo-hub the device is marked as offline.

The status contains all the information the device can provide.
If device status changes the status update should be sent immediately.

The status format is a text base structure.
For example relay box:
```
Relay1=on
Relay2=off
Led1=on
Led2=off
Voltage=na
Temperature=20.3
```

### Commands
The device can accept various commands.
The general format is the following: `<object>=<action>`
For example relay box can have the following commands:
`Relay1=on`, `Led2=off`, `Relay2=click`, `Led1=blink`

If the status of the device has changed after command action the status update
should be issued.

Each device type has its own set of commands.

## nrf24l01


## RFM69

