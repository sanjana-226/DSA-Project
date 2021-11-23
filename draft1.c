#include <stdio.h>>
#include <stdbool.h>

int main()
{
    FILE *fp = fopen("SampleInput.csv", "r");

    //find column nums

    int cols = 5;

    int data[cols][cols]; //only takes nums so no labels??
    //load data with 1s and 0s from input csv
    //labels are required for menu5 onwards so keep labels somehow??-but this might complicate things??
    //can keep 2 copies of my matrix?

    mainMenu(data, cols);
    return 0;
}   

void mainMenu(int data[][], int cols)
{
    //args are wrong??
    printf("Main Menu");
    printf("1. Does every website has a link to itself?");
    printf("2. Is it possible to always return back to the previous website from the current website in one step");
    printf("3. Does every website has all the links to websites which are reachable from it?");
    printf("4. Does there exist any website that contains a list to itself?");
    printf("5. Is it impossible to return to the previous website from the current website in one step?");
    printf("6. Is it impossible to return to the previous website from the current website in one step (excluding cases where the current and previous website is the same)?");
    printf("7. Is it possible to divide the network into multiple pieces such that every website n a piece is reachable from every other website in that piece?");
    printf("8. Is this relation an example of poset?");
    printf("9. Exit");

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        if (mainop1(data, cols))
        {
            printf("Yes");
            mainMenu(data, cols);
        }
        else
        {
            printf("No");
            menu2(1);
        }
        break;
    case 2:
        if (mainop2())
        {
            printf("Yes");
            mainMenu(data, cols);
        }
        else
        {
            printf("No");
            menu2(2);
        }
        break;
    case 3:
        if (mainop3())
        {
            printf("Yes");
            mainMenu(data, cols);
        }
        else
        {
            printf("No");
            menu2(3);
        }
        break;
    case 4:
        if (mainop4())
        {
            printf("Yes");
            mainMenu(data, cols);
        }
        else
        {
            printf("No");
        }
        break;
    case 5:
        if (mainop5())
        {
            printf("Yes");
            mainMenu(data, cols);
        }
        else
        {
            printf("No");
            mainMenu(data, cols);
        }
        break;
    case 6:
        if (mainop6())
        {
            printf("Yes");
            mainMenu(data, cols);
        }
        else
        {
            printf("No");
            mainMenu(data, cols);
        }
        break;
    case 7:
        if (mainop7())
        {
            printf("Yes");
            menu2(7);
        }
        else
        {
            printf("No");
            menu3();
        }
        break;
    case 8:
        if (mainop8())
        {
            printf("Yes");
            menu4();
        }
        else
        {
            printf("No");
            mainMenu(data, cols);
        }
        break;
    case 9:
        exit();
        break;
    }
}

bool mainop1(int data[][], int cols){
    //need args of data 2d array? and the indexes

    for(int i =0;i<cols;i++)
    {
        if (data[i][i]==0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
bool mainop2(int data[][], int cols){
    
    for(int i=0;i<cols;i++){
        for(int j=0;j<cols;j++){
            if ((data[i][j]==1) && (data[j][i]==1))
            {
                return true;
            }
        }
    }
    
}
bool mainop3(int data[][], int cols){
    //idek what that means tbh
}
bool mainop4(int data[][], int cols){
    //for any i??
    if (data[i][i]==1)
    {
        return true;
    }    
}
bool mainop5(int data[][], int cols){
    for(int i=0;i<cols;i++){
        for(int j=0;j<cols;j++){
            if ((data[i][j]==1) && (data[j][i]==0))
            {
                return true;
            }
        }
    }
}
bool mainop6(int data[][], int cols){
    for(int i=0;i<cols;i++){
        for(int j=0;j<cols;j++){
            if ((data[i][j]==1) && (data[j][i]==0) && (i!=j))
            {
                return true;
            }
        }
    }
}
bool mainop7(int data[][], int cols){
    //do some study
}
bool mainop8(int data[][], int cols){
    //do some study
}

void menu2(int data[][], int cols,int n){
    printf("Menu 2");
    printf("Do you want to visualize how the network will look if we add the minimum links to satisfy the property?");
    char response[5];
    scanf("%s", response);

    if (strcmp(response,"Yes") == 0)
    {
        switch(n)
        {
            case 1:
            fill1(data, cols);
            break;
            case 2:
            fill2(data, cols);
            break;
            case 3:
            fill3(data, cols);
            break;
            case 7:
            fill7(data, cols);
            break;
        }
    }
    else
    {
        mainMenu(data, cols);
    }
}

void fill1(int data[][], int cols){

}
void fill2(int data[][], int cols){
    
}
void fill3(int data[][], int cols){
    
}
void fill7(int data[][], int cols){
    
}

void menu3(int data[][], int cols){
    printf("Menu 3");
    printf("Do you want to know the nodes in each piece?");
    char response[5];
    scanf("%s", response);

    if (strcmp(response,"Yes") == 0)
    {
        
    }
    else
    {
        mainMenu(data, cols);
    }
}

void menu4(int data[][], int cols){
    printf("Menu 4");
    printf("1. Display the hasse diagram");
    printf("2. Display the website whose link is available in every website");
    printf("3. Display the website whcih has links of every website");
    printf("4. Display the websites which do not have links to any other website except itself");
    printf("5. Display websites which can't be reached by any website except itself");
    printf("6. Given some websites, display the websites which are reachable from all of them");
    printf("7. Given some website display all the websites from which you can reach all those websites");
    printf("8. Is this relation a lattice");
    printf("9. Return to Main Menu");

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        menu4op1(data, cols);
        break;
    case 2:
        if (mainop2(data, cols))
        menu4op2(data, cols);
        break;
    case 3:
        menu4op3(data, cols);
        break;
    case 4:
        menu4op4(data, cols);
        break;
    case 5:
        menu4op5(data, cols);
        break;
    case 6:
        
        break;
    case 7:
        
        break;
    case 8:
        if(checkLattice(data, cols))
        {
            menu5(data, cols);
        }
        break;
    case 9:
        mainMenu(data, cols);
        break;
    }
}

void menu4op1(int data[][], int cols){

}
void menu4op2(int data[][], int cols){
    
}
void menu4op3(int data[][], int cols){
    
}
void menu4op4(int data[][], int cols){
    
}
void menu4op5(int data[][], int cols){
    
}
void menu4op6(int data[][], int cols){
    
}
void menu4op7(int data[][], int cols){
    
}
void checkLattice(int data[][], int cols){
    
}

void menu5(int data[][], int cols){
    printf("Menu 5");
    printf("1. Given 2 websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach");
    printf("2. Given 2 websites A and B, display the website that can reach both A and B and is also reachable from all such websites that can reach to both A and B");
    printf("3. Is the lattice distributive?");
    printf("4. Return to Menu 4");

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        menu5op1(data, cols);
        break;
    case 2:
        menu5op2(data, cols);
        break;
    case 3:
        menu5op3(data, cols);
        break;
    case 4:
        menu4(data, cols);
        break;
    }
}

void menu5op1(int data[][], int cols){

}
void menu5op2(int data[][], int cols){
    
}
void menu5op3(int data[][], int cols){

}