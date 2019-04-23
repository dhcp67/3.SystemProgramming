/*************************************************************************
	> File Name: caiseshuchu.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月15日 星期一 16时27分37秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void printtype_user_root(char *,char *, char *);

int main() {
    char hostname[100];
    char *pwd;
    char *username = getenv("LOGNAME");
    gethostname(hostname,sizeof(hostname));
    pwd =getenv("PWD");
    printtype_user_root(username, hostname, pwd);

    return 0;

}

void printtype_user_root(char *username, char *hostname,char *pwd) {
    int cnt = 0, ret = 3,i = 0;
    if(strcmp(username,"root") != 0|| strlen(username) != 4) {
        printf("\033[32;1m%s@%s\033[0m:\033[34;1m%s\033[0m\n", username, hostname,pwd);
   }
    
    else printf("%s@%s:%s#\n", username, hostname, pwd);//root模式下
   
}
