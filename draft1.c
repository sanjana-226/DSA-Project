#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<unistd.h> 

char** websites;
char* graph;
int website_count=0;

bool mainop1();
bool mainop2();
bool mainop3();
bool mainop4();
bool mainop5();
bool mainop6();
bool mainop7();
bool mainop8();
bool checkTransitive();
bool checkAntiSymm();
void mainMenu();
void menu2(int n);
void fill1();
void fill2();
void fill3();
void fill7();
void menu3();
void menu4();
void menu4op1();
void menu4op2();
void menu4op3();
void menu4op4();
void menu4op5();
void menu4op6();
void menu4op7();
void checkLattice();
void menu5();
void menu5op1();
void menu5op2();
void menu5op3();

void plot(char * fname){
    int pid;
    if((pid = fork())==0){
        if(execlp("python", "python","visualise.py",fname,(char*)NULL)==-1){
        	execlp("python3", "python3","visualise.py",fname,(char*)NULL);
        };
    }
    exit(0);
}

void connect(int i, int j){
    graph[i*website_count+j] = true;
}

void connect2(char* graph,int i, int j){
    graph[i*website_count+j] = true;
}

bool is_connected(int i, int j){
    return graph[i*website_count+j];
}

void print_graph(){
    for (int i = 0; i < website_count; i++) {
        for (int j = 0; j < website_count; j++) {
            printf("%d ", is_connected(i,j));
        }
        printf("\n");
    }
}

void print_header(){
    printf("%d\n", website_count);
    for(int i = 0; i< website_count; i++)
        printf("%s\n", websites[i]);
}

void parse_header(char* header){
    int count=0;
    websites = malloc(sizeof(char*)*100);
    
    char* website = (char*) malloc(sizeof(char)*100);
    for(int i = 1; i<strlen(header); i++)
    {
        if (header[i]==',' || i == strlen(header)-1)
        {
            strncat(website, "\0", 1);
            websites[count] = website;
            website = (char*) malloc(sizeof(char)*100);
            count++;
        }
        else{
            strncat(website, &header[i], 1);
        }
    }
    website_count = count;
}

void parse_graph(FILE* fp){
    graph = calloc(sizeof(bool)*website_count, website_count);
    for(int row = 0; row<website_count; row++){
        while(getc(fp)!=',') ; //skip the first column
        for (int col = 0; col < website_count; col++) {
            if(getc(fp)=='1')
                connect(row,col);
            if(col!=website_count-1) // not last iteration
                getc(fp);
        }
    }
}

int main()
{
    FILE *fp = fopen("SampleInput.csv", "r");
    char header[1000];
    fgets(header, sizeof(header), fp);
    parse_header(header);
    print_header();
    parse_graph(fp);
    print_graph();
    mainMenu();
    return 0;
}   

void mainMenu()
{
    printf("Main Menu\n");
    printf("1. Does every website has a link to itself?\n");
    printf("2. Is it possible to always return back to the previous website from the current website in one step\n");
    printf("3. Does every website has all the links to websites which are reachable from it?\n");
    printf("4. Does there exist any website that contains a list to itself?\n");
    printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
    printf("6. Is it impossible to return to the previous website from the current website in one step (excluding cases where the current and previous website is the same)?\n");
    printf("7. Is it possible to divide the network into multiple pieces such that every website n a piece is reachable from every other website in that piece?\n");
    printf("8. Is this relation an example of poset?\n");
    printf("9. Exit\n\n");

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        if (mainop1())
        {
            printf("Yes\n\n");
            mainMenu();
        }
        else
        {
            printf("No\n\n");
            menu2(1);
        }
        break;
    case 2:
        if (mainop2())
        {
            printf("Yes\n\n");
            mainMenu();
        }
        else
        {
            printf("No\n\n");
            menu2(2);
        }
        break;
    case 3:
        if (mainop3())
        {
            printf("Yes\n\n");
            mainMenu();
        }
        else
        {
            printf("No\n\n");
            menu2(3);
        }
        break;
    case 4:
        if (mainop4())
        {
            printf("Yes\n\n");
            mainMenu();
        }
        else
        {
            printf("No\n\n");
        }
        break;
    case 5:
        if (mainop5())
        {
            printf("Yes\n\n");
            mainMenu();
        }
        else
        {
            printf("No\n\n");
            mainMenu();
        }
        break;
    case 6:
        if (mainop6())
        {
            printf("Yes\n\n");
            mainMenu();
        }
        else
        {
            printf("No\n\n");
            mainMenu();
        }
        break;
    case 7:
        if (mainop7())
        {
            printf("Yes\n\n");
            menu2(7);
        }
        else
        {
            printf("No\n\n");
            menu3();
        }
        break;
    case 8:
        if (mainop8())
        {
            printf("Yes\n\n");
            menu4();
        }
        else
        {
            printf("No\n\n");
            mainMenu();
        }
        break;
    case 9:
        exit(0);
        break;
    }
}

bool mainop1(){
    //need args of data 2d array? and the indexes

    for(int i=0;i<website_count;i++)
    {
        if (is_connected(i,i)==0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
bool mainop2(){
    
    for(int i=0;i<website_count;i++){
        for(int j=0;j<website_count;j++){
            if ((is_connected(i,j)==1) && (is_connected(j,i)==1))
            {
                return true;
            }
        }
    }
    
}
bool mainop3(){
    for(int i=0;i<website_count;i++){
        for(int j=0;j<website_count;j++){
            if (is_connected(i,j)==0)
            {
                return false;
            }   
        }
    }
}
bool mainop4(){
    //for any i??
for(int i=0;i<website_count;i++){
    if (is_connected(i,i)==1)
        {
            return true;
        }   
}
     
}
bool mainop5(){
    for(int i=0;i<website_count;i++){
        for(int j=0;j<website_count;j++){
            if ((is_connected(i,j)==1) && (is_connected(j,i)==0))
            {
                return true;
            }
        }
    }
}
bool mainop6(){
    for(int i=0;i<website_count;i++){
        for(int j=0;j<website_count;j++){
            if ((is_connected(i,j)==1) && (is_connected(j,i)==0) && (i!=j))
            {
                return true;
            }
        }
    }
}
bool mainop7(){
    //do some study
}
bool mainop8(){
    if(mainop1()&&checkAntiSymm()&&checkTransitive())
    {
        return true;
    }
}

bool checkTransitive(){
    for(int i=0;i<website_count;i++){
        for(int j=0;j<website_count;j++){
            for( int k=0;k<website_count;k++){
                if ((is_connected(i,j)) && (is_connected(j,k)) && (is_connected(i,k)))
            {
                    return true;
            }
            } 
        }
    }
}
bool checkAntiSymm(){
    for(int i=0;i<website_count;i++){
        for(int j=0;j<website_count;j++){
            if ((is_connected(i,j)==1) && (is_connected(j,i)==0))
            {
                return true;
            }
        }
    }
}

void menu2(int n){
    printf("Menu 2\n");
    printf("Do you want to visualize how the network will look if we add the minimum links to satisfy the property?\n");
    char response[5];
    scanf("%s", response);

    if (strcmp(response,"Yes") == 0)
    {
        switch(n)
        {
            case 1:
            fill1();
            break;
            case 2:
            fill2();
            break;
            case 3:
            fill3();
            break;
            case 7:
            fill7();
            break;
        }
    }
    else
    {
        printf("\n");
        mainMenu();
    }
}

void fill1(){
    char* graph1 = malloc(strlen(graph)+1);
    strcpy(graph1,graph);
    for(int i=0;i<website_count;i++)
    {
        if (is_connected(i,i)==0)
        {
            connect2(graph1,i,i);
        }
    }
    plot(graph1);
}
void fill2(){
    char* graph2 = malloc(strlen(graph)+1);
    strcpy(graph2,graph);
    for(int i=0;i<website_count;i++)
    {
        for(int j=0;j<website_count;j++)
        {
            if (is_connected(i,j)==1)
                    {
                        connect2(graph2,j,i);
                    }
        }
        
    }
    plot(graph2);
}
void fill3(){
    char* graph3 = malloc(strlen(graph)+1);
    strcpy(graph3,graph);
    for(int i=0;i<website_count;i++)
    {
        for(int j=0;j<website_count;j++)
        {
            if (is_connected(i,j)==0)
                    {
                        connect2(graph3,i,j);
                    }
        }
        
    }
    plot(graph3);
}
void fill7(){
    
}

void menu3(){
    printf("Menu 3\n");
    printf("Do you want to know the nodes in each piece?\n\n");
    char response[5];
    scanf("%s", response);

    if (strcmp(response,"Yes") == 0)
    {
        
    }
    else
    {
        mainMenu();
    }
}

void menu4(){
    printf("Menu 4\n");
    printf("1. Display the hasse diagram\n");
    printf("2. Display the website whose link is available in every website\n");
    printf("3. Display the website whcih has links of every website\n");
    printf("4. Display the websites which do not have links to any other website except itself\n");
    printf("5. Display websites which can't be reached by any website except itself\n");
    printf("6. Given some websites, display the websites which are reachable from all of them\n");
    printf("7. Given some website display all the websites from which you can reach all those websites\n");
    printf("8. Is this relation a lattice\n");
    printf("9. Return to Main Menu\n\n");

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        menu4op1();
        break;
    case 2:
        if (mainop2())
        menu4op2();
        break;
    case 3:
        menu4op3();
        break;
    case 4:
        menu4op4();
        break;
    case 5:
        menu4op5();
        break;
    case 6:
        
        break;
    case 7:
        
        break;
    case 8:
        //if(checkLattice())
        //{
        //    menu5();
        //}
        //break;
    case 9:
        mainMenu();
        break;
    }
    printf("\n");
}

void menu4op1(){

}
void menu4op2(){
    
}
void menu4op3(){
    
}
void menu4op4(){
    
}
void menu4op5(){
    
}
void menu4op6(){
    
}
void menu4op7(){
    
}
void checkLattice(){
    
}

void menu5(){
    printf("Menu 5\n");
    printf("1. Given 2 websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach\n");
    printf("2. Given 2 websites A and B, display the website that can reach both A and B and is also reachable from all such websites that can reach to both A and B\n");
    printf("3. Is the lattice distributive?\n");
    printf("4. Return to Menu 4\n\n");

    int a;
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        menu5op1();
        break;
    case 2:
        menu5op2();
        break;
    case 3:
        menu5op3();
        break;
    case 4:
        menu4();
        break;
    }
}

void menu5op1(){

}
void menu5op2(){
    
}
void menu5op3(){


}
