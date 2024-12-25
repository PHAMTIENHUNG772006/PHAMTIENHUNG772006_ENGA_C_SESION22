#include <stdio.h>
#include <string.h>
struct Account {
    char username[30];
    char password[30];
};
void registerAccount(struct Account *accounts, int *size);
void login(struct Account *accounts, int size);
void loadAccounts(struct Account *accounts, int *size);
int main() {
    struct Account accounts[100];
    int size = 0;
    loadAccounts(accounts, &size);
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();  
        switch (choice) {
            case 1:
                login(accounts, size);
                break;
            case 2:
                registerAccount(accounts, &size);
                break;
            case 3:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long chon lai.\n");
        }
    } while (choice != 3);

    return 0;
}
void registerAccount(struct Account *accounts, int *size) {
    struct Account newAccount;
    int isUsernameExist;
    do {
        printf("Nhap tai khoan: ");
        fgets(newAccount.username, 30, stdin);
        newAccount.username[strcspn(newAccount.username, "\n")] = 0;  
        isUsernameExist = 0;
        for (int i = 0; i < *size; i++) {
            if (strcmp(accounts[i].username, newAccount.username) == 0) {
                isUsernameExist = 1;
                break;
            }
        }
        if (isUsernameExist) {
            printf("Tai khoan da ton tai, vui long chon tai khoan khac.\n");
        }
    } while (isUsernameExist);
    do {
        printf("Nhap mat khau: ");
        fgets(newAccount.password, 30, stdin);
        newAccount.password[strcspn(newAccount.password, "\n")] = 0;  
        char confirmPassword[30];
        printf("Xac nhan mat khau: ");
        fgets(confirmPassword,30, stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = 0;

        if (strcmp(newAccount.password, confirmPassword) != 0) {
            printf("Mat khau khong khop, vui long nhap lai.\n");
        } else {
            break;
        }
    } while (1);
    accounts[*size] = newAccount;
    (*size)++;
    FILE *file = fopen("accounts.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    fwrite(size, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct Account), *size, file);
    fclose(file);
    printf("Dang ky thanh cong!\n");
}




void login(struct Account *accounts, int size) {
    char username[30], password[30];
    printf("Nhap tai khoan: ");
    fgets(username, 30, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Nhap mat khau: ");
    fgets(password, 30, stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong!\n");
            return;
        }
    }
    printf("Dang nhap that bai!\n");
}
void loadAccounts(struct Account *accounts, int *size) {
    FILE *file = fopen("accounts.bin", "rb");
    if (file == NULL) {
        printf("Khong co file tai khoan.\n");
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(accounts, sizeof(struct Account), *size, file);
    fclose(file);
}
