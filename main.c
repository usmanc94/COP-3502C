/*  Usman Chaudhry
    COP-3502C
    Programming Assignment 4
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// An AVL tree node
struct Node
{
    int priority;
   char taskName[20];
    struct Node *left;
    struct Node *right;
    int height;
};

// Returns height of the tree at node N.
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Returns maximum of two numbers
int max(int a, int b)
{
    return (a > b)? a : b;
}

// Helper function that allocates a new node with the given key and NULL left and right pointers.
struct Node* newNode(int priority, char *tname)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
   strcpy(node->taskName, tname);
    node->priority = priority;
    node->left   = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return(node);
}

// Function to right rotate subtree rooted with y
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Returns the balance
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert task with priority.
// Returns the new root of the subtree.
struct Node* insert(struct Node* node, char *tname, int prio, int *status)
{
    // Normal BST insertion */
    if (node == NULL) {
       *status = 1;
        return(newNode(prio, tname));
   }

    if (prio < node->priority)
        node->left = insert(node->left, tname, prio, status);
    else if (prio > node->priority)
        node->right = insert(node->right, tname, prio, status);
    else { // Tasks with equal priorities. (redundant)
       *status = 0;
        return node;
   }

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && prio < node->left->priority)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && prio > node->right->priority)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && prio > node->left->priority)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && prio < node->right->priority)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}

struct Node* query(struct Node *root, int prio) {

   // if we have reached leaf or the required node.
   if(root == NULL ||root->priority == prio) {
       return root;
   }

   // priority is less so go left.
   if(root->priority > prio) {
       return query(root->left, prio);
   }

   // priority is high so go right.
   return query(root->right, prio);
}
// Drier program to test above function
int main()
{
   struct Node *root = NULL, *found = NULL;

   int t,prio, op,status;
   char tname[20];

   scanf("%d",&t);
   while(t--) {
       status = 1;
       scanf("%d", &op);
       if(op == 1) {
           scanf("%s%d", tname, &prio);
           root = insert(root, tname, prio, &status);
           if(status == 0)
               printf("REDUNDANT\n");
           else
               printf("ADDED\n");
       }
       else if(op == 2) {
           scanf("%d", &prio);
           found = query(root,prio);
           if(found == NULL) {
               printf("NON-EXISTANT\n");
           }
           else{
               printf("%s\n",found->taskName);
           }
       }
   }

   return 0;
}
