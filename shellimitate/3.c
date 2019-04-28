/*************************************************************************
	> File Name: caiseshuchu.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月15日 星期一 16时27分37秒
 ************************************************************************/

#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define LEN 256

char secom[LEN][LEN];

int secondcom_com(char *);
char hostname[LEN];
char username[LEN];
char pwd[LEN];

int main() {
    //signal(SIGINT, SIG_IGN);
    gethostname(hostname,sizeof(hostname));
    char com[LEN];
    int len = 0;
    getcwd(pwd,100);
    while(strcmp(secom[0], "exit")) {
        fgets(com, LEN, stdin);
        len = secondcom_com(com);
        printf("<-\n");
    } 

	return 0;

}

int secondcom_com(char *com) {
    int ret = 0, i, j = 0;
    int len = strlen(com);
    for(i = 0; i < len; i++) {
        if(com[i] != ' ') {
            secom[j][ret++] = com[i];
        } else if(ret) {
            secom[j][ret] = '\0';
            j++;
            ret = 0;
        }
    }
    len = i;
    if(ret) {
        secom[j][ret - 1] = 'S';//<-test;
        secom[j][ret] = '\0';
    }
    secom[j + 1][0] = '\0';
    for(i = 0; i < len; i++) {
        printf("%s\n", secom[i]);
    }
    return len;
}
