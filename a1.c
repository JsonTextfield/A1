#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BUF  255

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
unsigned char encode(unsigned char, unsigned char, int);

int main(){
  char str[8];
  int  choice;
  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("\n  what is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

    switch (choice) {
    int keyEntry; //the integer representation of the key
    unsigned char key; //the unsigned char representation of the key
    unsigned char input[MAX_BUF*4]; //to cover large input //will not work with large input otherwise
    int counter = 0; //the counter used to encode
    case 1:
      printf(" Enter a plaintext message\n");
      fgets(input, sizeof(input), stdin); //get input from user
      printf(" Enter a numeric key (0-255)\n");
      scanf("%d", &keyEntry); //get numeric key from user
      if((keyEntry < 0)||(keyEntry > 255)){ //errror checking
        printf(" You did not enter a valid key");
        break;
      }
      key = (unsigned char)keyEntry;
      
      for(int g = 0; g < strlen(input)-1;){
        printf("%d ", encode(input[g], key, counter));
        counter = counter + 1;
        g = g + 1;
      }
      break;

    case 2:
   
      printf(" Enter a ciphertext message.\nType -1 at the end when finished \n");
      fgets(input, sizeof(input), stdin); //get input from user
      

      if (strstr(input, "-1") == NULL) { //error checking
          printf(" You need to enter -1 at the end of your ciphertext.");
          break;
      }

      printf(" Enter a numeric key (0-255)\n");
      scanf("%d", &keyEntry); //get numeric key from user
      if((keyEntry < 0)||(keyEntry > 255)){ //error checking
        printf(" You did not enter a valid key");
        break;
      }
      key = (unsigned char)keyEntry;
      /*the following code is used to split the string into integers so that I can decode them
      reference: http://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c*/      
      int x = 0;
      char *stringSplitter; //token
      int cipherNum; //integer form of ciphertext
      
      stringSplitter = strtok (input," ");
      while ((stringSplitter != NULL)&&(strcmp(stringSplitter, "-1") != 0)){
        sscanf(stringSplitter,"%d",&cipherNum);
        if((cipherNum < -1)||(cipherNum > 255)){ //errror checking
        printf(" There exists at least one invalid number in your ciphertext");
        break;
        }
        if(cipherNum == -1){break;} //breaks out of loop if -1 is reached
        printf ("%c", encode(cipherNum, key, counter)); //prints out the decoded text
        stringSplitter = strtok (NULL, " ,");
        x = x + 1;
        counter = counter + 1;
      }
      break;

    default:
      printf(" You did not enter a valid choice.\n");
      break;
  }

  return 0;
}


unsigned char encode(unsigned char source, unsigned char key, int counter){
  unsigned char resultingByte = source; //begin with your resulting byte assigned the value of the source byte
//If the counter is multiple of 3...
if(counter%3 == 0){
    for(int x = 0; x < 7;){
    //examine every other bit of both the source and key bytes starting at bit 0
      //if the source bit xor the key bit is 0, set the same bit in the resulting byte to 0
      if(getBit(source, x) ^ getBit(key, x) == 0){
        resultingByte = clearBit(resultingByte, x);      
      }
      //if the source bit xor the key bit is 1, set the same bit in the resulting byte to 1
      if(getBit(source, x) ^ getBit(key, x) == 1){
        resultingByte = setBit(resultingByte, x);
      }
      x = x+2;
    }
  }
  //If the counter is mod 3 is 1
  if(counter%3 == 1){
    for(int x = 1; x < 8;){
    //examine every other bit of both the source and key bytes starting at bit 1
      //if the source bit xor the key bit is 0, set the same bit in the resulting byte to 0      
      if(getBit(source, x) ^ getBit(key, x) == 0){
        resultingByte = clearBit(resultingByte, x);      
      }
      //if the source bit xor the key bit is 1, set the same bit in the resulting byte to 1
      if(getBit(source, x) ^ getBit(key, x) == 1){
        resultingByte = setBit(resultingByte, x);
      }
      x = x+2;
    }
  }
  //If the counter is mod 3 is 2
  if(counter%3 == 2){
    for(int x = 0; x < 8;){
    //examine every bit of both the source and key bytes
      //if the source bit xor the key bit is 0, set the same bit in the resulting byte to 0
      if(getBit(source, x) ^ getBit(key, x) == 0){
        resultingByte = clearBit(resultingByte, x);      
      }
      //if the source bit xor the key bit is 1, set the same bit in the resulting byte to 1
      if(getBit(source, x) ^ getBit(key, x) == 1){
        resultingByte = setBit(resultingByte, x);
      }
      x = x+1;
    }
  }
  return resultingByte;
}


/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n){ 
  return (c >> n) & 1;/*Bitshifts nth place of c to position 1 and &s it with 1,
which will produce 1 if c[n] is 1 or 0 otherwise*/
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n){ 
  c = (c | (1 << n));
/*Bitshifts 1 to nth place. If the number at nth place in c is 0 the c | (1 << n) is always 1*/
  return c;
}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n){ 
  c = (c & (c ^ (1 << n))); 
/*Bitshifts 1 to nth place. If the number at nth place in c is 0 the c ^ (1 << n) is 1, else 0
Then if the number at nth place in c is 1, c & (c ^ (c(1 << n))) is 0.
*/
  return c;
}
