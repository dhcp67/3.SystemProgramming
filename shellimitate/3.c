/*************************************************************************
	> File Name: caiseshuchu.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月15日 星期一 16时27分37秒
 ************************************************************************/

#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#define LEN 256

char secom[LEN][LEN];

char hostname[LEN];
char username[LEN];
char pwd[LEN];

int sec_command(int);//命令拆分
int cd_lscom(char secom[][LEN]);//命令区分
int print_command(int concom);//输出

int main() {
    //signal(SIGINT, SIG_IGN);
    struct passwd *p;
    p = getpwuid(getuid());
    strcpy(username, p->pw_name);
    strcpy(pwd, p->pw_dir);
    gethostname(hostname, LEN);

    char com[LEN];
    int len = 0;
    while(strcmp(secom[0], "exit")) {
        int scom = cd_lscom(secom);
        print_command(scom);
        fgets(com, LEN, stdin);
        len = secondcom_com(com);
    } 

	return 0;
}

int sec_com(char *com) {
    int ret = 0, i, j = 0;
    int len = strlen(com) - 1;
    for(i = 0; i < len; i++) {
        if(com[i] != ' ') {
            secom[j][ret++] = com[i];
        } else if(ret) {
            secom[j][ret] = '\0';
            j++;
            ret = 0;
        }
    }
    if(ret) {
        secom[j][ret] = '\0';
        j++;
    }
    len = j;
    return len;
}

int cd_lscomc(char scom[][LEN]) {
    int concom = 0;
    if(!strcmp(secom[0], "cd")) {//如果命令是cd
        
    } else if(!strcmp(secom[0], "ls")) {//如果命令是ls

     }
    return concom;
}
int print_command(int concom) {
    return 0;
}
