/*************************************************************************
	> File Name: test.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月24日 星期三 18时37分55秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    chdir("~/");
    char pwd[100] = {0};
    getcwd(pwd, 100);
    printf("%s\n", pwd);
    system("ls");
}
