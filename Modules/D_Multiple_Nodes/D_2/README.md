# D.2. DEMAC: A distributed memory architecture

![image](../../Figures/D_Multiple_Nodes/D_2/DEMAC.png)

## Prerequisites
- N/A

## Referenced by:

- ["A.2. DEMAC: Single node installation and setup"](../../A_Single_Core/A_2/README.md) -> [Continue Node Installation](#15-perform-node-installation-x4)

## List of Materials (4-Unit Rack)

This list describes the materials required to build a 4-board cluster

- 1 PC (Preferable with a unix-based OS, other OS are not supported by this procedure)

- 4 Parallella board
(you can get them from DigiKey or other vendors, you can find more information in their website https://www.parallella.org/)

- 4 micro-SD card with at least 16 Gb

- 1 USB Hub (Parallella Power Supply): 
A high quality USB hub with at least 4 ports (2000 mA rated 5 V DC for each board), connector options are: 
  - micro-USB
  - 5.5mm OD / 2.1mm ID center positive polarity plug

- 4 micro-USB Cables
 
- 1 Cooling Fan ***(Warning: The Parallella board requires cooling)***, pc fan options are:
  - 92 mm x 92 mm x 15 mm PC fan
  - 100 mm x 100 mm x 15 mm PC fan

- 1 Cooling fan Power Supply:  
  - For a PC fan you can use a power supply with 12 V and at least 1 A output

- 4 Ethernet Cables (RJ-45)

- 1 Switch or Router RJ-45 5-ports

- 1 Power strip (Ideally surge protected with power switch and at least 6 ports)

- Ethernet connection

3D Printed Parts:

- 4 Frame_01 to support the board

- 1 Frame_02 to hold the board trays (Frame_01)

- 1 Frame_03 to encase the fan

- 1 Frame_05 for the USB power supply

- 1 Frame_06 for the 5-port switch

Optional:

- 1 Frame_04 to complete the cooling system

<!-- ToDo: Add figures for list of materials  -->

## Rack Assembly Instructions 

### 0. Gather 3D Printed frames and other materials

<!-- (ToDo: Add reference to 0_Setup) -->

### 1. Attach Frame_05 to Frame_02

- Frame_05 and Frame_02 should snap together without additional elements

<!-- ![image](../../Figures/D_Multiple_Nodes/D_2/Step_01.png) -->

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_01.png" width="400">

### 2. Attach Frame_06 to Frame_05

- Frame_06 and Frame_05 should snap together without additional elements

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_02.png" width="400">


### 3. Place Fan in Frame_03 "Cooling Case"

- Slide the fan in the Frame_03_B
- Place the cable in the cable holder
- Secure the fan using Frame_03_T
- Frame_03_B and Frame_03_T should snap together without additional elements

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_03.png" width="400">


### 4. Attach Frame_03 to Frame_02

- Frame_03 and Frame_02 should snap together without additional elements
- Optionally, attach Frame_04 to Frame_02 

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_04.png" width="400">

### 5. Connect power strip to outlet (Power: OFF)

- Check that the switch is off before proceeding

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_05.png" width="600">

### 6. Place the USB hub in Frame_05 "Power Case"

- Slide the USB hub in Frame_05

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_06.png" width="600">

### 7. Connect USB hub to Power Strip (Power: OFF)

- Use the slot in the front of Frame_05 to connect the power cord to the USB hub

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_07.png" width="600">

### 8. Place the network switch in Frame_06 "Network Case"

- Slide the network switch in Frame_06

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_08.png" width="600">

### 9. Connect network switch to Power Strip (Power: OFF)

- Use the slot in the front of Frame_06 to connect the power cord to the network switch

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_09.png" width="600">

### 10. Connect cooling system to Power Strip (Power: OFF)

- Attach the power supply to the fan

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_10.png" width="600">

### 11. Energize and test peripherals (Power: ON)

- Check that the cooling system, network switch and USB hub

### 12. Connect the switch to internet

- Check for activity LEDs

### 13. Place Parallella board in Frame_01 "Board Tray" (x4)

- The Parallella board should fit the pins in Frame_01

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_13.png" width="400">

### 14. Slide Frame_01 into Frame_02 (x4)

- The Parallella board should fit the pins in Frame_01

<img src="../../Figures/D_Multiple_Nodes/D_2/Step_14.png" width="800">

### 15. Perform Node Installation (x4)

<!-- [Node Installation](#node-installation) -->

#### 15.1. Single node installation and setup (x4)

- Follow the instructions in steps 1-6 in the module [A.2. DEMAC: Single node installation and setup](../../A_Single_Core/A_2/README.md)

#### 15.7. Setup Board Hostname

- In Step 7, set up the names of the boards to be different for each board. DEMAC uses hostnames NOPA##, where ## is a two digit number that represents the ID of that node. 

For instance, a 4 unit rack can have names NOPA01, NOPA02, NOPA03, NOPA04. A 24-unit cluster might use NOPA01-24. 

It is possible to use other hostnames, as long as they are unique within the network.

#### 15.8. Setup IP

- In step 8 use the same ## ID of the board to set up the IP of that board.

For example:


NOPA01 IP -> 192.168.10.101

NOPA24 IP -> 192.168.10.124

#### 15.9. Add hostnames from other nodes


- Edit the file `/etc/hosts`

Add the IP address, hostname, and MAC address from other boards to this file. This will provide the required information to communicate different nodes.

```
sudo vim /etc/hosts
```

For example, in a 4-board rack, the `/etc/hosts` file will look like this: 

```
192.168.10.101  NOPA01	[Mac_Address]
192.168.10.102  NOPA02	[Mac_Address]
192.168.10.103  NOPA03	[Mac_Address]
192.168.10.104  NOPA04	[Mac_Address]
```

Replace “[Mac_Address]” with board’s MAC address

#### 15.10. Reboot
 
- Reboot the board to apply the changes.

```
sudo reboot -f
```

#### 15.11. Update && Upgrade

- Updating and upgrading packages might reduce errors that can arise from using outdated software.

```
sudo apt-get update
```

```
sudo apt-get upgrade -y
```

#### 15.12. Install Ansible

Ansible is an open source IT automation engine that automates provisioning, configuration management, application deployment, orchestration, and many other IT processes.

- Install Ansible using apt-get package manager

```
sudo apt-get install ansible -y
```

- Edit `/etc/ansible/hosts` to add information about other hosts in the system

```
sudo vim /etc/ansible/hosts
```

For example, the `/etc/ansible/hosts` for a 4-board rack might be:

```
NOPA01
NOPA02
NOPA03
NOPA04
```

#### 15.13. Install nsf

NFS (Network File System) allows you to 'share' a directory located on one networked computer with other computers/devices on that network. The computer where directory located is called the server and computers or devices connecting to that server are called clients. Clients usually 'mount' the shared directory to make it a part of their own directory structure.

More information in https://help.ubuntu.com/community/SettingUpNFSHowTo.

- In the server run the following commands:

```
sudo mkdir -p DEMAC_nfs
```

```
sudo chmod 777 DEMAC_nfs/
```

```
sudo apt-get install nfs-kernel-server
```

```
sudo vim /etc/exports
```

- Add the following text:

```
/home/parallella/DEMAC_nfs 192.168.10.0/24 (rw,nohide,insecure,no_subtree_check,async,no_root_squash)
```
> *Note: 
rw: read and write, 
nohide: exports both filesystems, 
insecure, 
no_subtree_check, 
no_root_squash

```
service nfs-kernel-server restart
```

- Check: 
```
sudo exportfs -v
```

- In the clients run the following commands:

```
mkdir DEMAC_nfs
```

```
sudo apt-get install rpcbind nfs-common -y
```

```
sudo apt-get install autofs
```

```
sudo vim /etc/auto.master 
```

- Comment last line and add:

```
/-	/etc/auto.mount
```

```
sudo vim /etc/auto.mount
```

- Add the following text:

```
/home/parallella/DEMAC_nfs    -rw,user,exec,auto,hard,intr,nosuid,acl    nopa08:/home/parallella/DEMAC_nfs
```

```
sudo service autofs start
```

- Reboot

```
sudo reboot -f
```

### 16. Repeat step 13 until all 4 nodes have been installed

<!-- [Node Installation](#13-perform-node-installation-x4) -->
[Node Setup](#13-place-parallella-board-in-frame_01-board-tray-x4)


<img src="../../Figures/D_Multiple_Nodes/D_2/Step_16.png" width="800">


### 17. Check the connection and status of all the boards

ssh parallella@NOPA##