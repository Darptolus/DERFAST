# 0. Setup

## List of Materials (4-Unit Rack)

This list describes the materials required to build a 4-board cluster

- 4 Parallella boards (you can get them from DigiKey or other vendors, you can find more information in their website https://www.parallella.org/)

- 4 micro-SD cards with at least 16Gb (here is a very cheap 10-pack or something like these more flexible combos)

- 4 micro-USB cables min length 30 cm (1 ft) (I recommend these)

- USB Charger [with at least 4 type A ports] (I recommend this one with 6-ports, or one with the same form factor, since the power case is designed for it)

- Cooling Fan [max size 100 mm x 100 mm x 15 mm] (I recommend this one because is cheap and works, but others with similar size and cable configuration works)

- Power supply for cooling fan (If your configuration is for more than 8 boards I recommend this one or something similar [AC 100 V/ 240 V to DC 12 V 10 A 120 W] that has a nice metal casing and can also be attached to the switch) (If you are going to plug just two fans or less you can use any 12 V with at least 1 A output power supply you may have lying around)

- 5 Ethernet Cables (4 can be short like these, depending on the distance from the switch to the boards, and one should be long enough to connect the switch with either your computer or the modem to access the cluster network)

- Switch or Router with enough RJ-45 ports

- Ethernet connection


## 3D Printing

3D-Printed Parts

- 4 Board Trays (Frame_01)

- 1 Board Casing (Frame_02)

- 1 Fan Casing (Frame_03_B & Frame_03_T)

- 1 Power Casing (Frame_04)

- 1 Network Casing (Frame_06)

Getting 3D files
STL files:

https://www.thingiverse.com/thing:4493780

https://cults3d.com/en/3d-model/various/demac-a-mo...

https://www.myminifactory.com/object/3d-print-dema...


## Slicing


3D Printing
Board Tray (Frame_01)

No additional supports required. This one is pretty straightforward, just place it with the flat surface facing the printing surface.

Board Casing (Frame_02)

This one may require some support in the middle beams. You can argue that a well tuned machine/slicer can print those bridges without additional support. Please try some bridge stress tests first if you want to print without supports since the idea was that the wouldn't require them. On the other hand, the columns lateral and walls provide enough support for these to be printed without additional support structures.

Fan Casing (Frame_03_B & Frame_03_T)

No additional supports required. Just place both parts with the flat surface facing the printing surface.

Power Casing (Frame_04)

Similar to Frame_02, this one may require some support in the middle beams. You can also try to print this one without additional support material (as it was intended). The columns lateral and walls provide enough support for these to be printed without additional support structures.

Output Cooling Casing (Frame_05_B & Frame_05_T)

No additional supports required. Just place both parts with the flat surface facing the printing surface.


Remove Support Material (if needed)
