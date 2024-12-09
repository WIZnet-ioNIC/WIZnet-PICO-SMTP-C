# How to Test SMTP Example



## Step 1: Prepare software

The following serial terminal programs are required for SMTP example test, download and install from below links.

- [**Tera Term**][link-tera_term]
- [**Hercules**][link-hercules]



## Step 2: Prepare hardware

If you are using W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2, you can skip '1. Combine...'

1. Combine WIZnet Ethernet HAT with Raspberry Pi Pico.

2. Connect ethernet cable to WIZnet Ethernet HAT, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 ethernet port.

3. Connect Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico to desktop or laptop using 5 pin micro USB cable. W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 require a USB Type-C cable.



## Step 3: Setup SMTP Example

To test the SMTP example, minor settings shall be done in code.

1. Setup SPI port and pin in 'w5x00_spi.h' in 'WIZnet-PICO-SMTP-C/port/ioLibrary_Driver/' directory.

Setup the SPI interface you use.
- If you use the W5100S-EVB-Pico, W5500-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2,

```cpp
/* SPI */
#define SPI_PORT spi0

#define PIN_SCK 18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_RST 20
```

If you want to test with the SMTP example using SPI DMA, uncomment USE_SPI_DMA.

```cpp
/* Use SPI DMA */
//#define USE_SPI_DMA // if you want to use SPI DMA, uncomment.
```
- If you use the W55RP20-EVB-Pico,
```cpp
/* SPI */
#define USE_SPI_PIO

#define PIN_SCK 21
#define PIN_MOSI 23
#define PIN_MISO 22
#define PIN_CS 20
#define PIN_RST 25
```

2. Setup network configuration such as IP in 'w5x00_smtp.c' which is the SMTP example in 'WIZnet-PICO-SMTP-C/examples/smtp/' directory.

Setup IP and other network settings to suit your network environment.

```cpp
/* Network */
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
        .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};
```

3. Setup smtp configuration in 'w5x00_smtp.c' in 'WIZnet-PICO-SMTP-C/examples/smtp/' directory.

```cpp
/* Port */
#define PORT_STMP 25
...
static uint8_t g_smtp_target_ip[4] = {192, 168, 11, 3};
```

Setup smtp message configuration in 'smtp.c'.
```cpp
char hello[50] = "HELO localhost";                       
char hello_reply[] = "250";                          
char from[] = "admin@demo.org";                        
char from_reply[] = "250";
char to[] = "wiznet@demo.org"; 
char to_reply[] = "250";
char data_init[10] = "data";                 
char data_reply[] = "354";                   
char Cc[] = "wiznet@demo.org";             
char subject[] = "Hello!WIZnet!";            
char content[] = "Hello!WIZnet!";            
char mime_reply[] = "250"; 
char mailfrom[50] = "MAIL FROM:<>";
char rcptto[50] = "rcpt to:<>";
char mime[200] = "From:\r\n";
char mime1[50] = "To:\r\n";
char mime2[50] = "Cc:\r\n";
char mime3[50] = "Subject:\r\n";
char mime4[50] = "MIME-Version:1.0\r\nContent-Type:text/plain\r\n\r\n";
char mime5[50] = "\r\n.\r\n";
```

## Step 4: Setup SMTP server

1. Setup IIS

![][link-setup_IIS]
   
2. Config SMTP mail
   
![][link-config_smtp_mail_1]

![][link-config_smtp_mail_2]

3. Download MailEnable
   
[**https://www.mailenable.com/download.asp**][link-mailenable]

![][link-download_mailenable_program]

 Check STMP port is listening 
 
![][link-check_smtp_port_listening]

Add user in mailbox

![][link-add_user_in_mailbox]


## Step 5: Build

1. After completing the SMTP example configuration, click 'build' in the status bar at the bottom of Visual Studio Code or press the 'F7' button on the keyboard to build.

2. When the build is completed, 'w5x00_smtp.uf2' is generated in 'WIZnet-PICO-SMTP-C/build/examples/smtp/' directory.



## Step 6: Upload and Run

1. While pressing the BOOTSEL button of Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 power on the board, the USB mass storage 'RPI-RP2' is automatically mounted.

![][link-raspberry_pi_pico_usb_mass_storage]

2. Drag and drop 'w5x00_smtp.uf2' onto the USB mass storage device 'RPI-RP2'.

3. Connect to the serial COM port of Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 with Tera Term.

![][link-connect_to_serial_com_port]

4. Reset your board.

5. If the SMTP example works normally on Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2, you can see the network information of Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 and the email is sent.

![][link-network_information]

6. You can check the email in the smtp server program.

![][link-check_recv_email_in_program]




<!--
Link
-->

[link-tera_term]: https://osdn.net/projects/ttssh2/releases/
[link-hercules]: https://www.hw-group.com/software/hercules-setup-utility
[link-mailenable]: http://www.mailenable.com/download.asp

[link-setup_IIS]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/setup_IIS.png
[link-config_smtp_mail_1]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/config_smtp_mail_1.png
[link-config_smtp_mail_2]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/config_smtp_mail_2.png
[link-download_mailenable_program]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/download_mailenable_program.png
[link-check_smtp_port_listening]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/check_smtp_port_listening.png
[link-add_user_in_mailbox]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/add_user_in_mailbox.png
[link-raspberry_pi_pico_usb_mass_storage]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/raspberry_pi_pico_usb_mass_storage.png
[link-connect_to_serial_com_port]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/connect_to_serial_com_port.png
[link-network_information]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/network_information.png
[link-check_recv_email_in_program]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-SMTP-C/blob/main/static/images/smtp/check_recv_email_in_program.png

