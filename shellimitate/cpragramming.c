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

void printtype_user_root(char *,char *, char *);
int second_com(char com[], char secom[], char *temp);
void pwd_now(char se[], char *te);

char opwd[2][100] = {0};
int ret = 0;
int prinout = 1;

int main() {
    signal(SIGINT, SIG_IGN);
    char hostname[100];
    char *username = getenv("LOGNAME");
    gethostname(hostname,sizeof(hostname));
    char pwd[100] = {0};
    char com[500] = {0};
    char secom[300] = {0};
    int num = 0;
    getcwd(pwd,100);
    signal(SIGINT, SIG_IGN);
    while(strcmp(com, "exit")) {
        if(!strcmp(com, "cd")) {
            chdir(secom);
        }
        getcwd(pwd,100);
        num && strcpy(pwd,opwd[ret]);
        printtype_user_root(username, hostname, pwd);
        strcpy(opwd[ret], pwd); 
        memset(com, 0, 49);
        memset(secom, 0, 99);
        scanf("%[^\n]", com);
        getchar();
        num = second_com(com, secom, username); 
    } 

	return 0;

}

void printtype_user_root(char *username, char *hostname,char *pwd) {
    printf("\033[32;1m%s@%s\033[0m:", username, hostname);
    int digit = -3;
        printf("\033[34;1m%s\033[0m", pwd);
    
    //if(prinout == 3) {
    //    printf("\033[34;1m%s/\033[0m", pwd);
    //}else {for(int i = 0; i < strlen(pwd); i++) {
    //    if (!i) {
    //        if(prinout == 2) {
    //            printf("\033[34;1m/\033[0m");
    //        }else if(prinout == 1) { 
    //            printf("\033[34;1m~\033[0m");
    //        } else  {
    //            printf("\033[34;1m~/\033[0m");
    //        }
    //    }
    //    if(digit == 0) {
    //        printf("\033[34;1m%c\033[0m", pwd[i]);
    //    } else if(pwd[i] == '/') {
    //        digit++;
    //    }
    //}
    //}
    prinout = 0;
    strcmp(username, "root") ? printf("$ ") : printf("# ");
}

int second_com(char com[], char secom[], char *temp) {
    ret = (!ret);
    int len = strlen(com);
    int n = 0, j = 0;
    int cnt = 0, int comlag = 1;
    for(int i = 0; i < len; i++) {
        if(com[i] == " ") {
            comlag = 0;
        }
        if(n) {
            secom[j] = com[i];
            com[i] = 0;
            j++;
        } else if(com[i] == ' ') {
            n = 1;
            com[i] = 0;
        }
    }
    //if(!strcmp(com, "cd") && (secom[0] == '-')) {
    //    cnt = (!cnt);
    //} else if(!strcmp(com, "cd") && (secom[0] == '/' && (secom[1] == ' ' ||
    //        secom[1] == 0))) {
    //    prinout = 2;
    //        } else if(!strcmp(com, "cd") && (secom[0] == '/')) {
    //            prinout = 3;
    //        }
    //else if(!strcmp(com, "cd") && (secom[0] == '~')) {
    //    pwd_now(secom, temp);
    //    prinout = 1;
    //} else if(!strcmp(com, "cd") && secom[0] == 0) {
    //    sprintf(secom, "/home/%s", temp);
    //    prinout = 1;
    //}
    return cnt;
}

void pwd_now(char se[], char *te) {
    int len = strlen(se);
    char swap[1000] = {0};
    sprintf(swap, "/home/%s", te);
    prinout = 1;
    for(int i = 1; i < len; i++) {
        sprintf(swap, "%s%c", swap, se[i]);
    }
    strcpy(se, swap);
}
