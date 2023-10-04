#include "utils.h"

int str_length(char str[])
{
    int count;
    for (count = 0; str[count] != '\0'; ++count)
        ;
    return count;
}

FILE *open_file_ro(char *device_name)
{
    FILE *device = NULL;
    char device_path[PATH_MAX];
    // Construct full path and open the device file
    if (getcwd(device_path, sizeof(device_path)) != NULL) // Current Working Directory
    {
        for (int i = 0; i < PATH_MAX - _CONF_MAX_LEN_DEVICE_NAME; i++)
        {
            if (device_path[i] == 0)
            {
                device_path[i] = '/';
                i++;
                int j;
                for (j = 0; j < str_length(device_name); j++)
                {
                    device_path[i + j] = device_name[j];
                }
                device_path[i + j] = '\0';
                break;
            }
        }
        device = fopen(device_path, "r");
        if (device == NULL)
        {
            status = _ERR_OPEN_DEVICE_NOK;
            err_handler(device_name);
        }
    }
    else // If getcwd fails
    {
        status = _ERR_OPEN_DEVICE_NOK;
        err_handler(device_name);
    }
#ifdef DBG
    printf("Disk : %s ", device_name);
#endif

    return device;
}

void print_start(void)
{
    printf("----------| Start i386 Emulator |----------\n");
    // TODO: print meta data about software (ex. version)
}

void print_end(void)
{
    printf("----------| Exit i386 Emulator |----------\n");
}
