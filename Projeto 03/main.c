#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

struct node
{
    int ID;
    char name[100], email[100], sex[20], address[100];
    double height;
    int vaccine;
    struct node *PtrNext;
};

struct node *startNode;
struct node *nodeBuffer;

void addNodes();
void editNode();
void deleteNode();
void displayList();
int generateID();
int validateEmail(char email[]);
int validateSex(char sex[]);
int validateHeight(double height);
int validateVaccine(int vaccine);

int nodeCounter = 0;

int main()
{
    startNode = NULL; 

    int option;

    do
    {
        printf("--------------- MENU ---------------\n");
        printf("1. Adicionar novo usuario\n");
        printf("2. Editar usuario existente\n");
        printf("3. Excluir usuario\n");
        printf("4. Exibir todos os usuarios\n");
        printf("0. Fehcar o programa\n");
        printf("------------------------------------\n");
        printf("Digite a opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            addNodes();
            break;
        case 2:
            editNode();
            break;
        case 3:
            deleteNode();
            break;
        case 4:
            displayList();
            break;
        case 0:
            printf("Programa encerrado.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
        printf("\n");
    } while (option != 0);

    return 0;
}

void addNodes()
{
    struct node *newNode;
    int nodeID, nodeVaccine;
    char nodeName[100], nodeEmail[100], nodeSex[20], nodeAddress[100];
    double nodeHeight;

    printf("---------- Adicionar Registro ----------\n");
    printf("Digite o nome completo: ");
    scanf(" %[^\n]", nodeName);
    printf("Digite o email: ");
    scanf(" %[^\n]", nodeEmail);

    while (validateEmail(nodeEmail) != 0)
    {
        printf("Email invalido. Tente novamente: ");
        scanf(" %[^\n]", nodeEmail);
    }

    printf("Digite o sexo (Masculino, Feminino ou Indiferente): ");
    scanf(" %[^\n]", nodeSex);
    nodeSex[0] = toupper(nodeSex[0]);

    while (validateSex(nodeSex) != 0)
    {
        printf("Sexo invalido. Tente novamente: ");
        scanf(" %[^\n]", nodeSex);
        nodeSex[0] = toupper(nodeSex[0]);
    }

    printf("Digite o endereco: ");
    scanf(" %[^\n]", nodeAddress);
    printf("Digite a altura (Entre 1.0 e 2.0): ");
    scanf("%lf", &nodeHeight);

    while (validateHeight(nodeHeight) != 0)
    {
        printf("Altura invalida. Tente novamente: ");
        scanf("%lf", &nodeHeight);
    }

    printf("Digite o status de vacinacao (1 para sim, 0 para nao): ");
    scanf("%d", &nodeVaccine);

    while (validateVaccine(nodeVaccine) != 0)
    {
        printf("Status de vacinacao invalido. Tente novamente: ");
        scanf("%d", &nodeVaccine);
    }

    nodeID = generateID();

    newNode = (struct node *)malloc(sizeof(struct node));

    strcpy(newNode->name, nodeName);
    strcpy(newNode->email, nodeEmail);
    strcpy(newNode->sex, nodeSex);
    strcpy(newNode->address, nodeAddress);
    newNode->height = nodeHeight;
    newNode->vaccine = nodeVaccine;
    newNode->ID = nodeID;
    newNode->PtrNext = NULL;

    if (startNode == NULL)
    {
        startNode = newNode;
    }
    else
    {
        nodeBuffer->PtrNext = newNode;
    }

    nodeBuffer = newNode;

    nodeCounter++;
    printf("\nRegistro adicionado com sucesso!\n");
    printf("---------------------------------------\n");
}

void editNode()
{
    int searchID, found = 0;
    struct node *currentNode;
    currentNode = startNode;

    printf("---------- Editar Registro ----------\n");
    printf("Digite o ID do registro que deseja editar: ");
    scanf("%d", &searchID);

    if (startNode == NULL)
    {
        printf("A lista esta vazia. Nenhum registro para editar.\n");
        return;
    }

    while (currentNode != NULL)
    {
        if (currentNode->ID == searchID)
        {
            found = 1;
            break;
        }
        currentNode = currentNode->PtrNext;
    }

    if (found == 1)
    {
        printf("Registro encontrado. Digite as novas informacoes:\n");

        printf("Digite o nome completo: ");
        scanf(" %[^\n]", currentNode->name);
        printf("Digite o email: ");
        scanf(" %[^\n]", currentNode->email);

        while (validateEmail(currentNode->email) != 0)
        {
            printf("Email invalido. Tente novamente: ");
            scanf(" %[^\n]", currentNode->email);
        }

        printf("Digite o sexo (Masculino, Feminino ou Indiferente): ");
        scanf(" %[^\n]", currentNode->sex);
        currentNode->sex[0] = toupper(currentNode->sex[0]);

        while (validateSex(currentNode->sex) != 0)
        {
            printf("Sexo invalido. Tente novamente: ");
            scanf(" %[^\n]", currentNode->sex);
            currentNode->sex[0] = toupper(currentNode->sex[0]);
        }

        printf("Digite o endereco: ");
        scanf(" %[^\n]", currentNode->address);
        printf("Digite a altura (Entre 1.0 e 2.0): ");
        scanf("%lf", &currentNode->height);

        while (validateHeight(currentNode->height) != 0)
        {
            printf("Altura invalida. Tente novamente: ");
            scanf("%lf", &currentNode->height);
        }

        printf("Digite o status de vacinacao (1 para sim, 0 para nao): ");
        scanf("%d", &currentNode->vaccine);

        while (validateVaccine(currentNode->vaccine) != 0)
        {
            printf("Status de vacinacao invalido. Tente novamente: ");
            scanf("%d", &currentNode->vaccine);
        }

        printf("\nRegistro editado com sucesso!\n");
    }
    else
    {
        printf("Registro nao encontrado.\n");
    }

    printf("-------------------------------------\n");
}

void deleteNode()
{
    struct node *previousNode, *currentNode;
    int searchID, found = 0;

    printf("---------- Excluir Registro ----------\n");
    printf("Digite o ID do registro que deseja excluir: ");
    scanf("%d", &searchID);

    if (startNode == NULL)
    {
        printf("A lista esta vazia. Nenhum registro para excluir.\n");
        return;
    }

    currentNode = startNode;
    while (currentNode != NULL)
    {
        if (currentNode->ID == searchID)
        {
            found = 1;
            break;
        }
        previousNode = currentNode;
        currentNode = currentNode->PtrNext;
    }

    if (found == 1)
    {
        if (currentNode == startNode)
        {
            startNode = currentNode->PtrNext;
        }
        else
        {
            previousNode->PtrNext = currentNode->PtrNext;
        }

        free(currentNode);
        nodeCounter--;

        printf("Registro excluido com sucesso!\n");
    }
    else
    {
        printf("Registro nao encontrado.\n");
    }

    printf("--------------------------------------\n");
}

void displayList()
{
    struct node *currentNode;
    currentNode = startNode;

    printf("---------- Lista de Registros ----------\n");

    if (startNode == NULL)
    {
        printf("A lista esta vazia. Nenhum registro para exibir.\n");
        return;
    }

    while (currentNode != NULL)
    {
        printf("ID: %d\n", currentNode->ID);
        printf("Nome: %s\n", currentNode->name);
        printf("Email: %s\n", currentNode->email);
        printf("Sexo: %s\n", currentNode->sex);
        printf("Endereco: %s\n", currentNode->address);
        printf("Altura: %.2f\n", currentNode->height);
        printf("Status de vacinacao: %s\n", currentNode->vaccine == 1 ? "Sim" : "Nao");
        printf("--------------------------------------\n");
        currentNode = currentNode->PtrNext;
    }
}

int generateID()
{
    srand(time(NULL));
    int id = rand() % 1000 + 1;
    struct node *currentNode = startNode;

    while (currentNode != NULL)
    {
        if (currentNode->ID == id)
        {
            id = rand() % 1000 + 1;
            currentNode = startNode;
        }
        else
        {
            currentNode = currentNode->PtrNext;
        }
    }

    return id;
}

int validateEmail(char email[])
{
    int i, at = 0, dot = 0;

    for (i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            at++;
        }
        if (email[i] == '.')
        {
            dot++;
        }
    }

    if (at == 1 && dot >= 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int validateSex(char sex[])
{
    if (strcmp(sex, "Masculino") == 0 || strcmp(sex, "Feminino") == 0 || strcmp(sex, "Indiferente") == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int validateHeight(double height)
{
    if (height >= 1.0 && height <= 2.0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int validateVaccine(int vaccine)
{
    if (vaccine == 0 || vaccine == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
