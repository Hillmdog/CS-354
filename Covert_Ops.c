#include <stdio.h>
#define N 4

int f0();//generats code 1
int f1();//generates code 2
int f2(int i);//generates code 3
void f3(int num, int *code);//generates code 4
void f3_helper(int *code);//help generate code 4
int Is_Number_Correct(int code, int correct, int num);//checks that the user codes match the generated ones

//i decided to leave the variable names as they are represented in x86 to help follow what i think was going on
int main() {
    int i;
    int n[N];
    int a[N];
    int c = 0;

    // get numbers from user
    printf("Enter four numbers: ");
    for (i = 0; i<N; i++) scanf("%d", &n[i]);
    printf("\nYou have entered: %d, %d, %d, %d\n",n[0], n[1], n[2], n[3]);
    
    // get answers
    a[0] = f0(); 
    a[1] = f1();
    a[2] = f2(i);
    a[3] = 4046;  
    f3(a[3], &a[3]);

    // print answers
    //for (i = 0; i< N; i++) printf("answers #%d = %d\n",i,a[i]);

    // test 
    c += Is_Number_Correct(n[0], a[0], 0);
    c += Is_Number_Correct(n[1], a[1], 1);
    c += Is_Number_Correct(n[2], a[2], 2);
    c += Is_Number_Correct(n[3], a[3], 3);
    // report results
    if (c==0) printf("You didn't get any correct numbers. Please try again.\n");
    if (c > 0 && c < N) printf("You got %d correct numbers.  Please try again.\n", c);
    if (c==N) printf("All numbers are correct! Nice work!\n");

    return 0;
}


int f0(){
    int eax = 5589516;
    return eax;
}


int f1(){
    int eax, edx;
    int four_ebp = 25027;
    int eight_ebp = 51330;
    int c_ebp = 67548;
    int ten_ebp = 30404;
    int fourteen_ebp = 49;
    int eighteen_ebp = 17;
    edx = eight_ebp;
    eax = c_ebp;
    if (four_ebp > eax){
        eax = four_ebp;
    }
    else{
        eax = four_ebp;
        eax = eax * eight_ebp;
    }
    if (ten_ebp < eax){
        eax = c_ebp;
        c_ebp = eax % fourteen_ebp;
        eax = c_ebp;
    }
    else{
        eax = ten_ebp;
        ten_ebp = eax / eight_ebp;
        eax = ten_ebp;
    }
    return eax;
}


int f2(int i){
    int eax = 0;
    int four_ebp = 0;
    int eight_ebp = 0;
    int pos_ebp = i;
    while (four_ebp <= 27){
        eax = four_ebp;
        eax = eax * eax;
        int edx = eax;
        eax = pos_ebp;
        eax = eax + edx;
        eight_ebp = eight_ebp + eax;
        four_ebp = four_ebp + 1;
    }
    eax = eight_ebp;
    return eax;
}


void f3(int num,int *code){
    int eax = *code;
    f3_helper(code);
    eax = *code;
    f3_helper(code);
    eax = num;
    int edx = *code;
    edx = edx * 2 * 2 * 2;
    edx = eax + edx;
    eax = num;
    *code = edx;
}

void f3_helper(int *code){
    int four_ebp = 3;
    int eax = *code;
    int edx = eax;
    eax = four_ebp;
    edx = eax + edx;
    *code = edx;
}

int Is_Number_Correct(int code, int correct, int num){
    int eax = code;
    if(code == correct){
        eax = 1;
        printf("Number %d: Correct. Nice Job.\n", num);
    }
    else{
        eax = 0;
        printf("Number %d: Incorrect\n", num);
    }
    return eax;
}
