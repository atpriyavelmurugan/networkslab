#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char str[100];
    int binary_stream[800];
    int stuffed_stream[1200];
    int transmitted_stream[1200];
    int received_stream[1200];
    int destuffed_stream[800];
    int flag[8] = {0,1,1,1,1,1,1,0};

    int bit_idx = 0;
    int stuffed_idx = 0;
    int destuffed_idx = 0;
    int count = 0;
    int stuffing_performed = 0;
    int len, i, b;
    char ch;
    int choice, pos1;
    int error_detected = 0;

    srand(time(NULL));

    printf("Enter word: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    len = strlen(str);

    for(i = 0; i < len; i++)
    {
        ch = str[i];
        for(b = 7; b >= 0; b--)
        {
            binary_stream[bit_idx++] = (ch >> b) & 1;
        }
    }
    for(i = 0; i < bit_idx; i++)
    {
        stuffed_stream[stuffed_idx++] = binary_stream[i];

        if(binary_stream[i] == 1)
            count++;
        else
            count = 0;

        if(count == 5)
        {
            stuffed_stream[stuffed_idx++] = 0;
            stuffing_performed = 1;
            count = 0;
        }
    }

    printf("\n=========== SENDER SIDE ===========\n");

    printf("\nOriginal Binary Data : ");
    for(i = 0; i < bit_idx; i++)
        printf("%d", binary_stream[i]);

    printf("\n\nStuffed Frame : ");

    for(i = 0; i < 8; i++)
        printf("%d", flag[i]);

    for(i = 0; i < stuffed_idx; i++)
        printf("%d", stuffed_stream[i]);

    for(i = 0; i < 8; i++)
        printf("%d", flag[i]);

    if(stuffing_performed)
        printf("\nStatus : Bit Stuffing Performed\n");
    else
        printf("\nStatus : No Bit Stuffing Required\n");


    for(i = 0; i < stuffed_idx; i++)
        transmitted_stream[i] = stuffed_stream[i];

    printf("\nDo you want to inject error\n");
    printf("0. No \n");
    printf("1. Yes\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 0:
            printf("No Error Introduced.\n");
            break;

        case 1:
            if (stuffed_idx > 0) {
                pos1 = (rand() % stuffed_idx) + 1;
                transmitted_stream[pos1-1] ^= 1;
                printf("Error injected at bit position: %d\n", pos1);
            }
            break;

        default:
            printf("Invalid Choice. Original Frame Sent.\n");
    }

    printf("\nTransmitted Frame : ");

    for(i = 0; i < 8; i++)
        printf("%d", flag[i]);

    for(i = 0; i < stuffed_idx; i++)
        printf("%d", transmitted_stream[i]);

    for(i = 0; i < 8; i++)
        printf("%d", flag[i]);

    for(i = 0; i < stuffed_idx; i++)
        received_stream[i] = transmitted_stream[i];

    printf("\n\n=========== RECEIVER SIDE ===========\n");

    printf("\nReceived Frame : ");

    for(i = 0; i < 8; i++)
        printf("%d", flag[i]);

    for(i = 0; i < stuffed_idx; i++)
        printf("%d", received_stream[i]);

    for(i = 0; i < 8; i++)
        printf("%d", flag[i]);

    count = 0;

    for(i = 0; i < stuffed_idx; i++)
    {
        destuffed_stream[destuffed_idx++] = received_stream[i];

        if(received_stream[i] == 1)
            count++;
        else
            count = 0;

        if(count == 5)
        {

            if(i + 1 < stuffed_idx && received_stream[i+1] == 1)
            {
                error_detected = 1;
            }
            i++;
            count = 0;
        }
    }

    if (destuffed_idx % 8 != 0)
    {
        error_detected = 1;
    }

    if (bit_idx != destuffed_idx)
    {
        error_detected = 1;
    }
    else
    {
        for(i = 0; i < bit_idx; i++)
        {
            if(binary_stream[i] != destuffed_stream[i])
            {
                error_detected = 1;
                break;
            }
        }
    }

   /* printf("\n\nDestuffed Data : ");
    for(i = 0; i < destuffed_idx; i++)
        printf("%d", destuffed_stream[i]);*/

    if (error_detected)
    {
        printf("\n\nError detected in transmission! Message discarded.\n");
    }
    else
    {
        printf("\n\nRecovered Data : ");
        for(i = 0; i < destuffed_idx; i += 8)
        {
            ch = 0;
            for(b = 0; b < 8; b++)
                ch = (ch << 1) | destuffed_stream[i+b];

            printf("%c", ch);
        }
        printf("\n");
    }

    return 0;
}
