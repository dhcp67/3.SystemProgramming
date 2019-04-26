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
#define len_size 200

void printtype_user_root(char *,char *, char *);
void second_com(char com[], char secom[], char temp[]);
void pwd_now(char se[], char te[]);

int main() {
    char hostname[len_size] = {0};
    char username[len_size] = {0};
    char pwd[len_size] = {0};
    char com[len_size] = {0};
    char secom[len_size] = {0};
    strcpy(username,getenv("LOGNAME"));
    scanf("%[^\n]", com);
    getchar();
    int ret = 1;
    do {
        if(!strcmp(com, "cd")) {
            if(!chdir(secom)) {
                ret = 1;
            }
        }
        ret && getcwd(pwd,len_size);
        ret--;
        printtype_user_root(username, hostname, pwd);
        memset(com, 0, len_size);
        memset(secom, 0, len_size);
        fgets(com, len_size, stdin);
        //scanf("%s[^\n]", com);
        //getchar();
        second_com(com, secom, username); 
    } while(strcmp(com, "exit"));

	return 0;

}

void printtype_user_root(char *username, char *hostname,char *pwd) {
    int cnt = 0, ret = 3,i = 0;
        printf("\033[32;1m%s@%s\033[0m:\033[34;1m%s\033[0m", username, hostname, pwd);
        strcmp(username, "root") ? printf("$"): printf("#"); 
}

void second_com(char com[], char secom[], char temp[]) {
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
    if(!strcmp(com, "cd") && (secom[0] == '~')) {
        pwd_now(secom, temp);
    }
}

void pwd_now(char se[], char te[]) {
    int len = strlen(se);
    char swap[1000] = {0};
    sprintf(swap, "/home/%s", te);    
    for(int i = 1; i < len; i++) {
        sprintf(swap, "%s%c", swap, se[i]);
    }
    strcpy(se, swap);
}
