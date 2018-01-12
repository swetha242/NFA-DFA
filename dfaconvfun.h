#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct node{
	char *binary;
	int *decimal;
	struct node * next;
};
void input();
void disp(char **tt,int states,int n);//REMOVE IN FINAL CODE
int transition(int s,int t,int e,char **tt,int n,int states);
void lam(int i,int j,char **tt,int n,int prod,int c);
void lmd(char **tt,int states,int n);
int dec_convert(char * bin, int * dec, int slots, int states);
void convert(char **tt1,int states,int n, int * final, int nfinal, int initial);
int disp1(struct node * h, int states, int n,  int * final, int nfinal, int lam, int initial);
void convert_lam(char **tt1,int states,int n, int * final, int nfinal, int initial);
