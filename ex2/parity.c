#include <stdio.h>
#include <string.h>

int main()
{
    char text[100];
    char frames[100][9];
    int len, numFrames = 0;
    int i, j;
    int ones, parity;
    char choice;
    printf("\nEnter Text Message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    len = strlen(text);
    if(len == 0)
    {
        printf("\nInvalid Input. String cannot be empty.\n");
        return 0;
    }

    for(i = 0; i < len; i++)
    {
        unsigned char ch = text[i];
        ones = 0;


        for(j = 0; j < 7; j++)
        {
            int bit = (ch >> (6 - j)) & 1;
            frames[numFrames][j] = bit + '0';

            if(bit == 1)
                ones++;
        }
        if(ones % 2 == 0)
            parity = 0;
        else
            parity = 1;

        frames[numFrames][7] = parity + '0';
        frames[numFrames][8] = '\0';

        numFrames++;
    }

    printf("\nGenerated Frame (7 Data Bits + 1 Parity Bit)\n");
    for(i = 0; i < numFrames; i++)
    {
        printf("Frame %d : %s\n", i + 1, frames[i]);
    }

    printf("\nDo you want to simulate errors? (Y/N): ");
    scanf(" %c", &choice);

    if(choice == 'Y' || choice == 'y')
    {
        int totalErrors;
        printf("Enter the number of bit errors to inject: ");
        scanf("%d", &totalErrors);

        for(int e = 0; e < totalErrors; e++)
        {
            int frameNo, bitPos;

            printf("\n[Error %d] Enter Frame Number (1-%d): ", e + 1, numFrames);
            scanf("%d", &frameNo);

            printf("[Error %d] Enter Bit Position (1-8): ", e + 1);
            scanf("%d", &bitPos);

            if(frameNo >= 1 && frameNo <= numFrames && bitPos >= 1 && bitPos <= 8)
            {
                if(frames[frameNo-1][bitPos-1] == '0')
                    frames[frameNo-1][bitPos-1] = '1';
                else
                    frames[frameNo-1][bitPos-1] = '0';

                printf("Error Simulated Successfully.\n");
            }
            else
            {
                printf("Invalid Frame Number or Bit Position. Error ignored.\n");
            }
        }
    }

    printf("\nReceived Frames\n");
    for(i = 0; i < numFrames; i++)
    {
        printf("Frame %d : %s\n", i + 1, frames[i]);
    }

    printf("\nReceiver Checking...\n");
    int errorFound = 0;

    for(i = 0; i < numFrames; i++)
    {
        ones = 0;
        for(j = 0; j < 8; j++)
        {
            if(frames[i][j] == '1')
                ones++;
        }

        if(ones % 2 == 0)
        {
            printf("Frame %d : No Error Detected\n", i + 1);
        }
        else
        {
            printf("Frame %d : Error Detected\n", i + 1);
            errorFound = 1;
        }
    }

    if(errorFound)
    {
        printf("\nMESSAGE DISCARDED\n");
    }
    else
    {
        printf("\nNO ERROR DETECTED\n");
        printf("Original Message Received Successfully\n");

        printf("\nExtracted Message : ");
        for(i = 0; i < numFrames; i++)
        {
            int asciiValue = 0;
            for(j = 0; j < 7; j++)
            {
                asciiValue = (asciiValue << 1) + (frames[i][j] - '0');
            }
            printf("%c", (char)asciiValue);
        }
        printf("\n");
    }

    return 0;
}
