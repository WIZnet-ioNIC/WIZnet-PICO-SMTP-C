#ifndef _SMTP_H_
#define _SMTP_H_

#ifdef __cplusplus
extern "C" {
#endif

enum run_state
{
    waitfor220 = 0,
    waitforHELO250,
    waitforAUTH334,
    waitforuser334,
    waitforpassword235,
    waitforsend250,
    waitforrcpt250,
    waitfordate354,
    waitformime250
};

void send_mail(uint8_t sock);
void mailmessage(void);
void base64encode(char *s, char *r);
void str_insert(char *s1, char *s2, int pos);
uint8_t smtp_init(uint8_t sock, uint8_t * ip, uint16_t port, uint8_t * buf);
void smtp_run();

#ifdef __cplusplus
}
#endif

#endif