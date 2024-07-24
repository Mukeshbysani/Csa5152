#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MX 5

void playfair(char ch1, char ch2, char key[MX][MX], FILE *out) {
    int i, j, w = -1, x = -1, y = -1, z = -1;

    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (ch1 == key[i][j]) {
                w = i;
                x = j;
            }
            if (ch2 == key[i][j]) {
                y = i;
                z = j;
            }
        }
    }

  
    if (w == -1 || x == -1 || y == -1 || z == -1) {
        printf("Characters not found in key matrix.\n");
        return;
    }

   
    if (w == y) { 
        x = (x + 1) % MX;
        z = (z + 1) % MX;
    } else if (x == z) {  
        w = (w + 1) % MX;
        y = (y + 1) % MX;
    } else { 
        int temp = x;
        x = z;
        z = temp;
    }

    printf("%c%c", key[w][x], key[y][z]);
    fprintf(out, "%c%c", key[w][x], key[y][z]);
}

int main() {
    int i, j, k = 0, m = 0, n;
    char key[MX][MX], keyminus[25], keystr[10], str[25] = {0};
    char alpa[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                     'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    FILE *out;

    if ((out = fopen("cipher.txt", "w")) == NULL) {
        printf("File Corrupted.");
        return 1;
    }

    printf("\nEnter key: ");
    gets(keystr);
    printf("\nEnter the plain text: ");
    gets(str);

    n = strlen(keystr);

   
    for (i = 0; i < n; i++) {
        if (keystr[i] == 'j') keystr[i] = 'i';
        else if (keystr[i] == 'J') keystr[i] = 'I';
        keystr[i] = toupper(keystr[i]);
    }

  
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'j') str[i] = 'i';
        else if (str[i] == 'J') str[i] = 'I';
        str[i] = toupper(str[i]);
    }

   
    j = 0;
    for (i = 0; i < 26; i++) {
        for (k = 0; k < n; k++) {
            if (keystr[k] == alpa[i])
                break;
            if (alpa[i] == 'J')
                break;
        }
        if (k == n) {
            keyminus[j] = alpa[i];
            j++;
        }
    }

  
    k = 0;
    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (k < n) {
                key[i][j] = keystr[k];
                k++;
            } else {
                key[i][j] = keyminus[m];
                m++;
            }
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }

    printf("\n\nEntered text: %s\nCipher Text: ", str);
    for (i = 0; i < strlen(str); i++) {
        if (str[i + 1] == '\0') {
            playfair(str[i], 'X', key, out);
        } else {
            if (str[i + 1] == 'J') str[i + 1] = 'I';
            if (str[i] == str[i + 1]) {
                playfair(str[i], 'X', key, out);
            } else {
                playfair(str[i], str[i + 1], key, out);
                i++;
            }
        }
    }

    fclose(out);
    return 0;
}
