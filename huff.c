#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct node_tree
{
  char c;
  int val;
  struct node_tree *left;
  struct node_tree *right;
}Node;
Node* createNode(char, int);
int count(char*, Node*[]);
Node* buildtree(Node*[], int);
int printtree(Node*, int, int[], FILE* );




int main(int argc, char * * argv)
{
  Node* array = malloc(1000*sizeof(Node));
  Node* tree;
  int n;
  int* intarray = malloc(1000*sizeof(int));
  char *filename = argv[1]; //input file name
  n = count(filename, &array);
  tree = buildtree(&array, n);
  char *outfile = argv[1];
  strcat(outfile,".huff");
  FILE* out = fopen(outfile,"w+");
  intarray[0] = 2;
  printtree(tree, 0, intarray, out);
  fclose(out);

  return 0;
}

Node* createNode(char c, int value)
{
  Node *retnode=malloc(sizeof(Node));
  retnode->c = (char)c;
  retnode->val = value;
  retnode->left = NULL;
  retnode->right = NULL;
  return retnode;
}

int count(char* filename, Node* array[])
{
  char a;
  int i = 0;
  int y = 0;
  int n = 0;
  FILE *fptr = fopen(filename,"r");
  a = fgetc(fptr);
  if(n == 0)
    {
      array[n] = createNode(a, 1);
    }
  else
    {
      while(a != EOF)
	{
	  a = fgetc(fptr);
	  i = 0;
	  y = n;
	  while(i <= n)
	    {
	      if(array[i]->c == a)
		{
		  array[i]->val = array[i]->val +1;
		}
	      else
		{
		  y++;
		  array[y] = createNode(a, 1);
		}
	      i++;
	    }
	  n = y;
	}
    }
  fclose(fptr);
  return n;
}

Node* buildtree(Node* array[], int n)
{
  Node* tree;
  Node* temp;
  Node* New;
  int val;
  char c;
  if(n == 0);
  {
    tree = array[0];
    return tree;
  }
  for(int i = 0; i < 2; i++)
    {
      for(int y = 1; y <= n; y++)
	{
	  if(array[y]->val > array[y-1]->val)
	    {
	      temp = array[y];
	      array[y] = array[y-1];
	      array[y-1] = temp;
	    }
	}
    }
  if(array[n]->val == array[n-1]->val)
    {
      array[n-1]->val = array[n-1]->val +1;
      n--;
    }
  else
    {
      val = array[n]->val + array[n-1]->val;
      New = createNode(c, val);
      New->left = array[n];
      New->right = array[n-1];
      array[n-1] = New;
      n--;
    } 
  tree = buildtree(array, n);
  return tree;
}

int printtree(Node* tree, int n, int array[], FILE* out)
{
  int a;
  char b;
  if(tree->left == NULL && tree->right == NULL)
    {
      if(array[0] == 2)
	{
	  b = tree->c;
	  fprintf(out, "%c ", b);
	  return 1;
	}
      else
	{
	  for(int i = 1; i <= n; i++)
	    {
	      fprintf(out, "%d",array[n]);
	    }
	  fprintf(out, "%c ", tree->c);
	  return 1;
	}
    }
  else
    {
      array[n] = 0;
      a = printtree(tree->left, n++, array, out);
      if(a == 1)
	{
	  array[n] = 1;
	  printtree(tree->right, n++, array, out);
	}
    }
  return 1;
}
