#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SinhVien {
    int id;
    int age;
    char name[50];
};
void printfSV(struct SinhVien *sv, int size);
void addSV(struct SinhVien *sv, int *size);
void editSV(struct SinhVien *sv, int size);
void deleteSV(struct SinhVien *sv, int *size);
void writeToFile(struct SinhVien *sv, int size);
void sortSV(struct SinhVien *sv, int size);
void searchSV(struct SinhVien *sv, int size);
int main() {
    struct SinhVien sv[100];
    int size = 0;
    int choice;
    FILE *file;
    do {
        printf("**********MENU***********\n");
        printf("1. In danh sach sinh vien \n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Thoat\n");
        printf("Moi ban chon chuc nang tu (1-7): ");
        scanf("%d", &choice);
        getchar(); 
        switch(choice) {
            case 1:
                printfSV(sv, size);
                break;
            case 2:
                addSV(sv, &size);
                writeToFile(sv, size); 
                break;
            case 3:
                editSV(sv, size);
                writeToFile(sv, size); 
                break;
            case 4:
                deleteSV(sv, &size);
                writeToFile(sv, size); 
                break;
            case 5:
                searchSV(sv, size);
                break;
            case 6:
                sortSV(sv, size);
                writeToFile(sv, size);  
                break;
            case 7:
                printf("Da thoat chuong trinh\n");
                break;
            default:
                printf("Loi du lieu, hay nhap lai!\n");
                break;
        }
    } while(choice != 7);

    return 0;
}

void printfSV(struct SinhVien *sv, int size) {
    if (size == 0) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    printf("Danh sach sinh vien:\n");
    printf("ID\tName\tAge\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%s\t%d\n", sv[i].id, sv[i].name, sv[i].age);
    }
}
void addSV(struct SinhVien *sv, int *size) {
    if (*size >= 100) {
        printf("Danh sach sinh vien da day, khong the them moi!\n");
        return;
    }
    struct SinhVien newSV;
    printf("Nhap ID: ");
    scanf("%d", &newSV.id);
    getchar(); 
    printf("Nhap ten: ");
    fgets(newSV.name, sizeof(newSV.name), stdin);
    newSV.name[strcspn(newSV.name, "\n")] = 0;  
    printf("Nhap tuoi: ");
    scanf("%d", &newSV.age);
    sv[*size] = newSV;
    (*size)++;
    printf("Sinh vien da duoc them.\n");
}
void editSV(struct SinhVien *sv, int size) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++) {
        if (sv[i].id == id) {
            printf("Sinh vien tim thay: %d, %s, %d\n", sv[i].id, sv[i].name, sv[i].age);
            printf("Cap nhat ten moi: ");
            getchar();  
            fgets(sv[i].name, sizeof(sv[i].name), stdin);
            sv[i].name[strcspn(sv[i].name, "\n")] = 0; 
            printf("Cap nhat tuoi moi: ");
            scanf("%d", &sv[i].age);
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }
    printf("Sinh vien voi ID %d khong ton tai.\n", id);
}
void deleteSV(struct SinhVien *sv, int *size) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *size; i++) {
        if (sv[i].id == id) {
            for (int j = i; j < *size - 1; j++) {
                sv[j] = sv[j + 1];
            }
            (*size)--;
            printf("Sinh vien da duoc xoa.\n");
            return;
        }
    }
    printf("Sinh vien %d khong ton tai.\n", id);
}
void searchSV(struct SinhVien *sv, int size) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++) {
        if (sv[i].id == id) {
            printf("Sinh vien tim thay: %d, %s, %d\n", sv[i].id, sv[i].name, sv[i].age);
            return;
        }
    }
    printf("Sinh vien ID %d khong ton tai.\n", id);
}
void sortSV(struct SinhVien *sv, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (sv[i].id > sv[j].id) {
                struct SinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep theo ID.\n");
}
void writeToFile(struct SinhVien *sv, int size) {
    FILE *file = fopen("students.bin", "wb");
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);  
    fwrite(sv, sizeof(struct SinhVien), size, file);  
    fclose(file);
}
