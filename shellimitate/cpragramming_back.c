/*************************************************************************
	> File Name: caiseshuchu.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月15日 星期一 16时27分37秒
 ************************************************************************/

#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <math.h>
#define LEN 256

char secom[LEN][LEN];
char hostname[LEN];
char username[LEN];
char pwd[LEN];
char tempwd[2][LEN];
int pwdflag = 1;

enum {
    NO_COM,
    EXIT,
    CD_ERROR,
    CD,
    CD_YES,
    CD_PREVIOUS,//cd - previous occasion
    LS,
    LS_AL,
    CP
};

int sec_com(char *);//命令拆分
int cd_lscom(char *);//命令区分
int print_command(int );//输出
void ls_print(int );

int main() {
    //signal(SIGINT, SIG_IGN);
    struct passwd *p;
    p = getpwuid(getuid());
    strcpy(username, p->pw_name);
    //strcpy(pwd, p->pw_dir);
    strcpy(pwd, getenv("PWD"));
    gethostname(hostname, LEN);

    char com[LEN];
    int len = 0, ret = NO_COM;
    while(ret != EXIT) {
        if(ret == CD || ret == CD_PREVIOUS) {
            if(chdir(secom[1]) == 0 && ret != NO_COM){
                memset(pwd, 0, LEN);
                getcwd(pwd, LEN);
                ret = CD_PREVIOUS;
            } else {
                ret = CD_ERROR;
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
    int concom = NO_COM;
    if(strcmp(secom[0], "cd") == 0) {//如果命令是cd
             if((!strcmp(secom[1], "~") && !strcmp(secom[2], "\0")) || strcmp(secom[1], "\0") == 0) {
                sprintf(secom[1], "/home/%s", username);
                concom = CD;;
             } else if(strcmp(secom[1], "-") == 0) {//未完
                 strcpy(tempwd[pwdflag], pwd);
                 pwdflag = !pwdflag;
                 strcpy(secom[1], tempwd[pwdflag]);
                 concom = CD_PREVIOUS;
             } else if(strcmp(secom[2], "\0") == 0){
            concom = CD;
             } else {
                 concom = CD_ERROR;
             }
    } else if(strcmp(secom[0], "ls") == 0) {//如果命令是ls
        if(!strcmp(secom[1], "-al")) {
            concom = LS_AL;
        } else {
            concom = LS;
        }
    } else if(strcmp(secom[0], "cp") == 0) {
        concom = CP;
    }else if(strcmp(secom[0], "exit") == 0 && strcmp(secom[1], "\0") == 0) {
        concom = EXIT;
    }
    return concom;
}
int print_command(int concom) {
    if(concom == CD_ERROR) {
        printf("error\n");
    }
    if(concom == LS || concom == LS_AL) {
        ls_print(concom);
    }
    char home[LEN];
    sprintf(home,"/home/%s", username);
    printf("\033[32;1m%s@%s\033[0m:\033[34;1m%s\033[0m", username, hostname, pwd);
    if(strcmp(username, "root") == 0) {
        printf("# ");
    } else {
        printf("$ ");
    }
    for(int i = 0; i < LEN; i++) {
        strcpy(secom[i],"\0");
    }
    return concom;
}

void ls_print(int concom) {
    if(concom == LS) {
        struct stat buf;
        if(strcmp(secom[1], "\0") == 0) {
            DIR *dir;
            dir = opendir(pwd);
            struct dirent *file;
            while((file = readdir(dir)) != NULL) {
                printf("%s\t", file->d_name);
            }
        } else {
            for(int i = 1; strcmp(secom[i], "\0") != 0;i++) {
                if(stat(secom[i], &buf) == 0) {
                    printf("%s ", secom[i]);
                }
            }
        }
        printf("\n");
    } else if(concom == LS_AL) {
        struct stat buf;
        DIR *dir;
        if(strcmp(secom[2], "\0") == 0) {
            struct dirent *file;
            dir = opendir(pwd);
            while((file = readdir(dir)) != NULL) {
                stat(file->d_name, &buf);
                int ret = file->d_type;
                switch (ret) {
                case 1:
                    printf("p");
                    break;
                case 2:
                    printf("c");
                    break;
                case 4:
                    printf("d");
                    break;
                case 6:
                    printf("f");
                    break;
                case 8:
                    printf("-");
                    break;
                case 10:
                    printf("-");
                    break;
                default:
                    printf("-");
                }
            int cnt = buf.st_mode;
            char tempchar;
            // debug <<<<<<<<<<-----------------------------
            printf("%c", tempchar = ((cnt / 100 == 4) ? 'r' : '-'));
            printf("%c", tempchar = ((cnt / 100 == 2) ? 'w' : '-'));
            printf("%c", tempchar = ((cnt / 100 == 2) ? 'x' : '-'));
            printf("%c", tempchar = ((cnt / 10 == 4) ? 'r' : '-'));
            printf("%c", tempchar = ((cnt / 10 == 2) ? 'w' : '-'));
            printf("%c", tempchar = ((cnt / 10 == 1) ? 'x' : '-'));
            printf("%c", tempchar = ((cnt / 1 == 4) ? 'r' : '-'));
            printf("%c", tempchar = ((cnt & 2) ? 'w' : '-'));
            printf("%c", tempchar = ((cnt & 1) ? 'x' : '-'));
            int num = log10(buf.st_mtime);
            printf(" %ld %s %s %6ld %ld %s\n", buf.st_nlink, username, username, buf.st_size, buf.st_mtime, file->d_name);
            }
        } else {
            for(int i = 2; strcmp(secom[i], "\0") != 0;i++) {
                if(stat(secom[i], &buf) == 0) {
                    printf(" %s\n", secom[i]);
                }
            }
        }
    } 
}
