#include <stdio.h>
#include <string.h>

char data[100], divisor[30];
char dividend[150], r[150];
char transmitted[150], received[150];

void xorOperation(int pos, int divLen)
{
    int i;

    for(i = 0; i < divLen; i++)
    {
        if(dividend[pos + i] == divisor[i])
            dividend[pos + i] = '0';
        else
            dividend[pos + i] = '1';
    }
}

int main()
{
    int dataLen, divLen;
    int i;
    char choice;

    printf("Enter Data Bits : ");
    scanf("%s", data);

    printf("Enter Generator Polynomial : ");
    scanf("%s", divisor);

    dataLen = strlen(data);
    divLen = strlen(divisor);
    for(i = 0; i < dataLen; i++)
    {
        if(data[i] != '0' && data[i] != '1')
        {
            printf("\nInvalid Data.\n");
            return 0;
        }
    }

    for(i = 0; i < divLen; i++)
    {
        if(divisor[i] != '0' && divisor[i] != '1')
        {
            printf("\nInvalid Generator.\n");
            return 0;
        }
    }

    strcpy(dividend, data);

    for(i = 0; i < divLen - 1; i++)
        dividend[dataLen + i] = '0';

    dividend[dataLen + divLen - 1] = '\0';

    strcpy(r, dividend);

    for(i = 0; i <= dataLen - 1; i++)
    {
        if(r[i] == '1')
        {
            int j;

            for(j = 0; j < divLen; j++)
            {
                if(r[i + j] == divisor[j])
                    r[i + j] = '0';
                else
                    r[i + j] = '1';
            }
        }
    }

    strcpy(transmitted, data);

    printf("\nCRC Bits : ");

    for(i = 0; i < divLen - 1; i++)
    {
        transmitted[dataLen + i] = r[dataLen + i];
        printf("%c", r[dataLen + i]);
    }

    transmitted[dataLen + divLen - 1] = '\0';

    printf("\nTransmitted Frame : %s\n", transmitted);

    strcpy(received, transmitted);

    printf("\nSimulate Error? (Y/N): ");
    scanf(" %c", &choice);

    if(choice == 'Y' || choice == 'y')
    {
        int pos;

        printf("Enter Bit Position to Flip (1-%lu): ", strlen(received));
        scanf("%d", &pos);

        if(pos >= 1 && pos <= strlen(received))
        {
            if(received[pos - 1] == '0')
                received[pos - 1] = '1';
            else
                received[pos - 1] = '0';
        }
        else
        {
            printf("Invalid Position\n");
            return 0;
        }
    }

    printf("\nReceived Frame : %s\n", received);

    strcpy(r, received);

    for(i = 0; i <= strlen(received) - divLen; i++)
    {
        if(r[i] == '1')
        {
            int j;

            for(j = 0; j < divLen; j++)
            {
                if(r[i + j] == divisor[j])
                    r[i + j] = '0';
                else
                    r[i + j] = '1';
            }
        }
    }

    int error = 0;

    for(i = strlen(received) - divLen + 1; i < strlen(received); i++)
    {
        if(r[i] != '0')
        {
            error = 1;
            break;
        }
    }

    if(error)
    {
        printf("\nCRC Remainder : ");

        for(i = strlen(received) - divLen + 1; i < strlen(received); i++)
            printf("%c", r[i]);

        printf("\n\nResult : ERROR DETECTED");
        printf("\nMessage Discarded\n");
    }
    else
    {
        printf("\nCRC Remainder : ");

        for(i = strlen(received) - divLen + 1; i < strlen(received); i++)
            printf("%c", r[i]);

        printf("\n\nResult : NO ERROR");

        printf("\nExtracted Data : ");

        for(i = 0; i < dataLen; i++)
            printf("%c", received[i]);

        printf("\n");
    }

    return 0;
}
