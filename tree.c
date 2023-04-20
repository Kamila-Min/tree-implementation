#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <string.h>
#include <malloc.h>


typedef int Data;

typedef struct Node Node;
struct Node 
{
    Data val;      
    Node * left;    
    Node * right;   
};

Node *tree_add (Node * tree, Data x);

void tree_print_direct (Node * tree);

void tree_print_symmetric (Node * tree);

void tree_print_back(Node * tree);

Node *insert_node (Node * tree, Data y);

Node *delete_node (Node * tree, Data z);

Node * min_node(Node * tree);

Node * tree_destroy (Node ** tree);

int height_tree (Node * tree);

int main ()
{
    Node * tree = NULL; 

    Data x = 0;

    int q = 0;

    int k = 0;

    while (k != 1)
    {
        printf ("Please, choose one of this actions and enter the appropriate number:\n");
        printf ("1. Creating the binary tree\n");
        printf ("2. Travesal and printing of binary tree\n");
        printf ("3. Inserting a node into a binary tree\n");
        printf ("4. Deleting a node from a binary tree\n");
        printf ("5. Checking the emptiness of the binary tree\n");
        printf ("6. Deleting the binary tree\n");
        printf ("7. Determining the depth of the binary tree\n");

        scanf ("%d", &q);
        
        switch (q)
        {
            case 1:
             {
                 printf ("Creating the binary tree:\n");
                 int i = 0;

                while (i != 1)
                {
                 printf ("Write the vertex value\n");
        
                 scanf ("%d", &x);
        
                 printf ("x = %d \n", x);
   
                 tree = tree_add (tree, x);

                 printf ("Is it the end? If yes write 1, else - enter 0\n");

                 scanf("%d", &i);
                }
             }
             break;

            case 2:
            {
                printf ("Travesal and printing of binary tree:\n");
                printf ("Forward traversal: \n");
                tree_print_direct (tree);
                printf ("\n");

                printf ("Symmetric travesal:\n");
                tree_print_symmetric (tree);
                printf ("\n");

                printf ("Inverse travesal:\n");
                tree_print_back (tree);
                printf ("\n");
            }
            break;

            case 3:
            {
                printf ("Inserting a node into a binary tree:\n");

                printf ("Enter the new node's value\n");

                Data y = 0;
                scanf ("%d", &y);

                printf ("Inserting the node - %d\n", y);

                tree = insert_node (tree, y);
            }
            break;

            case 4:
            {
                printf ("Deleting a node from a binary tree\n");

                printf ("Enter the node's value, which must be deleted\n");

                Data z = 0;
                scanf ("%d", &z);

                printf ("Deleting the node - %d\n", z);

                tree = delete_node (tree, z);
            } 
            break;

            case 5:
            {
                printf ("Checking the emptiness of the binary tree\n");
                
                if (tree == NULL)
                 printf ("The tree is empty\n");
                
                if (tree != NULL)
                 printf ("The tree is not empty\n");

                else printf ("ERROR");
            }   
            break;

            case 6:
            {
                printf ("Deleting the binary tree\n");

                tree_destroy (&tree);
            }
            break;

            case 7:
            {
                printf ("Determining the depth of the binary tree\n");

                int h = height_tree (tree);

                printf ("The height of tree is %d \n", h);
            }
            break;
        }

        printf ("If you want to continue, enter 0, else - enter 1\n");

        scanf ("%d", &k);
    }

    return 0;
}

Node *tree_add (Node * tree, Data x)
{
    if (tree == NULL) 
    {
      tree = (Node *) malloc(sizeof(Node));
	  tree->val = x;
	  tree->left = NULL;
	  tree->right = NULL;
    } 
    else if (x < tree->val) 
    {
	  tree->left = tree_add(tree->left, x);
    }

    else if (x > tree->val) 
    {
    	tree->right = tree_add(tree->right, x);
    }

    return tree;

}

void tree_print_direct (Node * tree)
{
     if (tree == NULL)
	return;
    
    printf("%d  ", tree->val);
    tree_print_direct(tree->left);
    tree_print_direct(tree->right);
}

void tree_print_symmetric(Node * tree)
{
    if (tree == NULL)
	return;

    tree_print_symmetric(tree->left);
    printf("%d  ", tree->val);
    
    tree_print_symmetric(tree->right);
}

void tree_print_back (Node * tree)
{
    if (tree == NULL)
	return;
    tree_print_back(tree->left);
    tree_print_back(tree->right);
    printf("%d  ", tree->val);
}

Node *insert_node (Node * tree, Data y)
{
    if (tree == NULL) 
    {
      tree = (Node *) malloc(sizeof(Node));
	  tree->val = y;
	  tree->left = NULL;
	  tree->right = NULL;
    } 
    else if (y < tree->val) 
    {
	  tree->left = tree_add(tree->left, y);
    }

    else if (y > tree->val) 
    {
    	tree->right = tree_add(tree->right, y);
    }

    return tree;

}

Node *delete_node (Node * tree, Data z)
{
    Node * temp_node = NULL;
    
    if (tree == NULL)
     return tree;
    
    if (z < tree->val)
     tree->left = delete_node (tree->left, z);

    else if (z > tree->val)
     tree->right = delete_node (tree->right, z);

    else
    {
        temp_node = (struct Node *)malloc(sizeof(struct Node));
    
        if (tree->left == NULL)
         {
            Node *temp_node = tree->right;
            free (tree);

            return temp_node;
         }   
        else
         {
            if (tree->right == NULL)
            Node *temp_node = tree->left;

            free (tree);

            return temp_node;
         }  
    
        Node *temp_node = min_node (tree->right);
        tree->val = temp_node->val;
        tree->right = delete_node (tree->right, temp_node->val);
    }
    
    return tree;
}

Node * min_node(Node * tree)
{
    Node* temp = tree;

    while (temp && temp->left != NULL)

        temp = temp->left;

    return temp;
}


int height_tree (Node * tree)
{
    int left = 0, right = 0;
    
    if (tree == NULL)
	 return 0;
    
    left = height_tree (tree->left);
    
    right = height_tree (tree->right);
    
    if (left > right) 
     return (left+1); 
    
    else 
     return (right+1);
}

void tree_destroy (Node * tree) 
{
  if (tree != NULL) 
    {
      tree_destroy (tree->left);
      tree_destroy (tree->right);
      free(tree);
    } 
}
