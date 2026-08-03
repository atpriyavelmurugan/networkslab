#include <stdio.h>
#include <string.h>

char text[200];
char blocks[50][9];
char checksum[9];

void binaryAddition(char a[], char b[])
{
    int carry = 0;
    int i;

    for(i = 7; i >= 0; i--)
    {
        int sum = (a[i]-'0') + (b[i]-'0') + carry;

        a[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
    while(carry)
    {
        int next_carry = 0;
        for(i = 7; i >= 0; i--)
        {
            int sum = (a[i]-'0') + carry + next_carry;
            a[i] = (sum % 2) + '0';
            next_carry = sum / 2;
        }
        carry = next_carry;
    }
}

int main()
{
    int len, i, j, numBlocks = 0;
    char sum[9] = "00000000";
    char receivedSum[9];
    char choice;

    printf("Enter Text Message : ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    len = strlen(text);
    if(len == 0)
    {
        printf("Invalid Input. String cannot be empty.\n");
        return 0;
    }

    for(i = 0; i < len; i++)
    {
        unsigned char ch = text[i];

        for(j = 0; j < 8; j++)
        {
            int bit = (ch >> (7 - j)) & 1;
            blocks[numBlocks][j] = bit + '0';
        }
        blocks[numBlocks][8] = '\0';
        numBlocks++;
    }

    printf("\nData Blocks\n");

    for(i = 0; i < numBlocks; i++)
    {
        printf("Block %d: %s\n", i + 1, blocks[i]);
        binaryAddition(sum, blocks[i]);
    }

    for(i = 0; i < 8; i++)
    {
        if(sum[i] == '0')
            checksum[i] = '1';
        else
            checksum[i] = '0';
    }
    checksum[8] = '\0';

    printf("\nChecksum : %s\n", checksum);

    printf("\nTransmitted Frame\n");
    for(i = 0; i < numBlocks; i++)
        printf("%s ", blocks[i]);

    printf("%s\n", checksum);

    strcpy(receivedSum, "00000000");
    for(i = 0; i < numBlocks; i++)
        binaryAddition(receivedSum, blocks[i]);

    binaryAddition(receivedSum, checksum);

    printf("\nSimulate Error? (Y/N): ");
    scanf(" %c", &choice);

    if(choice == 'Y' || choice == 'y')
    {
        int blockNo, bitPos;

        printf("Enter Block Number (1-%d): ", numBlocks);
        scanf("%d", &blockNo);

        printf("Enter Bit Position (1-8): ");
        scanf("%d", &bitPos);

        if(blockNo >= 1 && blockNo <= numBlocks && bitPos >= 1 && bitPos <= 8)
        {
            if(blocks[blockNo-1][bitPos-1] == '0')
                blocks[blockNo-1][bitPos-1] = '1';
            else
                blocks[blockNo-1][bitPos-1] = '0';

            printf("Error Simulated Successfully.\n");

            strcpy(receivedSum, "00000000");
            for(i = 0; i < numBlocks; i++)
                binaryAddition(receivedSum, blocks[i]);

            binaryAddition(receivedSum, checksum);
        }
        else
        {
            printf("Invalid Block Number or Bit Position.\n");
        }
    }

    printf("\nReceived Blocks\n");
    for(i = 0; i < numBlocks; i++)
        printf("Block %d : %s\n", i + 1, blocks[i]);

    printf("Checksum : %s\n", checksum);

    int error = 0;
    for(i = 0; i < 8; i++)
    {
        if(receivedSum[i] != '1')
        {
            error = 1;
            break;
        }
    }


    if(error)
    {
        printf("\nResult : ERROR DETECTED\n");
        printf("Message Discarded\n");
    }
    else
    {
        printf("\nResult : NO ERROR\n");
        printf("Original Message Received Successfully\n");
        printf("Extracted Message : ");

        for(i = 0; i < numBlocks; i++)
        {
            int asciiValue = 0;
            for(j = 0; j < 8; j++)
            {
                asciiValue = (asciiValue << 1) + (blocks[i][j] - '0');
            }
            printf("%c", (char)asciiValue);
        }
        printf("\n");
    }

    return 0;
}
