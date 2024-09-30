# A.2. DEMAC: Single node installation and setup

## Prerequisites
- N/A

## Referenced by:

- ["D.2. DEMAC: A distributed memory architecture"](../../D_Multiple_Nodes/D_2/README.md) -> [Node Installation](#node-installation)

## List of Materials

This list describes the materials required to install a single board, as well as some optional 3D printed frames to suport the board and peripherals. 

- PC (Preferable with a unix-based OS, other OS are not supported by this procedure)

- Parallella board (you can get them from DigiKey or other vendors, you can find more information in their website https://www.parallella.org/)

- micro-SD card with at least 16 Gb

- Cooling Fan ***(Warning: The Parallella board requires cooling)***

- Parallella Power Supply: 
A high quality 2000 mA rated 5 V DC power supply, connector options are: 
  - micro-USB 
  - 5.5mm OD / 2.1mm ID center positive polarity plug
 
- Cooling fan Power Supply:  
  - For a PC fan you can use a power supply with 12 V and at least 1 A output

- Ethernet Cable (RJ-45)

- Switch or Router with enough RJ-45 ports

- Ethernet connection

Optional:

- Frame_01 to support the board

- Frame_02 to hold the board trays (Frame_01)

- Frame_03 to encase the fan

- Frame_04 for airflow

- Frame_05 for the USB power supply

- Frame_06 for the 5-port switch

> *Note: Additional instructions on how to assembly a 4-Unit rack can be found in ["D.2. DEMAC: A distributed memory architecture"](../../D_Multiple_Nodes/D_2/README.md)

## Node Installation
**Parabuntu 2019**

[Linux](#linux) | [Mac](#mac) | [Windows](#windows)

### 1. Create Booteable micro-SD card

The SD card needs to be loaded with the necessary files to support hardware management and software resources that provides common services for computer programs, also known as the Operating System (OS).

- Download ISO (.img) file from: 

https://github.com/parallella/parabuntu/releases/tag/parabuntu-2019.1-beta1

- Open a terminal

`Ctrl+Alt+T`

- Change directory to where the ISO file is located

```
cd <Downloads_Directory>
```

- Check current devices

```
lsblk
```
```
df -h
```

- Insert SD card into SD reader and check the name of the SD card (usually starts with mmcblk0 or sdb)

```
lsblk
```
```
df -h
```

- Unmount the SD card

```
umount <sd-partition-path>
```

- Write the image to the SD card, where <d_name> is the SD card name

```
sudo dd bs=4M if=<parabuntu_filename>.img of=/dev/<d_name> status=progress
```

- Make sure all writes to the SD card have completed
```
sync
```
> *Note: Check the version of the board (z7010/z7020) to use the correct ISO*

- Resize partition using gparted to use all available space

```
gparted
```

### 2. Eject micro-SD card and put it in board

### 3. Connect periherals 
- Connect Ethernet cable to the board and the router 
- Power on the cooling fan
- Connect power source to the board

### 4. Get IP [default_ip] assigned in router the interface

### 5. Try to connect to the board through ssh using the terminal

```
ssh parallella@[default_ip]
```

> *Syntax: ssh [remoteuser]@[remotehost]*

If this command is successful, it will attempt to login to the board and start a remote session. Allow the board to add your fingerprint (y/yes), your fingerprint will be added to the file `~/.ssh/known_hosts`.

### 6. Test the Epiphany co-processor before continuing

> Note: `game-of-life` files are part of the Parallella GitHub examples `(ToDo: Add_Link)`

Open a new terminal (B) and go to the `DERFAST/Modules/A_Single_Core/A_2` directory, if it is located in home use:

```
cd ~/DERFAST/Modules/A_Single_Core/A_2
```

> *Note: ~ expands to the home directory*

In terminal (B), copy the directory `game-of-life-v2` in `DERFAST/Modules/A_Single_Core/A_2` to the board using scp.

```
scp -r game-of-life-v2 parallella@[default_ip]:/home/parallella
```

> *Syntax: scp [file_name] [remoteuser]@[remotehost]:[/remote/directory]*

Run epiphany example to validate correct installation 

```
cd game-of-life-v2
```

```
./build.sh; ./main.elf 3
```

The expected outcome may differ every time! Here is an example :

```
X	X	X	X	X	X
X	O	X	X	O	X
X	O	O	O	O	X
X	O	O	O	X	X
X	O	X	O	O	X
X	X	X	X	X	X

X	X	X	X	X	X
X	O	X	X	O	X
X	X	O	O	O	X
X	O	O	O	X	X
X	O	X	O	O	X
X	X	X	X	X	X

X	X	X	X	X	X
X	O	O	O	O	X
X	O	O	X	O	X
X	X	O	X	O	X
X	O	O	O	O	X
X	X	X	X	X	X
```

> Note: It is also possible to get more examples with the github repository from Parallella using git clone

If the co-processor is not working, try reinstalling the OS in the SD card [Step 1.](#1-create-booteable-micro-sd-card)

### 7. Setup Board Hostname

The board's hostname is a combination of alphanumeric characters used to identify each board. DEMAC follows a namescheme where each board is named NOPA##, where ## is a unique 2-digit ID. For example, board 01 will be NOPA01.

#### Single-Node

Edit the file `/etc/hostname`

```
sudo vim /etc/hostname
```
Remove the default name "parallella" and replace it with:
```
NOPA01
```

#### Multi-Node 

In a multi-node system, each node needs a unique hostname. Choose a naming scheme that aligns with the objective of the project. For example, in the 24-board version of DEMAC, boards are named NOPA01-NOPA24. Learn more about multi-node setup [here](../../D_Multiple_Nodes/D_2/README.md).

Remove the default name "parallella" and replace it with (## is the board ID number):
```
NOPA##
```


### 8. Setup IP

There are two options to set a fixed IP for the board in the network. 

#### Setup IP in the router interface

Log into the router configuration interface, each router's interface might be different and provide support for different features. Using this interface you can set up a static IP 

#### Setup Static IP in the board

- Edit `/etc/netplan/*.yaml`

```
sudo vim /etc/netplan/*.yaml
```

The contents of the file should look like this, replace ## for the board's ID. 

```
network:
 ethernets:
  eth0:
      	addresses: [192.168.10.1##/24]
      	gateway4: 192.168.10.1
      	dhcp4: true
      	optional: true
      	nameservers:
              	addresses: [8.8.8.8,8.8.4.4]
 version: 2
 ```

```
sudo netplan apply
```

> Note: The procedure to set up an static IP might differ for different linux versions or distributions. 

### 9. Reboot
 
- Reboot the board to apply the changes.

```
sudo reboot -f
```

### 10. Update && Upgrade

```
sudo apt-get update
```

```
sudo apt-get upgrade -y
```

To continue assembling the 4-Unit rack follow ["D.2. DEMAC: A distributed memory architecture"](../../D_Multiple_Nodes/D_2/README.md)


