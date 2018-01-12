#include"dfaconvfun.h"
void input()
{
	int i,j,s,t,e,lambda=0,n,states, inputs, initial,nfinal,p;	
	scanf("%d",&states);
	scanf("%d",&inputs);
	scanf("%d",&initial);
	scanf("%d",&nfinal);
	int * fin;
	fin=(int *)malloc(sizeof(int)*nfinal);
	for (i=0; i< nfinal; i++)
		scanf("%d", &fin[i]);
	
	n=inputs+1;
	p=states*n;
	//p=pr/8+(!!(pr%8));
	char **tt=(char**)malloc(states*sizeof(char*));
	for(i=0;i<states;i++)
	{
		tt[i]=(char*)malloc(p*sizeof(int));
		for(j=0;j<p;j++)
			tt[i][j]='0';
	}
	scanf("%d",&s);
	scanf("%d",&t);
	scanf("%d",&e);
	while(s>=0)
	{
		
		int x=transition(s,t,e,tt,n,states);
		s=-1;
		if(x)
			lambda=1;
		scanf("%d",&s);
		scanf("%d",&t);
		scanf("%d",&e);
	}
	if(lambda==1)
	{
		lmd(tt,states,inputs);		
	}
	disp(tt,states,p);
	if(lambda==1)
		convert_lam(tt,states,n,fin,nfinal,initial);
	else 
		convert(tt,states,n,fin,nfinal,initial);
	free(tt);
}
void lmd(char **tt,int states,int n)
{
	int i,j,p;
	int prod=n*states;
	for(i=0;i<states;i++)
		{
			tt[i][states*n+i]='1';
		}
	
	for(i=0;i<states;i++)
		{
			for(j=0;j<states;j++)
			{
				if(i!=j && tt[i][prod+j]=='1')
					lam(i,j,tt,states,prod,0);
			}
		}
}
int transition(int s,int t,int e,char **tt,int n,int states)
{
	int j,i,prod,x=0;
	prod=(n-1)*states;
		if(t==-1)
		{
			j=prod+e;
			x=1;
		}
		else
			j=t*states+e;
		tt[s][j]='1';
		
	return x;
}	
	
void lam(int i,int j,char **tt,int n,int prod,int c)
{
		if(c==n)
			return ;
		int k;
		for(k=0;k<n;k++)
		{
			if(k!=j && tt[j][prod+k]=='1')
			{
				tt[i][prod+k]='1';
				lam(i,k,tt,n,prod,++c);				
			}
		}
	
}

void disp(char **tt,int states,int n)
{
	int i,j;
	printf("\n");
	for(i=0;i<states;i++)
	{
		for(j=0;j<n;j++)
			{
			printf("%c ",tt[i][j]);
			if(j%states==states-1)
				printf("|");
			}
		printf("\n");
	}
	
}
void convert(char **tt1,int states,int n, int * final, int nfinal, int initial)
{
	
	int i,j;
	struct node *head;
	head=NULL;
	int p;
	p=n*states;
	char * visited;
	visited=(char *)malloc(pow(2,states)*sizeof(char));
	memset(visited,'0',pow(2,states)*sizeof(char));
	int f; f=pow(2,(states-initial-1));
	visited[f]='1';
	int c;
	c=0;
	struct node *temp;
	temp=head;
	int key;
	//printf("%d \n", n);
	while(c<n)
	{
		struct node *transit;
		transit=(struct node *)malloc(sizeof(struct node *));
		char *temp1; 
		int *temp2;
		temp1=(char*)malloc((n+1)*states*sizeof(char));
		temp2=(int*)malloc((n+1)*sizeof(int));
	
		if(temp==NULL)
		{
			
			memset(temp1,'0',states*sizeof(char));
			temp1[initial]='1';
			strcpy((temp1+states),tt1[initial]);//
			printf("\n");
			for(i=0;i<(n+1)*states;i++)
				{printf("%c ",temp1[i]);
				if(i%states==states-1)
					printf("|"); 
				}
			dec_convert(temp1,temp2,n+1,states);
			transit->binary=temp1;
			transit->decimal=temp2;
			transit->next=NULL;
			head=transit;temp=transit;	

		}
		else 
		{
			key=temp->decimal[c];
			if((key!=0) && (visited[key]-'0')==0)
			{	visited[key]='1'; 	
				memset(temp1,'0',(n+1)*states*sizeof(char));
				for(i=states-1;i>=0;i--)//converting to binary
				{	temp1[i]=(key&1)+'0';
					key=key>>1;
				}
				for(i=0;i<states;i++)
				{
					if(temp1[i]=='1')
					{
						for(j=states;j<(states*n+1);j++)
						{
							temp1[j]=((tt1[i][j-states]-'0')|(temp1[j]-'0'))+'0';
						}
					}
				}
				printf("\n");
				for(i=0;i<(n+1)*states;i++)
				{printf("%c ",temp1[i]);
				if(i%states==states-1)
					printf("|"); 
				}
				dec_convert(temp1,temp2,n+1,states);
				transit->binary=temp1;
				transit->decimal=temp2;
				transit->next=NULL;
				struct node * tempo;
				tempo=head;
				while(tempo->next!=NULL)
				{ tempo=tempo->next;}
				tempo->next=transit;
			}
		}
		c++;
		if(c==n && temp->next!=NULL )
			{c=1;temp=temp->next;}
		
	}
	disp1(head,states,n,final, nfinal,0,initial);
		
	
}


int dec_convert(char * bin, int * dec, int slots, int states)
{
	int i,j,k;
	i=0;k=0;
	int sum;
	int p1=slots*states;
	while(i<p1)
	{
		sum=0;
		for(j=0;j<states;j++)
		{
			if(bin[i+j]=='1')
			{
				sum=sum+pow(2,states-j-1);//
			}
			
		}
		dec[k]=sum; k++; i=i+states;
	}
}

int disp1(struct node * h, int states, int n, int *final, int nfinal, int lam, int initial)
{
	int i=0;
	int j,k=0;
	int key;
	struct node * temp;
	temp=h;
	int list[20];
	
	while(temp!=NULL)
	{
		printf("\n%d  %d  %d", temp->decimal[0], i, temp->decimal[i+1]);
		i++; 
		if(i==n-1)
			{i=0;
			  j=0;
			 key=temp->decimal[0];
			  while(j<nfinal && (key&(int)(pow(2,states-final[j]-1)))==0)
				j++;
			  if(j!=nfinal)
				list[k++]=key;
			temp=temp->next;
			}
		
	}
	printf("\nThe initial state is\n");
	
	printf("%d",(int)h->decimal[0]);
	printf("\nThe final states are\n");
	for(j=0;j<k;j++)
		printf("%d  ",list[j]);
}
void convert_lam(char **tt1,int states,int n, int *final ,int nfinal, int initial)
{
	int i,j,k,k1;
	struct node *head;
	head=NULL;
	int p;
	p=(n-1)*states;
	char * visited;
	visited=(char *)malloc(pow(2,states)*sizeof(char));
	memset(visited,'0',pow(2,states)*sizeof(char));
	int c;
	c=0;
	struct node *temp;
	temp=head;
	int key;
	//printf("%d \n", n);
	while(c<n)
	{
		struct node *transit;
		transit=(struct node *)malloc(sizeof(struct node *));
		char *temp1; 
		int *temp2;
		temp1=(char*)malloc((n+1)*states*sizeof(char));
		temp2=(int*)malloc((n+1)*sizeof(int));
	
		if(temp==NULL)
		{
		  memset(temp1,'0',(n)*states*sizeof(char));
	          for(i=0;i<states;i++)
		   {

		     temp1[i]=tt1[initial][p+i];
		     if(temp1[i]=='1')
			{
				for(j=0;j<n-1;j++)				
				   {	for(k=0;k<states;k++)
					      {
								//temp1[j*states+k]=(temp1[j*states+k]-'0')|(tt1[i][p+k]-'0')+'0';
						 if(tt1[i][j*states+k]=='1')
						   {

						     for(int k1=0;k1<states;k1++)
							{temp1[(j+1)*states+k1]=(temp1[(j+1)*states+k1]-'0')|(tt1[k][p+k1]-'0')+'0';}
						    }
					       }
				   }
			}

		   }
			printf("\n");
			for(i=0;i<(n)*states;i++)
				{printf("%c ",temp1[i]);
				if(i%states==states-1)
					printf("|"); 
				}
			dec_convert(temp1,temp2,n+1,states);
			transit->binary=temp1;
			transit->decimal=temp2;
			transit->next=NULL;
			head=transit;temp=transit;	
			int f; 
			f=transit->decimal[0];
			visited[f]='1';

		}
		else 
		{
			key=temp->decimal[c];
			if((key!=0) && (visited[key]-'0')==0)
			{visited[key]='1'; 	
			memset(temp1,'0',(n+1)*states*sizeof(char));
			for(i=states-1;i>=0;i--)//converting to binary
			{	temp1[i]=(key&1)+'0';
				key=key>>1;
			}
			for(i=0;i<states;i++)
			{
		           if(temp1[i]=='1')
				{
				  for(j=0;j<n-1;j++)				
					 {   for(k=0;k<states;k++)
					      {
						if(tt1[i][j*states+k]=='1')
						  {

						    for(int k1=0;k1<states;k1++)
							{temp1[(j+1)*states+k1]=(temp1[(j+1)*states+k1]-'0')|(tt1[k][p+k1]-'0')+'0';}
							}
						  }
					      }
				          }
				}
				printf("\n");
				for(i=0;i<(n)*states;i++)
				{printf("%c ",temp1[i]);
				if(i%states==states-1)
					printf("|"); 
				}
				dec_convert(temp1,temp2,n+1,states);
				transit->binary=temp1;
				transit->decimal=temp2;
				transit->next=NULL;
				struct node * tempo;
				tempo=head;
				while(tempo->next!=NULL)
				{ tempo=tempo->next;}
				tempo->next=transit;
			}
		}
		c++;
		if(c==n && temp->next!=NULL )
			{c=1;temp=temp->next;}
		
	}
	disp1(head,states,n,final,nfinal,1, initial);
	
}

