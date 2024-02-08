#include "door.h"

#define MAX_LENGTH 100

struct my_struct read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct my_struct);
    fseek(pfile, offset, SEEK_SET);
    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);
    rewind(pfile);
    return record;
}

void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
    int offset = index * sizeof(struct my_struct);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    struct my_struct record1 = read_record_from_file(pfile, record_index1);
    struct my_struct record2 = read_record_from_file(pfile, record_index2);

    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);  // Move the position pointer to the end of the file.
    size = ftell(
        pfile);  // Read the number of bytes from the beginning of the file to the current position pointer.
    rewind(pfile);  // For safety reasons, move the position pointer back to the beginning of the file.
    return size;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}

int compare(int a, int b) {
    int ans = 0;
    if (a < b) ans = -1;
    if (a > b) ans = 1;
    return ans;
}

int compare_doors(my_struct door_1, my_struct door_2) {
    int desigion = compare(door_1.year, door_2.year);
    if (desigion == 0) desigion = compare(door_1.month, door_2.month);
    if (desigion == 0) desigion = compare(door_1.day, door_2.day);
    if (desigion == 0) desigion = compare(door_1.h, door_2.h);
    if (desigion == 0) desigion = compare(door_1.m, door_2.m);
    if (desigion == 0) desigion = compare(door_1.s, door_2.s);
    return desigion;
}
void swap(my_struct *door_1, my_struct *door_2) {
    my_struct temp = *door_1;
    *door_1 = *door_2;
    *door_2 = temp;
}
void sort_doors(FILE *pfile, my_struct *doors, int n) {
    for (int i = 0; i < n - 1; i++) {
        my_struct max = doors[i];
        int imax = i;
        for (int j = i; j < n; j++) {
            if (compare_doors(max, doors[j]) > 0) {
                max = doors[j];
                imax = j;
                printf("swap\n");
            }
        }
        swap(&doors[i], &doors[imax]);
        swap_records_in_file(pfile, i, imax);
    }
}

void print_doors(my_struct *doors, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d %d %d %d %d\n", doors[i].year, doors[i].month, doors[i].day, doors[i].h,
               doors[i].m, doors[i].s, doors[i].status, doors[i].code);
    }
}

my_struct add_door() {
    my_struct door;
    scanf("%d %d %d %d %d %d %d %d", &door.year, &door.month, &door.day, &door.h, &door.m, &door.s,
          &door.status, &door.code);
    return door;
}

int main() {
    FILE *fs;
    int mode = 0;
    char *path = malloc(MAX_LENGTH * sizeof(char));
    while (mode != -1) {
        scanf("%99s", path);
        scanf("%d", &mode);
        if (mode == 0) {
            char fillPath[MAX_LENGTH + 3] = "../";
            strcat(fillPath, path);
            fs = fopen(fillPath, "r");
            if (fs != NULL) {
                int i = 0;
                int amount = get_records_count_in_file(fs);
                my_struct doors[amount];
                for (; i < amount; i++) {
                    doors[i] = read_record_from_file(fs, i);
                }
                if (i == 0) {
                    printf("n/a");
                } else
                    print_doors(doors, amount);
                fclose(fs);
            } else
                printf("n/a\n");
        }
        if (mode == 1) {
            char fillPath[MAX_LENGTH + 3] = "../";
            strcat(fillPath, path);
            fs = fopen(fillPath, "r");
            if (fs != NULL) {
                int i = 0;
                int amount = get_records_count_in_file(fs);
                my_struct doors[amount];
                for (; i < amount; i++) {
                    doors[i] = read_record_from_file(fs, i);
                }
                if (i == 0) {
                    printf("n/a");
                } else {
                    sort_doors(fs, doors, amount);
                    print_doors(doors, amount);
                }
                fclose(fs);
            } else
                printf("n/a\n");
        }
        if (mode == 2) {
            char fillPath[MAX_LENGTH + 3] = "../";
            strcat(fillPath, path);
            fs = fopen(fillPath, "r");
            if (fs != NULL) {
                int i = 0;
                int amount = get_records_count_in_file(fs);
                my_struct doors[amount + 1];
                for (; i < amount; i++) {
                    doors[i] = read_record_from_file(fs, i);
                }
                doors[amount] = add_door();
                write_record_in_file(fs, doors, amount);
                amount = get_records_count_in_file(fs);
                sort_doors(fs, doors, amount + 1);
                print_doors(doors, amount + 1);
                fclose(fs);
            } else
                printf("n/a\n");
        }
        if (mode < 0 || mode > 2) printf("n/a\n");
    }
}