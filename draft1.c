#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char **websites;
bool *graph;
int website_count = 0;
bool *visited = NULL;

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
bool checkLattice();
void menu5();
void menu5op1();
void menu5op2();
bool menu5op3();
bool is_connected(int i, int j);
bool is_connected2(bool *graph, int i, int j);
int checkLUB(int i, int j);
int checkGLB(int i, int j);
int LUB(int i, int j);
int GLB(int i, int j);
void dfs1(int node);
void dfs2(int node);

typedef struct
{
    int *data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} Stack;

Node *newNode(int data, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = next;
    return node;
}

int pop(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("Stack is empty\n");
        return -1;
    }
    Node *temp = stack->head;
    stack->head = stack->head->next;
    stack->size--;
    int data = temp->data;
    free(temp);
    return data;
}

Stack *push(Stack *stack, int value)
{
    Node *node = newNode(value, stack->head);
    stack->head = node;
    stack->size++;
    return stack;
}

void plot(char *fname)
{
    int pid;
    if ((pid = fork()) == 0)
    {
        if (execlp("python", "python", "visualise.py", fname, (char *)NULL) == -1)
        {
            execlp("python3", "python3", "visualise.py", fname, (char *)NULL);
        };
    }
    exit(0);
}

void connect(int i, int j)
{
    graph[i * website_count + j] = true;
}

void connect2(bool *graph, int i, int j)
{
    graph[i * website_count + j] = true;
}

void disconnect2(bool *graph, int i, int j)
{
    graph[i * website_count + j] = false;
}

bool is_connected(int i, int j)
{
    return graph[i * website_count + j];
}

bool is_connected2(bool *graph, int i, int j)
{
    return graph[i * website_count + j];
}

bool path(int node1, int node2)
{
    if (visited == NULL)
        visited = (bool *)malloc(sizeof(bool) * website_count);

    if (is_connected(node1, node2))
        return true;

    for (int x = 0; x < website_count; x++)
    {
        if (visited[x] == true)
            continue;

        visited[x] = true;
        if (is_connected(node1, x) && path(x, node2))
            return true;
    }

    return false;
}

bool path2(int node1, int node2)
{
    bool *visited = NULL;
    path(node1, node2);
    return true;
}
void print_graph()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            printf("%d ", is_connected(i, j));
        }
        printf("\n");
    }
}

void print_header()
{
    printf("%d\n", website_count);
    for (int i = 0; i < website_count; i++)
        printf("%s\n", websites[i]);
}

bool valid_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-';
}

void parse_header(bool *header)
{
    int count = 0;
    websites = malloc(sizeof(bool *) * 100);

    bool *website = (bool *)malloc(sizeof(char) * 100);
    int header_length = strlen(header);
    //start at 1 to skip starting comma
    for (int i = 1; i < header_length; i++)
    {
        if (!valid_char(header[i]) || i == header_length - 1)
        {
            if (strlen(website) > 0)
            {
                strncat(website, "\0", 1);
                websites[count] = website;
                count++;
            }
            website = (char *)malloc(sizeof(char) * 100);
        }
        else
        {
            strncat(website, &header[i], 1);
        }
    }
    website_count = count;
}

void parse_graph(FILE *fp)
{
    graph = calloc(sizeof(bool) * website_count, website_count);
    for (int row = 0; row < website_count; row++)
    {
        while (getc(fp) != ',')
            ;
        for (int col = 0; col < website_count; col++)
        {
            if (getc(fp) == '1')
                connect(row, col);
            if (col != website_count - 1)
                getc(fp);
        }
    }
}

void convertToCSV(bool *graph)
{
    FILE *p;
    p = fopen("graph.csv", "w");
    fprintf(p, ",");

    for (int i = 0; i < website_count; i++)
    {
        fprintf(p, "%s %d", websites[i], i);
        if (i != website_count - 1)
            fprintf(p, ",");
    }
    fprintf(p, "%c", '\n');

    for (int i = 0; i < website_count; i++)
    {
        fprintf(p, "%s,", websites[i]);
        for (int j = 0; j < website_count; j++)
        {
            fprintf(p, "%d", is_connected2(graph, i, j));
            if (j != website_count - 1)
                fprintf(p, ",");
        }
        fprintf(p, "%c", '\n');
    }
    fclose(p);
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

bool mainop1()
{
    for (int i = 0; i < website_count; i++)
    {
        if (is_connected(i, i) == 0)
        {
            return false;
        }
    }
    return true;
}
bool mainop2()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if ((is_connected(i, j) == 1) && (is_connected(j, i) == 1))
            {
                return true;
            }
        }
    }
    return false;
}
bool mainop3()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (is_connected(i, j) == 0)
            {
                return false;
            }
        }
    }
    return true;
}
bool mainop4()
{
    for (int i = 0; i < website_count; i++)
    {
        if (is_connected(i, i) == 1)
        {
            return true;
        }
    }
    return false;
}
bool mainop5()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if ((is_connected(i, j) == 1) && (is_connected(j, i) == 0))
            {
                return true;
            }
        }
    }
    return false;
}
bool mainop6()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if ((is_connected(i, j) == 1) && (is_connected(j, i) == 0) && (i != j))
            {
                return true;
            }
        }
    }
    return false;
}
// bool mainop7()
// {
//     //do some study
// }

Stack stack;
bool *visited;

int *component;
Stack *componentNodes;
int numComponents;

void dfs1(int node)
{
    visited[node] = true;
    for (int x = 0; x < website_count; x++)
    {
        if (visited[x] == true)
            continue;

        if (is_connected(node, x))
        {
            dfs1(x);
        }
    }
    push(&stack, node);
}

void dfs2(int node)
{
    printf("%s", websites[node]);
    component[node] = numComponents;
    push(&componentNodes[node], node);
    visited[node] = true;
    for (int x = 0; x < website_count; x++)
    {
        if (visited[x] == true)
            continue;

        if (is_connected(x, node))
        {
            dfs2(x);
        }
    }
    push(&stack, node);
}

bool mainop7()
{
    fill7();
    for (int i = 0; i < website_count; i++)
    {
        if (visited[i] == 0)
        {
            return false;
        }
    }
}

void fill7()
{

    visited = (bool *)calloc(sizeof(bool), website_count);
    componentNodes = calloc(sizeof(Stack), website_count);
    component = calloc(sizeof(int), website_count);

    for (int i = 0; i < website_count; i++)
    {
        component[i] = -1;
    }

    for (int i = 0; i < website_count; i++)
        if (!visited[i])
            dfs1(i);

    for (int i = 0; i < website_count; i++)
        visited[i] = false;

    while (stack.size > 0)
    {
        int v = pop(&stack);
        if (!visited[v])
        {
            printf("Component %d: ", numComponents);
            dfs2(v);
            numComponents++;
            printf("\n");
        }
    }
}

bool mainop8()
{
    if (mainop1() && checkAntiSymm() && checkTransitive())
    {
        return true;
    }
    return false;
}
bool checkTransitive()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            for (int k = 0; k < website_count; k++)
            {
                if ((is_connected(i, j)) && (is_connected(j, k)) && (is_connected(i, k)))
                {
                    return true;
                }
            }
        }
    }
}
bool checkAntiSymm()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if ((is_connected(i, j) == 1) && (is_connected(j, i) == 0))
            {
                return true;
            }
        }
    }
}

void menu2(int n)
{
    printf("Menu 2\n");
    printf("Do you want to visualize how the network will look if we add the minimum links to satisfy the property? [Y/N] \n");
    char response[100];
    scanf("%s", response);

    char correct[] = "Y";
    int k = strncmp(response, correct, 3);

    // int k = 0;
    if (k == 0)
    {
        switch (n)
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

void fill1()
{
    bool *graph1 = malloc(sizeof(char) * website_count * website_count);
    memcpy(graph1, graph, sizeof(char) * website_count * website_count);
    for (int i = 0; i < website_count; i++)
    {
        if (is_connected(i, i) == 0)
        {
            connect2(graph1, i, i);
        }
    }

    convertToCSV(graph1);
    plot("graph.csv");
}
void fill2()
{
    bool *graph2 = malloc(sizeof(char) * website_count * website_count);
    memcpy(graph2, graph, sizeof(char) * website_count * website_count);
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (is_connected(i, j) == 1)
            {
                connect2(graph2, j, i);
            }
        }
    }

    convertToCSV(graph2);
    plot("graph.csv");
}
void fill3()
{
    bool *graph3 = malloc(sizeof(char) * website_count * website_count);
    memcpy(graph3, graph, sizeof(char) * website_count * website_count);
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (is_connected(i, j) == 0)
            {
                connect2(graph3, i, j);
            }
        }
    }
    convertToCSV(graph3);
    plot("graph.csv");
}
// void fill7()
// {
// }

void menu3()
{
    printf("Menu 3\n");
    printf("Do you want to know the nodes in each piece? [Y/N] \n\n");
    char response[5];
    scanf("%s", response);

    if (strcmp(response, "Y") == 0)
    {
        //find nodes,print
    }
    else
    {
        mainMenu();
    }
}

void menu4()
{
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
        if (checkLattice())
        {
            menu5();
        }
        break;
    case 9:
        mainMenu();
        break;
    }
    printf("\n");
}

void menu4op1()
{
    bool *hasse = malloc(sizeof(char) * website_count * website_count);
    memcpy(hasse, graph, sizeof(char) * website_count * website_count);
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (is_connected(i, j) == 1)
            {
                disconnect2(hasse, i, j);
            }
            for (int k = 0; k < website_count; k++)
            {
                if ((is_connected(i, j) == 1) && (is_connected(j, k) == 1) && (is_connected(i, k) == 1))
                {
                    disconnect2(hasse, i, k);
                }
            }
        }
    }
    convertToCSV(hasse);
    plot("graph.csv");
}
void menu4op2()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (is_connected(i, j))
            {
                printf("%s", websites[i]);
            }
        }
    }
}
void menu4op3()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            printf("%s", websites[j]);
        }
    }
}
void menu4op4()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if ((is_connected(i, i) == 1) && (is_connected(i, j) == 0))
            {
                printf("%s", websites[i]);
            }
        }
    }
}
void menu4op5()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if ((is_connected(i, i) == 1) && (is_connected(j, i) == 0))
            {
                printf("%s", websites[i]);
            }
        }
    }
}
void menu4op6()
{
    char inputs[100];
    scanf("Type the names of the websites(space separated)%[^\n]", inputs);
    char delim[] = " ";
    char *ptr = strtok(inputs, delim);
    while (ptr != NULL)
    {
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }
    int inputIndex[100];
    int count = strlen(inputs);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (strcmp(websites[j], inputs[i]))
            {
                inputIndex[i] = j;
            }
            else
            {
                //deal with this somehow?
            }
        }
    }

    for (int x = 0; x < website_count; x++)
    {
        for (int i = 0; i < count; i++)
        {
            if (is_connected(inputIndex[i], x) == 0)
            {
                printf("%s", websites[x]);
                //this doesnt make logical sense
            }
        }
    }
}
void menu4op7()
{
    char inputs[100];
    scanf("Type the names of the websites(space separated)%[^\n]", inputs);
    char delim[] = " ";
    char *ptr = strtok(inputs, delim);
    while (ptr != NULL)
    {
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }
    int inputIndex[100];
    int count = strlen(inputs);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (strcmp(websites[j], inputs[i]))
            {
                inputIndex[i] = j;
            }
            else
            {
                //deal with this somehow?
            }
        }
    }

    for (int x = 0; x < website_count; x++)
    {
        for (int i = 0; i < count; i++)
        {
            if (is_connected(x, inputIndex[i]) == 0)
            {
                printf("%s", websites[x]);
                //this doesnt make logical sense
            }
        }
    }
}
bool checkLattice()
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if (checkLUB(i, j) == 1 && checkGLB(i, j) == 1)
                return true;
        }
    }
}
int checkLUB(int i, int j)
{
    int count1 = 0;
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            for (int x = 0; x < website_count; x++)
            {
                if (path2(x, i) && path2(x, j))
                {
                    count1++;
                    return count1;
                }
            }
        }
    }
}
int checkGLB(int i, int j)
{
    int count2 = 0;
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            for (int y = 0; y < website_count; y++)
            {
                if (path2(i, y) && path2(j, y))
                {
                    count2++;
                    return count2;
                }
            }
        }
    }
}

void menu5()
{
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
        if (menu5op3())
            printf("Yes");
        else
            printf("No");
        break;
    case 4:
        menu4();
        break;
    }
}

void menu5op1()
{
    char A[100];
    int AIndex;
    int BIndex;
    scanf("Type the first website %s", A);

    for (int i = 0; i < website_count; i++)
    {
        if (strcmp(websites[i], A))
        {
            AIndex = i;
        }
        else
        {
            printf("Invalid website name ");
            menu5op1();
        }
    }

    char B[100];
    scanf("Type the second website %s", B);

    for (int i = 0; i < website_count; i++)
    {
        if (strcmp(websites[i], B))
        {
            BIndex = i;
        }
        else
        {
            printf("Invalid website name ");
            menu5op1();
        }
    }

    for (int x = 0; x < website_count; x++)
    {
        if ((is_connected(AIndex, x)) && (is_connected(BIndex, x)))
        {
            for (int y = 0; y < website_count; y++)
            {
                if ((path(AIndex, y)) && (path(BIndex, y)) && (path(x, y)))
                {
                    printf("%s ", websites[x]);
                }
            }
        }
    }
}
void menu5op2()
{

    char A[100];
    int AIndex;
    int BIndex;
    scanf("Type the first website %s", A);

    for (int i = 0; i < website_count; i++)
    {
        if (strcmp(websites[i], A))
        {
            AIndex = i;
        }
        else
        {
            printf("Invalid Website");
            menu5op2();
        }
    }

    char B[100];
    scanf("Type the second website %s", B);

    for (int i = 0; i < website_count; i++)
    {
        if (strcmp(websites[i], B))
        {
            BIndex = i;
        }
        else
        {
            printf("Invalid Website");
            menu5op2();
        }
    }

    for (int x = 0; x < website_count; x++)
    {
        if ((path(x, AIndex)) && (path(x, BIndex)))
        {
            for (int y = 0; y < website_count; y++)
            {
                if ((path(y, AIndex)) && (path(y, BIndex)) && (path(y, x)))
                {
                    printf("%s", websites[x]);
                }
            }
        }
    }
}
bool menu5op3()
{
    for (int a = 0; a < website_count; a++)
    {
        for (int b = 0; b < website_count; b++)
        {
            for (int c = 0; c < website_count; c++)
            {
                if (GLB(a, LUB(b, c)) == LUB(GLB(a, b), GLB(a, c)))
                    return true;
            }
        }
    }
    return false;
}

int LUB(int i, int j)
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            for (int x = 0; x < website_count; x++)
            {
                if (path2(x, i) && path2(x, j))
                {
                    return x;
                }
            }
        }
    }
}
int GLB(int i, int j)
{
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            for (int y = 0; y < website_count; y++)
            {
                if (path2(i, y) && path2(j, y))
                {
                    return y;
                }
            }
        }
    }
}
