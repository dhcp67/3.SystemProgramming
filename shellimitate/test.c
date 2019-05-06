/*************************************************************************
	> File Name: test.c
	> Author: lichun
	> Mail: 318082789@qq.com
	> Created Time: 2019年04月27日 星期六 22时29分52秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main() {
    char com[100] = {0};
    char secom[200] = {0};
    scanf("%[^\n]", com);
    getchar();
    int ret = 0;
    int j = 0;
    for(int i = 0; i < strlen(com); i++) {
        if (ret) {
            j = i;
            break;
        }
        if(com[i] != ' ') {
            j++;
            if (j != i) {
                com[j] = com[i];
                com[i] = 0;
            }
            if (com[i + 1] == 0 || com[i + 1] == ' ') ret = 1;
        }
    }
    printf("%d  %s\n",j, com);
    return 0;
}
