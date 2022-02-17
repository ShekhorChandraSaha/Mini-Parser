#include<bits/stdc++.h>
using namespace std;

/// fp = first parenthesis, sp = second parenthesis, tp = third parenthesis.

string lines[100];
int linelen=0;

struct node
{
    char data;
    struct node *next;
}*topfp=NULL,*topsp=NULL,*toptp=NULL;

struct errorlist
{
    int data;
    struct errorlist *next;
}*head=NULL,*tail=NULL;


void checklist(int val);
void createlist(int val);
void print();
void pushfp(char x);
void popfp(int x);
void pushsp(char x);
void popsp(int x);
void pushtp(char x);
void poptp(int x);



int main()
{
    ifstream file("dataset.txt",ios::in);
    string templine;

    while(!file.eof())
    {

        getline(file,templine);
        lines[linelen++] = templine;
    }

    for(int i=0;i<linelen;i++)
    {
        for(int k=0;k<lines[i].length();k++)
        {
            if(lines[i][k]== '(')
            {
                pushfp(lines[i][k]);
            }
            if(lines[i][k]==')')
            {
                popfp(i+1);
            }
            if(lines[i][k]== ';' || lines[i][k] == '{' || lines[i][k] == '}')
            {
                if(topfp != NULL)
                {
                 checklist(i+1);
                 while(topfp != NULL)
                 {
                     popfp(i+1);
                 }
                }
            }
            if(lines[i][k]== '[')
            {
                pushtp(lines[i][k]);
            }
            if(lines[i][k]==']')
            {
                poptp(i+1);
            }
            if(lines[i][k] == ')' || lines[i][k] == ';' || lines[i][k] == '{' || lines[i][k] == '}')
            {
                if(toptp != NULL)
                {
                 checklist(i+1);
                 while(toptp != NULL)
                 {
                     poptp(i+1);
                 }
                }
            }
            if(lines[i][k]== '{')
            {
                pushsp(lines[i][k]);
            }
            if(lines[i][k]=='}')
            {
                popsp(i+1);
            }



        }
    }
    if(topsp != NULL)
    {
        checklist(linelen-1);
    }

     print();


     return 0;
}

void checklist(int val)
{
    int flag = 1 ;
    struct errorlist *temp;
    temp=head;
    while(1)
    {
        if(temp==NULL)
        {
            break;
        }
        else if(temp->data==val)
            {
                flag = -1;
                break;
            }
        else
        {
            temp = temp->next;
        }
    }

    if(flag == 1)
    {
        createlist(val);
    }
}

void createlist(int val)
{

    struct errorlist *curr;
    curr=(struct errorlist *)malloc(sizeof(struct errorlist));
    curr->data = val;
    curr->next = NULL;
    if(head==NULL)
    {
        head= curr;
        tail=curr;
    }
    else
    {
        tail->next = curr;
        tail=curr;

    }
}

void print()
{
    struct errorlist *temp;
    temp = head;
    while(1)
    {
        if(temp == NULL)
        {
            break;
        }
        else
        {
            cout<<"Error in line number: "<<temp->data<<endl;
            temp = temp->next;
        }
    }
    delete(temp);
}


void pushfp(char x)
{
    struct node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;

    if(topfp==NULL)
    {
        topfp= newnode;
    }
    else
    {
        newnode->next = topfp;
        topfp=newnode;

    }

}

void popfp(int x)
{
    struct node *temp;
    if(topfp==NULL)
    {
        checklist(x);


    }
    else
    {
        temp = topfp;
        topfp=topfp->next;
        delete(temp);
    }

}

void pushsp(char x)
{
    struct node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;

    if(topsp==NULL)
    {
        topsp= newnode;
    }
    else
    {
        newnode->next = topsp;
        topsp=newnode;

    }

}

void popsp(int x)
{
    struct node *temp;
    if(topsp==NULL)
    {
        checklist(x);


    }
    else
    {
        temp = topsp;
        topsp=topsp->next;
        delete(temp);
    }

}


void pushtp(char x)
{
    struct node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;

    if(toptp==NULL)
    {
        toptp= newnode;
    }
    else
    {
        newnode->next = toptp;
        toptp=newnode;

    }

}

void poptp(int x)
{
    struct node *temp;
    if(toptp==NULL)
    {
        checklist(x);


    }
    else
    {
        temp = toptp;
        toptp=toptp->next;
        delete(temp);
    }

}



