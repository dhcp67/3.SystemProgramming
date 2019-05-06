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
char tempwd[2][LEN];
int pwdflag = 1;

enum {
    EXIT,
    ERROR,
    CD,
    CD_PREVIOUS,//cd - previous occasion
    LS,
    LS_AL
};

int sec_com(char *);//命令拆分
int cd_lscom(char *com);//命令区分
int print_command(int concom);//输出

int main() {
    //signal(SIGINT, SIG_IGN);
    struct passwd *p;
    p = getpwuid(getuid());
    strcpy(username, p->pw_name);
    //strcpy(pwd, p->pw_dir);
    strcpy(pwd, getenv("PWD"));
    gethostname(hostname, LEN);

    char com[LEN];
    int len = 0, ret = CD;
    while(ret != EXIT) {
        if(ret == CD) {
            if(chdir(secom[1]) == 0){
                memset(pwd, 0, LEN);
                getcwd(pwd, LEN);
            }
        }
        print_command(ret);
        fgets(com, LEN, stdin);
        len = sec_com(com);
        ret = cd_lscom(com);
    } 

	return 0;
}

int sec_com(char *com) {
    int ret = 0, i, j = 0;
    int len = strlen(com) - 1;
    printf("%d\n",len);
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

int cd_lscom(char *com) {
    int concom = -1;
    if(strcmp(secom[0], "cd") == 0) {//如果命令是cd
             if((strcmp(secom[1], "~") == 0 && strcmp(secom[2], "\0")) || strcmp(secom[1], "\0") == 0) {
                sprintf(secom[1], "/home/%s", username);
             } else if(strcmp(secom[1], "-") == 0) {
                 strcpy(tempwd[pwdflag], pwd);
                 pwdflag = !pwdflag;
                 strcpy(secom[1], tempwd[pwdflag]);
             }
            concom = CD;
        //if(ii == 0 && strcmp(pwd, tempwd[pwdflag]) != 0) {
        //    strcpy(tempwd[pwdflag], pwd);
        //    pwdflag = !pwdflag;
        //}
    } else if(strcmp(secom[0], "ls") == 0) {//如果命令是ls
        if(!strcmp(secom[1], "-al")) {
            concom = LS_AL;
        } else {
            concom = LS;
        }
    } else if(strcmp(secom[0], "exit") == 0 && strcmp(secom[1], "\0") == 0) {
        concom = EXIT;
    } else{
        concom = CD;    
    }
    return concom;
}
int print_command(int concom) {
    char home[LEN];
    sprintf(home,"/home/%s", username);
    if(concom == CD) {
        printf("\033[32;1m%s@%s\033[0m:\033[34;1m%s\033[0m", username, hostname, pwd);
        if(strcmp(username, "root") == 0) {
            printf("# ");
        } else {
            printf("$ ");
        }
        
    }
    if(concom == LS_AL) {
        
    }
    for(int i = 0; i < LEN; i++) {
        strcpy(secom[i],"\0");
    }
    return concom;
}
