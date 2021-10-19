#include <stdio.h>
#include <math.h>

#define BINARY_STRING_LENGTH 33
#define HEX_STRING_LENGTH 11

//Matthew Hillmer, HW1, mhillmer@wisc.edu, 2/20/2021

void GetBinaryFromUser(char *binary);
void GetHexFromUser(char *hex);
void GetDecimalFromUser(unsigned int *x);

void ConvertBinaryToDecimal(const char *binary, unsigned int *decimal);
void ConvertHexToDecimal(const char *hex, unsigned int *decimal);
void ConvertDecimalToBinary(const unsigned int decimal, char *binary); 
void ConvertDecimalToHex(const unsigned int decimal, char *hex); 

int main(){
    char binary[BINARY_STRING_LENGTH] = "11011";
    char hex[HEX_STRING_LENGTH] = "0x3F";
	unsigned int decimal = 31;
	
	enum MENU {binary_to_decimal=1, hex_to_decimal, decimal_to_binary, decimal_to_hex};
	while (1) {
		printf("Which conversion would you like to do?\n");
		printf("  %d. Binary to Decimal\n", binary_to_decimal);
		printf("  %d. Hex to Decimal\n", hex_to_decimal);
		printf("  %d. Decimal to Binary\n", decimal_to_binary);
		printf("  %d. Decimal to Hex\n", decimal_to_hex);
		printf("  q to Quit\n");
		int choice;
		if (!scanf("%d", &choice)) return 0;  // exits if user enters something other than a digit
		
		switch (choice) {
			case binary_to_decimal: {
				GetBinaryFromUser(binary); 
				ConvertBinaryToDecimal(binary, &decimal); 
				printf("Binary: %s\nDecimal: %u\n\n", binary, decimal);
			} break;
			case hex_to_decimal: {
				GetHexFromUser(hex); 
				ConvertHexToDecimal(hex, &decimal); 
				printf("Hex: %s\nDecimal: %u\n\n", hex, decimal);
			} break;
			case decimal_to_binary: {
				GetDecimalFromUser(&decimal); 
				ConvertDecimalToBinary(decimal, binary); 
				printf("Decimal: %u\nbinary: %s\n\n", decimal, binary);
			} break;
			case decimal_to_hex: {
				GetDecimalFromUser(&decimal); 
				ConvertDecimalToHex(decimal, hex); 
				printf("Decimal: %u\nHex: %s\n\n", decimal, hex);
			} break;
			default: return 0; // exit if user enters an invalid number
		}
	}
	return 0;
}
//gets the binary input 
void GetBinaryFromUser(char * binary) {
    printf("Please enter binary string here: ");
    scanf("%s", binary);
    return;
}
//gets the hex input
void GetHexFromUser(char * hex) {
    // this function has been written for you
    printf("Please enter hex string here (do include the 0x prefix): ");
    scanf("%s", hex);
       	for (char *p=hex;*p;p++) if(*p>='a') *p-='a'-'A';  // to upper case
    return;
}
//gets the decimal input
void GetDecimalFromUser(unsigned int *x) {
    printf("Please enter decimal number here: ");
    scanf("%u", x);
    return; 
}
//this converts a binary string to a decimal value
void ConvertBinaryToDecimal(const char * binary, unsigned int *decimal) {
    int value = 0;//create blank value
    while (*binary != '\0'){//while the string is not at the end
         value = 2* value + (*binary++ - '0');//increment by power of two and add to decinaml vvalue
    }
    *decimal = value;//set the pointer to the value
    return;
}
//converts hex string to decimal value
void ConvertHexToDecimal(const char *hex, unsigned int *decimal) {
    int length = 0, i = 0, value = 0, base = 1;
    while (hex[i]!='\0'){//gets the length of the hex value string
        i++;
        length++;
    }
    for (i=length--; i >= 0; i--){//creates decimal value from the hex
        if(hex[i]>='0' && hex[i]<='9'){//if the hex is a int
            value += (hex[i] - 48)*base;//get ascii number and add
            base*=16;//increment base value
        }
        else if(hex[i] >= 'A' && hex[i] <= 'F'){//if the hex digit is a char
            value += (hex[i] - 55)*base ;//get ascii value decrement
            base*=16;
        }
    }
    *decimal = value;//set pointer to value
    return;
}
//converts decimal to binary string
void ConvertDecimalToBinary(const unsigned int decimal, char *binary) {
    int i = 0, temp, j, end;
    temp = decimal;//creates a temp variable to manipulate 
    if (temp != 0){//if the value is not zero create a binary value
        while(temp!=0){//while the value is not zero
            binary[i] = (temp % 2) + 48;//get the mod and add the int to the string
            temp = (temp/2);//divide the decimal for next binary number
            i++;//increment
        }
        end = i;//set for end of loop later
        i--;//decremnt for the flip of loop
    }
    else{//if the vlaue is zero return zero
        binary[0] = 48;//ascii value of 0
        binary[1] = '\0';//end string character
        return;
    }
    for(j = 0; j<i; j++){//loop the reverses the string
        char save = binary[j];//saves the value of binary[j]
        binary[j]=binary[i];//swaps the values
        binary[i] = save;//swaps the values
        i--;
    }
    binary[end] = '\0';//use end to set the end of the string
    return;
}
//this creates a hex string from a decimal value
void ConvertDecimalToHex(const unsigned int decimal, char *hex) {
    int temp, i = 2 , number, j, end;
    hex[0]='0';//sets the 0 at the start
    hex[1]='X';//sets the X at the start
    number = decimal;//creates int to manipulate
    while(number!=0){//while the int isnt zero create hex string
        temp = number % 16;//mod to get the he value
        if (temp >= 10){// if it is larger than 10 create a char value
            temp = temp + 55;//increment for ascii value
        }
        else{//else set the int value
            temp = temp + 48;//increment for ascii value of ints
        }
        hex[i] = temp;//set the hex value in string
        number = number / 16;//decremnt the int value
        i++;
    }
    end = i;//create variable for end of string
    i--;
    for(j = 2; j<i; j++){//this reverses the hex string to be in the right order
        char save = hex[j];//creates temp value of hex[j]
        hex[j]=hex[i];//swaps the values
        hex[i]=save;//swaps the values
        i--;
    }
    hex[end] = '\0';//set the end of the hex string
    return;
}










