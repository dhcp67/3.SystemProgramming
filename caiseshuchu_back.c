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
void second_com(char com[], char secom[], char *temp);
void pwd(char se[], char *);

int main() {
    char hostname[100];
    char *username = getenv("LOGNAME");
    gethostname(hostname,sizeof(hostname));
    char pwd[100] = {0};
    char com[500] = {0};
    char secom[1000] = {0};
    int ret = 1;
    while(strcmp(com, "exit")) {
        if(!strcmp(com, "cd")) {
            if(!chdir(secom)) {
                ret = 1;
            }
        }
        ret && getcwd(pwd,100);
        ret--;
        printtype_user_root(username, hostname, pwd);
        memset(com, 0, 49);
        memset(secom, 0, 99);
        gets(com);
        //scanf("%s[^\n]", com);
        //getchar();
        second_com(com, secom, username); 
    } 

	return 0;

}

void printtype_user_root(char *username, char *hostname,char *pwd) {
    int cnt = 0, ret = 3,i = 0;
        printf("\033[32;1m%s@%s\033[0m:\033[34;1m%s\033[0m", username, hostname, pwd);
        strcmp(username, "root") ? printf("$"): printf("#"); 
}

void second_com(char com[], char secom[], char *temp) {
    int len = strlen(com);
    int ret = 0, j = 0;
    for(int i = 0; i < len; i++) {
        if(ret) {
            secom[j] = com[i];
            com[i] = 0;
            j++;
        } else if(com[i] == ' ') {
            ret = 1;
            com[i] = 0;
        }
    }
    !strcmp(com, "cd") && secom[0] == "~" && pwd(secom, temp);
}

pwd(char se[], char *te) {
    
}
