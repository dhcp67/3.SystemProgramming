/*************************************************************************
	> File Name: test.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月27日 星期六 22时29分52秒
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    struct stat buf;
    stat("a.out", &buf);
    printf("%d\n", buf.st_ino);
    return 0;
}
