#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 65535
#define VERTEX 123

typedef struct
{
    float station;
    float distance;
    float time;
}Graph;

void dijkstra(Graph (*G)[VERTEX],int startnode,int endnode,int type,char path[VERTEX][30]);
void CreateGraph(Graph (*G)[VERTEX]);

int main()
{
    FILE *fp_name;
    int i,u,v,type;
    Graph G[VERTEX][VERTEX];
    char path[VERTEX][30],start[30],end[30];
    system("cls");
    system("color 80");
    //system("mspaint metro.jpg");
    
    printf("\n\n");
    printf("\t\t\t***************************************************************************\n");
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t*               Welcome to Chengdu Metro Inquiry System                   *\n");
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t*          Which route do you like:                                       *\n");
    printf("\t\t\t*                   1.The fewest stations                                 *\n");
    printf("\t\t\t*                   2.The shortest distance(The least cost)               *\n");
    printf("\t\t\t*                   3.The fastest time                                    *\n");
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t***************************************************************************\n");

    printf("Enter your choice:");
    scanf("%d",&type);

    CreateGraph(G);

    fp_name=fopen("chengdumetro_name.txt","r");
    for(i=0;i<VERTEX;i++)
        fscanf(fp_name,"%s",path[i]);

    printf("\nEnter the starting station:");
    scanf("%s",start);
    printf("\nEnter the ending station:");
    scanf("%s",end);
    for(i=0;i<VERTEX;i++)
    {
        if(strcmp(start,path[i])==0)
            u=i;
        if(strcmp(end,path[i])==0)
            v=i;
    }
    dijkstra(G,u,v,type,path);
    
    return 0;
}

void CreateGraph(Graph (*G)[VERTEX])
{
    FILE *fp_station,*fp_distance,*fp_time;
    int i,j;
    fp_station=fopen("chengdumetro_station.txt","r");
    fp_distance=fopen("chengdumetro_distance.txt","r");
    fp_time=fopen("chengdumetro_time.txt","r");
    for(i=0;i<VERTEX;i++)
    {
        for(j=0;j<VERTEX;j++)
        {
            fscanf(fp_station,"%f",&(*(G+i)+j)->station);
            fscanf(fp_distance,"%f",&(*(G+i)+j)->distance);
            fscanf(fp_time,"%f",&(*(G+i)+j)->time);
        }
    }
}
void dijkstra(Graph (*G)[VERTEX],int startnode,int endnode,int type,char path[VERTEX][30])
{
 
    int pred[VERTEX],price=0;
    float cost[VERTEX][VERTEX],expense[VERTEX],minexpense,total_distance=0,total_time=0;
    int visited[VERTEX],count,nextnode,i,j,number;
    char newpath[VERTEX][30];

    for(i=0;i<VERTEX;i++)
        for(j=0;j<VERTEX;j++)
            if((*(G+i)+j)->station==0)
                cost[i][j]=INFINITY;
            else
            {
                switch(type)
                {
                    case 1:cost[i][j]=(*(G+i)+j)->station;break;
                    case 2:cost[i][j]=(*(G+i)+j)->distance;break;
                    case 3:cost[i][j]=(*(G+i)+j)->time;break;
                }
            }

    for(i=0;i<VERTEX;i++)
    {
        expense[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    
    expense[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<VERTEX-1)
    {
        minexpense=INFINITY;

        for(i=0;i<VERTEX;i++)
            if(expense[i]<minexpense&&!visited[i])
            {
                minexpense=expense[i];
                nextnode=i;
            }
          
            visited[nextnode]=1;
            for(i=0;i<VERTEX;i++)
                if(!visited[i])
                    if(minexpense+cost[nextnode][i]<expense[i])
                    {
                        expense[i]=minexpense+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }

    for(i=0;i<VERTEX;i++)
        if(i==endnode)
        {
            strcpy(newpath[0],path[i]);
            number=1;
            j=i;

            do
            {
                total_distance+=(*(G+j)+pred[j])->distance;
                total_time+=(*(G+j)+pred[j])->time;
                j=pred[j];
                strcpy(newpath[number],path[j]);
                number++;
            }while(j!=startnode);
        }
    printf("\nPath=");
    for(i=number-1;i>0;i--)
        printf("%s->",newpath[i]);
    printf("%s\n\n",newpath[i]);
    printf("\t\t\t***************************************************************************\n");
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t*      total_stations      total_distance      total_time       fare      *\n");
    printf("\t\t\t*                                                                         *\n");    
    printf("\t\t\t*          %3d                %4.1f km           %3.0f min",number,total_distance,total_time);
    if(total_distance>70)
        price=(total_distance-70)/20+10;
    else if(total_distance>50)
        price=10;
    else if(total_distance>40)
        price=9;
    else if(total_distance>32)
        price=8;
    else if(total_distance>24)
        price=7;
    else if(total_distance>18)
        price=6;
    else if(total_distance>12)
        price=5;
    else if(total_distance>8)
        price=4;
    else if(total_distance>4)
        price=3;
    else
        price=2;
    printf("        %d yuan     *\n",price);
    printf("\t\t\t*                                                                         *\n");
    printf("\t\t\t***************************************************************************\n");
}
