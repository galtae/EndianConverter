#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX_LENGTH 32

//#define __TEST

void delete_space(char s[]) 
{		
    char tmp[MAX_LENGTH];
    int i, k = 0;
    for (i = 0; i < (int)strlen(s); i++) 
    {
        if (s[i] != ' ')
            tmp[k++] = s[i];
    }
    tmp[k] = 0;    
    strcpy_s(s, MAX_LENGTH, tmp);
}

unsigned int invertEndian(unsigned int inVal) {
    int result;
    unsigned char bytes[4];
    bytes[0] = (unsigned char)((inVal >> 24) & 0xff);
    bytes[1] = (unsigned char)((inVal >> 16) & 0xff);
    bytes[2] = (unsigned char)((inVal >> 8) & 0xff);
    bytes[3] = (unsigned char)((inVal >> 0) & 0xff);

    result = ((int)bytes[0] << 0) |
        ((int)bytes[1] << 8) |
        ((int)bytes[2] << 16) |
        ((int)bytes[3] << 24);

    return result;
}

unsigned long long invertEndian8(unsigned long long inVal) {
    unsigned long long result;
    unsigned char bytes[8];
    bytes[0] = (unsigned char)((inVal >> 56) & 0xff);
    bytes[1] = (unsigned char)((inVal >> 48) & 0xff);
    bytes[2] = (unsigned char)((inVal >> 40) & 0xff);
    bytes[3] = (unsigned char)((inVal >> 32) & 0xff);
    bytes[4] = (unsigned char)((inVal >> 24) & 0xff);
    bytes[5] = (unsigned char)((inVal >> 16) & 0xff);
    bytes[6] = (unsigned char)((inVal >> 8) & 0xff);
    bytes[7] = (unsigned char)((inVal >> 0) & 0xff);

    result = ((unsigned long long)bytes[0] << 0) |
        ((unsigned long long)bytes[1] << 8) |
        ((unsigned long long)bytes[2] << 16) |
        ((unsigned long long)bytes[3] << 24) |
        ((unsigned long long)bytes[4] << 32) |
        ((unsigned long long)bytes[5] << 40) |
        ((unsigned long long)bytes[6] << 48) |
        ((unsigned long long)bytes[7] << 56);

    return result;
}

int ConvertEndian(char* input_str)
{    
    int Ret = 0;
    delete_space(input_str);
    //printf("%s\n", input_str);

    //unsigned long number = strtol(input_str, NULL, 16);    
    unsigned long number = strtoul(input_str, NULL, 16);
    Ret = invertEndian(number);
    printf("%X", Ret);
    return Ret;
}

void convertUnsignedLongLongToHexString(unsigned long long number, char* str) {
    int i = 0;
    unsigned long long temp = number;

    // Convert the number to a hexadecimal string in reverse order
    do {
        int digit = temp & 0xF;
        if (digit < 10)
            str[i] = '0' + digit;
        else
            str[i] = 'A' + (digit - 10);
        temp >>= 4;  // Shift right by 4 bits
        i++;
    } while (temp > 0);

    str[i] = '\0';  // Set null character at the end of the string

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

unsigned long long ConvertEndian8(char* input_str)
{    
    unsigned long long Ret = 0;
    delete_space(input_str);
    //printf("%s\n", input_str);

    //unsigned long number = strtol(input_str, NULL, 16);    
    unsigned long long number = strtoull(input_str, NULL, 16);
    Ret = invertEndian8(number);
    printf("%X", Ret);
    return Ret;
}

unsigned long long CopyClipBoard(unsigned long long Number)
{
    int Ret = 0;
    unsigned char dest_str[MAX_LENGTH] = "";
    char dest_str1[MAX_LENGTH] = "";
    //_itoa_s(Number, dest_str, 16);

    convertUnsignedLongLongToHexString(Number, dest_str1);

    ::OpenClipboard(NULL);
    EmptyClipboard();

    HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, 256);
    char* mem = (char*)GlobalLock(hglbCopy);

    strcpy_s(mem, MAX_LENGTH, dest_str1);
    GlobalUnlock(hglbCopy);
    ::SetClipboardData(CF_TEXT, mem);
    CloseClipboard();
    return Ret;
}

int main()
{

    char input_str[MAX_LENGTH];

#ifdef __TEST
    strcpy_s(input_str, 17, "1234567890123456");    
#endif

#ifndef __TEST
    scanf_s("%[^\n]s", &input_str, sizeof(input_str));
    //printf("%s\n", input_str);
#endif

    int input_str_lenth =  strlen(input_str);
    //printf("\n%d", a);

    unsigned long long Number;

    if (input_str_lenth <= 8)
        Number = ConvertEndian(input_str);

    else
        Number = ConvertEndian8(input_str);
    
    CopyClipBoard(Number);   

 	return 0;
}