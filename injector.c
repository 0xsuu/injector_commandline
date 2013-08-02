#include <stdio.h>

int main(int argc,char *argv[])
{
    FILE *fp,*fpNew;
            
    fp = fopen("~/Desktop/target","rb");
    fpNew = fopen("~/Desktop/new","wb");

    if (argc < 3)
    {
        printf("Useage: injector [offset(hex)] [insert_byte(hex)]\n");
        return;
    }
    if (fpNew == 0)
    {
        printf("# warning: failed to create new file\n");
        return 1;
    }
    else
    {
        printf("[+] new file created\n");
    }
    
    if (fp == 0)
    {
        printf("# warning: failed to read raw file\n");
        return 1;
    }
    else
    {
        printf("[+] reading raw file\n");
    }
    
    fseek(fp,0,SEEK_SET);
            
    char output;
    output = fgetc(fp);
            
    int count = 0;
    int offset = 0;
    offset = strtoul(argv[1], 0, 16);
    printf("[+] dumping");
    
    while(!feof(fp))
    {
        if (count % 10000 == 0)
        {
            printf(".");
        }
        
        if (count == offset)
        {
            printf("\n[+] injecting offset:0x%X\n",offset);
            fputc(strtoul(argv[2], 0, 16),fpNew);
            printf("[+] %02X changed to %02lX\n",output,strtoul(argv[2], 0, 16));
            printf("[+] dumping");
        }
        else
        {
            fputc(output,fpNew);
        }
        output=fgetc(fp);
        count++;
    }
    
    printf("\n");
    
    fclose(fp);
    fclose(fpNew);
    return 0;
}
