#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define versionCode 1
#define size versionCode * 4 + 17

bool qrCode[size][size];
int queueCode[size][size];
int toPow[] = {-1, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75, 4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166, 6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61, 202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175};
int toDec[] = {-1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161, 95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226, 217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206, 129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204, 133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84, 168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115, 230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65, 130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166, 81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9, 18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22, 44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142, 1};

bool isOddColumn(int x)
{
    return (x + (x > 6 ? 0 : 1)) / 2 % 2 == 0;
}

void initQueueCode()
{

    int x = size - 1;
    int y = size - 1;

    for (int i = 1; i <= 26 * 8; i++)
    {
        if (y == 6)
        {
            if (isOddColumn(x))
            {
                y--;
            }
            else
            {
                y++;
            }
        }
        if (x == 6)
        {
            x -= 1;
        }
        if (0 <= x && x < size && 0 <= y && y < size)
        {
            queueCode[y][x] = i;
        }

        if (x % 2 == (x > 6 ? 0 : 1))
        {
            x--;
        }
        else
        {

            x++;

            if ((x > 8 && (!isOddColumn(x) && (y == size - 1) || isOddColumn(x) && ((x > 12 && y == 9) || (x > 10 && x <= 14 && (y == 0))))) || (x <= 8 && (isOddColumn(x) && (y == 9) || !isOddColumn(x) && y == 12)))
            {
                if (x == 10)
                {
                    x = 8;
                    y = 12;
                    continue;
                }
                x -= 2;
            }
            else
            {
                if (isOddColumn(x))
                {
                    y--;
                }
                else
                {
                    y++;
                }
            }
        }
    }
}

void drawCorner(int x, int y)
{
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 7; i++)
        {
            qrCode[y][x + i] = true;
            qrCode[y + i][x] = true;
            qrCode[y + 6][x + i] = true;
            qrCode[y + i][x + 6] = true;
        }
        for (int i = x + 2; i < x + 5; i++)
        {
            for (int j = y + 2; j < y + 5; j++)
            {
                qrCode[j][i] = true;
            }
        }
    }
}

void drawTimingPattern()
{
    for (int i = 0; i < 3; i++)
    {
        qrCode[8 + 2 * i][6] = true;
        qrCode[6][8 + 2 * i] = true;
    }
    qrCode[size - 8][8] = true;
}

void drawFormatString(int errorCorrectionLevel)
{
    int typeInformation[] = {
        0,
        29427, // code = L-1
        20773, // code = M-1
        12392, // code = Q-1
        5054,  // code = H-1
    };

    // int typeInformation = 20773;

    for (int i = 0; i < 15; i++)
    {

        int state = !!(typeInformation[errorCorrectionLevel] & 1 << (14 - i));
        // int state = !!(typeInformation & 1 << (14 - i));

        qrCode[i <= 7 ? 8 : (14 - i == 6 ? 7 : 14 - i)][i <= 7 ? (i >= 6 ? i + 1 : i) : 8] = state;
        qrCode[i < 7 ? size - 1 - i : 8][i < 7 ? 8 : i + 6] = state;
    }
}

void initializeQrCode(int errorCorrectionLevel)
{

    initQueueCode();

    drawCorner(0, 0);
    drawCorner(0, size - 7);
    drawCorner(size - 7, 0);

    drawTimingPattern();
    drawFormatString(errorCorrectionLevel);
}

void getPos(int k, int *pos)
{

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (queueCode[y][x] == k)
            {
                pos[0] = x, pos[1] = y;
                return;
            }
        }
    }

    return;
}

void writeCaracter(int c, int k, bool applyMask)
{
    // printf("%c -> %d:\n", c, c);
    for (int i = 0; i < 8; i++)
    {
        int pos[2] = {0};
        getPos(k, pos);

        bool state = !!(c & 1 << (7 - i));

        // printf("\t%d %d %d\n", pos[0], pos[1], state);

        // int mask = pos[0] % 3 == 0;
        int mask = (pos[1] + (pos[1] < 6 ? 0 : 1)) % 2 == 1;

        if (applyMask)
        {
            qrCode[pos[1]][pos[0]] = mask ? !state : state;
        }
        else
        {
            qrCode[pos[1]][pos[0]] = state;
        }

        // qrCode[pos[1]][pos[0]] = mask ? true : false;
        k++;
    }
}

void setQrCodeData(char data[], int errorCorrectionLevel)
{
    int len = strlen(data);
    int k = 1;
    bool applyMask = true;

    short dataEncoding = 4;
    short dataLength = len;

    int messLens[] = {
        0,
        19,
        16,
        13,
        9,
    };


    int messLen = messLens[errorCorrectionLevel]; // 16
    int corrLen = 26 - messLen;

    if (len > messLen-1)
    {
        printf("Data is too long!");
        return;
    }

    printf("messLen = %d\n", messLen);

    short codeWords[26] = {0};

    // Create codewords
    codeWords[0] = (dataEncoding << 4) | (dataLength >> 4);
    codeWords[1] = ((dataLength & 15) << 4) | (data[0] >> 4);

    for (int i = 0; i < messLen - 2; i++)
    {
        if (i < len)
        {
            codeWords[i + 2] = ((data[i] & 15) << 4) | (i + 1 == len ? 0 : data[i + 1] >> 4);
        }
        else
        {
            codeWords[i + 2] = (i % 2 ? 17 : 236);
        }
    }

    printf("%s\n", data);

    // Calculate error correction codewords

    short genePolys[][26] = {
        [7] = {0, 87, 229, 146, 149, 238, 102, 21},
        [10] = {0, 251, 67, 46, 61, 118, 70, 64, 94, 32, 45},
        [13] = {0, 74, 152, 176, 100, 86, 100, 106, 104, 130, 218, 206, 140, 78},
        [17] = {0, 43, 139, 206, 78, 43, 239, 123, 206, 214, 147, 24, 99, 150, 39, 243, 163, 136},
    };
    short messPoly[26] = {0};
    for (int i = 0; i < messLen; i++)
    {
        messPoly[i] = codeWords[i];
    }

    for (int i = 0; i < messLen; i++)
    {
        short tempGenePoly[26] = {0};
        for (int j = 0; j < corrLen + 1; j++)
        {
            // int pow = (genePoly[j] + toPow[messPoly[i]]);
            int pow = (genePolys[corrLen][j] + toPow[messPoly[i]]);
            tempGenePoly[j + i] = toDec[pow > 255 ? pow % 255 : pow];
            // printf("GenePoly[%d] -> %d\n", 25 - (j + i), tempGenePoly[j + i]);
        }
        for (int j = i; j < 26; j++)
        {
            messPoly[j] = (tempGenePoly[j] ^ messPoly[j]);
        }
    }

    // for (int j = 0; j < 26; j++)
    // {
    //     printf("messPoly[%d] -> %d\n", 25 - j, messPoly[j]);
    // }

    // Print codeWords
    for (int l = 0; l < 26; l++)
    {
        // if (codeWords[l] != 0)
        if (l < messLen)
        {
            writeCaracter(codeWords[l], k, applyMask);
            // printf("%d -> %c\n", l, codeWords[l]);
        }
        else
        {
            writeCaracter(messPoly[l], k, applyMask);
            // printf("%d -> %c\n", l, messPoly[l]);
        }
        k += 8;
    }
}

void printQrCode()
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf(queueCode[i][j] > 99 ? "%d " : (queueCode[i][j] > 9 ? "%d  " : "%d   "), queueCode[i][j]);
            // printf("%d", qrCode[j][i]);
        }
        printf("\n");
    }
}

void writeQrCode(const char *filename)
{

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Erreur lors de l'ouverture du fichier.");
        return;
    }

    // Write PGM header
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", size + 2, size + 2);
    fprintf(file, "%d\n", 1);

    // Write pixel values
    for (int i = 0; i < size + 2; i++)
    {

        fprintf(file, "1 ");
    }
    fprintf(file, "\n");

    for (int i = 0; i < size; ++i)
    {

        fprintf(file, "1 \n");
        for (int j = 0; j < size; ++j)
        {
            fprintf(file, "%d ", 1 - qrCode[i][j]);
            printf("%d", qrCode[i][j]);
        }
        fprintf(file, "1\n");
        printf("\n");
    }
    for (int i = 0; i < size + 2; i++)
    {

        fprintf(file, "1 ");
    }

    fclose(file);
}

int main()
{

    int errorCorrectionLevel = 2; // or 3
    char data[] = "Hello World!";

    initializeQrCode(errorCorrectionLevel);
    setQrCodeData(data, errorCorrectionLevel);
    // printQrCode();

    writeQrCode("image.pgm");

    return 0;
}