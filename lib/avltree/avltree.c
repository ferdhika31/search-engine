/*
	Program 		: avltree.c
	Deskripsi 		: ADT AVL Tree
	Author 			: Zentut edited by Ferdhika
	Tanggal/Version : 21/06/2016 v.1.0
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: adt from www.zentut.com
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"avltree.h"
/*
    remove all AVLs of an AVL tree
*/
void dispose(AVL* t)
{
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        free( t );
    }
}
 
/*
    find a specific AVL's key in the tree
*/
AVL* find(char *e, AVL* t )
{
    if( t == NULL )
        return NULL;
    if( strcmp(e,t->data) < 0 )
        return find( e, t->left );
    else if( strcmp(e,t->data) > 0 )
        return find( e, t->right );
    else
        return t;
}
 
/*
    find minimum AVL's key
*/
AVL* find_min( AVL* t )
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
 
/*
    find maximum AVL's key
*/
AVL* find_max( AVL* t )
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
 
    return t;
}
 
/*
    get the height of a AVL
*/
static int height( AVL* n )
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}
 
/*
    get maximum value of two integers
*/
static int max( int l, int r)
{
    return l > r ? l: r;
}
 
/*
    perform a rotation between a k2 AVL and its left child
 
    note: call single_rotate_with_left only if k2 AVL has a left child
*/
 
static AVL* single_rotate_with_left( AVL* k2 )
{
    AVL* k1 = NULL;
 
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
 
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}
 
/*
    perform a rotation between a AVL (k1) and its right child
 
    note: call single_rotate_with_right only if
    the k1 AVL has a right child
*/
 
static AVL* single_rotate_with_right( AVL* k1 )
{
    AVL* k2;
 
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
 
    return k2;  /* New root */
}
 
/*
 
    perform the left-right double rotation,
 
    note: call double_rotate_with_left only if k3 AVL has
    a left child and k3's left child has a right child
*/
 
static AVL* double_rotate_with_left( AVL* k3 )
{
    /* Rotate between k1 and k2 */
    k3->left = single_rotate_with_right( k3->left );
 
    /* Rotate between K3 and k2 */
    return single_rotate_with_left( k3 );
}
 
/*
    perform the right-left double rotation
 
   notes: call double_rotate_with_right only if k1 has a
   right child and k1's right child has a left child
*/
 
 
 
static AVL* double_rotate_with_right( AVL* k1 )
{
    /* rotate between K3 and k2 */
    k1->right = single_rotate_with_left( k1->right );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_right( k1 );
}
 
/*
    insert a new AVL into the tree
*/
AVL* insertAVL(char *e, AVL* t )
{
    if( t == NULL )
    {
        /* Create and return a one-AVL tree */
        t = (AVL*)malloc(sizeof(AVL));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else
        {
            strcpy(t->data, e);
            t->height = 0;
            t->left = t->right = NULL;
            t->count = 1;
        }
    }
    else if( strcmp(e,t->data) < 0 )
    {
        t->left = insertAVL( e, t->left );
        if( height( t->left ) - height( t->right ) == 2 )
            if( strcmp(e,t->left->data) < 0 )
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
    }
    else if( strcmp(e,t->data) > 0 )
    {
        t->right = insertAVL( e, t->right );
        if( height( t->right ) - height( t->left ) == 2 )
            if( strcmp(e,t->right->data) > 0 )
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
    }
    /* Else X is in the tree already; we'll do nothing */
    else{
    	t->count++;
    }
 
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}
 
/*
    remove a AVL in the tree
*/
AVL* delete( char *e, AVL* t )
{
    printf( "Sorry; Delete is unimplemented; %d remains\n", e );
    return t;
}
 
/*
    data data of a AVL
*/
char* get(AVL* n)
{
    return n->data;
}

/*
	menampilkan jumlah kata 
*/
int* countKata(AVL* n){
	return n->count;
}
 
/*
    Recursively display AVL tree or subtree
*/
void display_avl(AVL* t)
{
    if (t == NULL)
        return;
    printf("%s (%d)",t->data,t->count);
 
    if(t->left != NULL)
        printf("(L:%s)",t->left->data);
    if(t->right != NULL)
        printf("(R:%s)",t->right->data);
    printf("\n");
 
    display_avl(t->left);
    display_avl(t->right);
}
