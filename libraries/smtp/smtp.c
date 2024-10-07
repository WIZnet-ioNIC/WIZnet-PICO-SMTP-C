#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "wizchip_conf.h"

#include "smtp.h"

static uint8_t SMTP_STATE = waitfor220;

static uint8_t smtp_server_ip[4];
static uint8_t smtp_server_port;
static uint8_t stmp_sock;
static char *p_rx_buf;

extern uint8_t Mail_Send_OK;

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

void mailmessage(void) 
{
  uint16_t len_from = strlen(from);
  uint16_t len_to = strlen(to);
  uint16_t len_Cc = strlen(Cc);
  uint16_t len_sub = strlen(subject);
  strcat(hello, "\r\n");
  str_insert(mailfrom, from, 11);
  strcat(mailfrom, "\r\n");
  str_insert(rcptto, to, 9);
  strcat(rcptto, "\r\n");
  strcat(data_init, "\r\n");

  str_insert(mime, from, 5);
  str_insert(mime1, to, 3);
  str_insert(mime2, Cc, 3);
  str_insert(mime3, subject, 8);
  str_insert(mime5, content, 0);
  strcat(mime, mime1);
  strcat(mime, mime2);
  strcat(mime, mime3);
  strcat(mime, mime4);
  strcat(mime, mime5);
}

void send_mail(uint8_t sock) // send mail
{
  int ret;
  switch (SMTP_STATE)
  {
  case waitfor220:
    if (strstr((const char *)p_rx_buf, "220") != NULL)
    {
      ret = send(sock, (uint8_t *)hello, strlen(hello));
      SMTP_STATE = waitforHELO250;
    }
    else
    {
      printf("Connected failed!\r\n");
    }
    break;
  case waitforHELO250:
    if (strstr((const char *)p_rx_buf, hello_reply) != NULL && strstr((const char *)p_rx_buf, "Mail") == NULL)
    {
      ret = send(sock, (uint8_t *)mailfrom, strlen(mailfrom));
      SMTP_STATE = waitforsend250;
    }
    else
    {
      printf("smtp handshake failed!\r\n");
    }
    break;
  case waitforsend250:
    if (strstr((const char *)p_rx_buf, from_reply) != NULL && strstr((const char *)p_rx_buf, "queued as") == NULL)
    {
      ret = send(sock, (uint8_t *)rcptto, strlen(rcptto));
      SMTP_STATE = waitforrcpt250;
    }
    else
    {
      printf("Send email failed to set up!\r\n");
    }
    break;
  case waitforrcpt250:
    if (strstr((const char *)p_rx_buf, to_reply) != NULL)
    {
      ret = send(sock, (uint8_t *)data_init, strlen(data_init));
      SMTP_STATE = waitfordate354;
    }
    else
    {
      printf("Failed to set the receiving mailbox!\r\n");
    }
    break;
  case waitfordate354:
    if (strstr((const char *)p_rx_buf, data_reply) != NULL)
    {
      ret = send(sock, (uint8_t *)mime, strlen(mime));
      SMTP_STATE = waitformime250;
    }
    else
    {
      printf("Failed to send content setup\r\n");
    }
    break;
  case waitformime250:
    if (strstr((const char *)p_rx_buf, mime_reply) != NULL)
    {
      Mail_Send_OK = 1;
      printf("mail send OK\r\n");
    }
    break;
  default:
    break;
  }
}

uint8_t smtp_init(uint8_t sock, uint8_t * ip, uint16_t port, uint8_t * buf)
{
  if(sock <= _WIZCHIP_SOCK_NUM_)
  {
    stmp_sock = sock;

    smtp_server_ip[0] = ip[0];
    smtp_server_ip[1] = ip[1];
    smtp_server_ip[2] = ip[2];
    smtp_server_ip[3] = ip[3];
    smtp_server_port = port;

    p_rx_buf = buf;

    return 1;
  }
  return 0;
}

void smtp_run() 
{
  uint8_t ret = 0;
  uint32_t len = 0;
  uint16_t anyport = 5000;
  
  switch (getSn_SR(stmp_sock))
  {
    case SOCK_INIT:
      ret = connect(stmp_sock, smtp_server_ip, smtp_server_port);
      break;
    case SOCK_ESTABLISHED:
      if (getSn_IR(stmp_sock) & Sn_IR_CON)
      {
        setSn_IR(stmp_sock, Sn_IR_CON);
      }
      while (!Mail_Send_OK)
      {
        len = getSn_RX_RSR(stmp_sock);
        if (len > 0)
        {
          memset(p_rx_buf, 0, len);
          len = recv(stmp_sock, (uint8_t *)p_rx_buf, len);
          send_mail(stmp_sock);
        }
      }
      disconnect(stmp_sock);
      break;
    case SOCK_CLOSE_WAIT:
      if ((len = getSn_RX_RSR(stmp_sock)) > 0)
      {
        while (!Mail_Send_OK)
        {
          len = recv(stmp_sock, (uint8_t *)p_rx_buf, len);
          send_mail(stmp_sock);
        }
      }
      disconnect(stmp_sock);
      break;
    case SOCK_CLOSED:
      socket(stmp_sock, Sn_MR_TCP, anyport++, 0x00);
      break;
    default:
      break;
  }
}

void str_insert(char *s1, char *s2, int pos) 
{
  int i;
  int len = strlen(s2);
  for (i = 0; i < len; i++)
  {
    *(s1 + pos + len + i) = s1[pos + i];
    *(s1 + pos + i) = s2[i];
  }
}
