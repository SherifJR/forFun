#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define q0 0
#define q1 1
#define q2 2

int transitions[3][2]= {
  {q1, q0}, //at q0 if 0 go to q1, if 1 stay at q0
  {q1, q2}, //at q1 if 0 stay at q1, if 1 go to q2 "now the string is accepted"
  {q2, q2}  //at q2 if you have 0 or 1 stay at q2.
};

int dfa(char* string){
  int current_state = 0;
  
  for(int i=0; string[i]; i++){
    char ch = string[i];
    if(ch>'1' || ch<'0') return -1;
    current_state = transitions[current_state][ch-'0'];
  }
  return current_state;
}

int main()
{
  char string[64];
  printf("Enter string to check: ");
  scanf("%63s", string);
  (dfa(string) == 2) ? printf("String %s is accepted\n", string) : printf("String you entered not accepted");

  return 0;
}
