# How to Test FTP_Client Example



## Step 1: Prepare software

The following serial terminal program is required for ftp_client test, download and install from below links.

- [**Tera Term**][link-tera_term]
- [**Hercules**][link-hercules]
- [**FileZilla Server Interface**][link-filezilla_server]



## Step 2: Prepare hardware

1. Combine WIZnet Ethernet HAT with Raspberry Pi Pico.

2. Connect ethernet cable to WIZnet Ethernet HAT ethernet port.

3. Connect Raspberry Pi Pico to desktop or laptop using 5 pin micro USB cable.

If you use W5100S-EVB-Pico, you can skip '1. Combine...'



## Step 3: Setup FTP_Client Example

To test the ftp_client example, minor settings shall be done in code.

1. Setup SPI port and pin.

Setup the SPI interface you use.

```cpp
/* SPI */
#define SPI_PORT spi0

#define PIN_SCK 18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_RST 20
```

If you want to test with the ftp_client example using SPI DMA, uncomment USE_SPI_DMA.

```cpp
/* Use SPI DMA */
//#define USE_SPI_DMA // if you want to use SPI DMA, uncomment.
```



2. Setup network configuration such as IP.

Setup IP and other network settings to suit your network environment.

```cpp
/* Network */
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 1, 15},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 1, 1},                      // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
        .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};
```

3. Setup ftp_client configuration in ftpc.c file.(route: RP2040-HAT-C\libraries\ioLibrary_Driver\Internet\FTPClient\ftpc.c)

```cpp
uint8_t FTP_destip[4] = {192, 168, 1, 2};		// For FTP client examples; destination network info
uint16_t FTP_destport = 21;						// For FTP client examples; destination network info
```



## Step 4: Setup FileZilla Server program

1. Execute FileZilla Server program and open FTP server.

![][link-filezilla_server_program_open]

2. Add user and Set password

![][link-filezilla_add_user]

3. Set folder path to share

![][link-filezilla_set_path]

4. General sttings

![][link-filezilla_general_settings]



## Step 5: Build

1. After completing the ftp_client example configuration, click 'build' in the status bar at the bottom of Visual Studio Code or press the 'F7' button on the keyboard to build.

2. When the build is completed, 'w5x00_ftp_client.uf2' is generated in 'RP2040-HAT-C/build/examples/ftp/client' directory.



## Step 6: Upload and Run

1. While pressing the BOOTSEL button of Raspberry Pi Pico power on the board, the USB mass storage 'RPI-RP2' is automatically mounted.

![][link-raspberry_pi_pico_usb_mass_storage]

2. Drag and drop 'w5x00_ftp_client.uf2' onto the USB mass storage device 'RPI-RP2'.

3. Connect to the serial COM port of Raspberry Pi Pico with Tera Term.

![][link-connect_to_serial_com_port]

4. Reset your board.

5. If the ftp_clinet example works normally on Raspberry Pi Pico, you can see the network information of Raspberry Pi Pico and the FileZilla web site.

![][link-see_network_information_of_raspberry_pi_pico]

6. Input the user ID(You created in step 4.)

![][link-input_user_id]

7. Input the password

![][link-input_password]

8. Press number '1'

![][link-press_num1]

9. You can see FTP server directory

![][link-ftp_server_directory]

10. Wireshark packet capture

![][link-ftp_wireshark_result]

<!--
Link
-->

[link-tera_term]: https://osdn.net/projects/ttssh2/releases/
[link-hercules]: https://www.hw-group.com/software/hercules-setup-utility
[link-filezilla]: https://osdn.net/projects/filezilla/downloads/67734/FileZilla_Server-0_9_60.exe/


[link-filezilla_server_program_open]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/filezilla_server_program_open.png
[link-filezilla_add_user]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/filezilla_add_user.png
[link-filezilla_set_path]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/filezilla_set_path.png
[link-filezilla_general_settings]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/filezilla_general_settings.png



[link-raspberry_pi_pico_usb_mass_storage]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/raspberry_pi_pico_usb_mass_storage.png
[link-connect_to_serial_com_port]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/serial_com_port.png
[link-see_network_information_of_raspberry_pi_pico]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/network_information.png
[link-input_user_id]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/input_user_id.png
[link-input_password]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/input_password.png
[link-press_num1]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/press_num1.png
[link-ftp_server_directory]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/ftp_server_directory.png
[link-ftp_wireshark_result]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/ftp/client/ftp_wireshark_result.png
