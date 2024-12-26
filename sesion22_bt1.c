#include <stdio.h>
#include <string.h>

struct SinhVien {
    char id[20];
    char name[50];
    int age;
};

void printfSV();
void loadFileSv();
void addSV();
void saveFile();
void editSV(struct SinhVien *sv1, int numberStudent);
void deleteSV();
void seachSV(struct SinhVien *sv1, int numberStudent);
void sortSV(struct SinhVien *sv, int numberStudent);

struct SinhVien sv[100];
int numberStudent = 0;

int main() {
    int choice;
    loadFileSv();
    do {
        printf("\n**********MENU***********\n");
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
                printfSV();
                break;
            case 2:
                addSV();
                saveFile();
                break;
            case 3:
                editSV(sv, numberStudent);
                saveFile();
                break;
            case 4:
                deleteSV();
                saveFile();
                break;
            case 5:
                seachSV(sv, numberStudent);
                break;
            case 6:
                sortSV(sv, numberStudent);
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

void printfSV() {
    if (numberStudent == 0) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    for(int i = 0; i < numberStudent; i++) {
        printf("Danh sach sinh vien:\n");
        printf("%s\t", sv[i].name);
        printf("%s\t", sv[i].id);
        printf("%d\t", sv[i].age);
        printf("\n");
    }
}

void loadFileSv(){
    FILE *file = fopen("student.bin", "rb");
    if (file == NULL) {
        printf("Loi khong the mo file\n");
        return;
    }
    numberStudent = fread(&sv, sizeof(struct SinhVien), 100, file);
    fclose(file);
}

void addSV() {
    if (numberStudent >= 100) {
        printf("Danh sach sinh vien da day, khong the them moi!\n");
        return;
    }
    struct SinhVien sv1;
    printf("Nhap ID: ");
    fgets(sv1.id, sizeof(sv1.id), stdin);
    sv1.id[strcspn(sv1.id, "\n")] = 0; 
    printf("Nhap ten: ");
    fgets(sv1.name, sizeof(sv1.name), stdin);
    sv1.name[strcspn(sv1.name, "\n")] = 0; 
    printf("Nhap tuoi: ");
    scanf("%d", &sv1.age);
    getchar(); 
    sv[numberStudent] = sv1;
    numberStudent++;
    printf("Sinh vien da duoc them.\n");
}

void saveFile() {
    FILE *file;
    file = fopen("student.bin", "wb");
    if (file == NULL) {
        printf("Loi khi luu file\n");
        return;
    }
    fwrite(sv, sizeof(struct SinhVien), numberStudent, file);  
    fclose(file);
}

void editSV(struct SinhVien *sv1, int numberStudent) {
    char id[20];
    printf("Nhap ID sinh vien can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0; 
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) { 
            printf("Sinh vien tim thay: %s, %s, %d\n", sv[i].id, sv[i].name, sv[i].age);
            printf("Cap nhat ten moi: ");
            fgets(sv[i].name, sizeof(sv[i].name), stdin);
            sv[i].name[strcspn(sv[i].name, "\n")] = 0; 
            printf("Cap nhat tuoi moi: ");
            scanf("%d", &sv[i].age);
            getchar(); 
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }
    printf("Sinh vien voi ID %s khong ton tai.\n", id);
}

void deleteSV() {
    char id[20];
    printf("Nhap ID sinh vien can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            for (int j = i; j < numberStudent - 1; j++) {
                sv[j] = sv[j + 1]; 
            }
            numberStudent--;  
            printf("Sinh vien da duoc xoa.\n");
            return;
        }
    }
    printf("Sinh vien voi ID %s khong ton tai.\n", id);
}

void seachSV(struct SinhVien *sv1, int numberStudent) {
    char id[20];
    int found = 0;
    printf("Moi ban nhap Ma sinh vien de tien hanh tim kiem: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            printf("Sinh vien tim thay la: \n");
            printf("ID: %s\tTen: %s\tTuoi: %d\n", sv[i].id, sv[i].name, sv[i].age);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay thong tin sinh vien %s\n", id);
    }
}

void sortSV(struct SinhVien *sv, int numberStudent) {
    for (int i = 0; i < numberStudent - 1; i++) {
        for (int j = i + 1; j < numberStudent; j++) {
            if (strcmp(sv[i].id, sv[j].id) > 0) {
                struct SinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep theo ID.\n");
}

