#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parse a specific column (0-indexed) from a CSV row, handling quotes
void get_column(const char *line, int target_col, char *output, size_t max_len) {
    int current_col = 0;
    int in_quotes = 0;
    int idx = 0;

    for (size_t i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
        char c = line[i];

        if (c == '"') {
            in_quotes = !in_quotes; // Toggle quotes state
        } else if (c == ',' && !in_quotes) {
            if (current_col == target_col) {
                break; // Target column extraction finished
            }
            current_col++;
            idx = 0; // Reset buffer for next column
        } else if (current_col == target_col) {
            if (idx < max_len - 1) {
                output[idx++] = c;
            }
        }
    }
    output[idx] = '\0';
}

int main() {
    FILE *fp = fopen("newdata.csv", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // arr[0]: Total counts, arr[1]: Survived counts
    // 18 slots total: 9 for Male (3 classes * 3 categories), 9 for Female
    int arr[2][18] = {0};
    char line[1000];

    // Skip CSV Header
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        char str_alive[10], str_class[10], str_sex[10], str_category[10];

        // Extract required columns safely
        get_column(line, 1, str_alive, sizeof(str_alive));
        get_column(line, 2, str_class, sizeof(str_class));
        get_column(line, 4, str_sex, sizeof(str_sex));
        get_column(line, 12, str_category, sizeof(str_category));

        // Convert parsed strings to integers
        int alive = atoi(str_alive);
        int pclass = atoi(str_class);
        int category = atoi(str_category);

        // Validate range bounds (class: 1-3, category: 1-3)
        if (pclass < 1 || pclass > 3 || category < 1 || category > 3) {
            continue;
        }

        int gender_offset;

        if (strcmp(str_sex, "female") == 0) {
            gender_offset = 9;
        } else if (strcmp(str_sex, "male") == 0) {
            gender_offset = 0;
        } else {
            continue; 
        }

        int index = gender_offset + (pclass - 1) * 3 + (category - 1);

        arr[0][index]++;

        if (alive == 1) {
            arr[1][index]++;
        }
    }
    }

    fclose(fp);

    // Print array output
    for (int k = 0; k < 2; k++) {
        for (int n = 0; n < 18; n++) {
            printf("%d ", arr[k][n]);
        }
        printf("\n");
    }

    return 0;
}
