
/*  名 称: 建立二叉树(非递归)
*  作 者: lyndon
*  时 间: 2016/11/15
*
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 #include <unistd.h>
#define STACKSIZE 50
#define bitree_size(tree)  ((tree)->size)
#define bitree_root(tree)  ((tree)->root)
#define bitree_left(node)  ((node)->left)
#define bitree_right(node) ((node)->right)

char *treeStruct = "GDA00FE000MH00Z00";
static int flag_tree = 0; //0 初始值 ，1 左子树 ，2 右子树


typedef struct Bitree_
{
    char str;
    struct Bitree_ *left;
    struct Bitree_ *right;

}BiTreeNode;


typedef struct Stack_
{
    BiTreeNode *node[40];
    int s_top;
    int stack_size;
}Stack;


Stack * Stack_init(Stack * StackParams)
{
//    memset(StackParams->str, 0x0, sizeof(StackParams->str));
    StackParams->s_top = -1;
    StackParams->stack_size = 0;
    return StackParams;
}

Stack * Stack_push(Stack * StackParams, BiTreeNode * a)
{
    StackParams->node[++StackParams->s_top] = a;
    StackParams->stack_size++;
    return StackParams;
}

Stack * Stack_pop(Stack * StackParams)
{
    StackParams->s_top--;
    StackParams->stack_size--;
    return StackParams;
}

BiTreeNode * Stack_top(Stack * StackParams)
{
    return StackParams->node[StackParams->s_top];
}

//如果为空 返回1 非空返回 0
int isStackEmpty(Stack * StackParams)
{
    if(StackParams->stack_size == 0)
        return 1;
    else
        return 0;
}

//如果为空 返回1 非空返回 0
int isStackClean(Stack * StackParams)
{
    StackParams->s_top = -1;
    StackParams->stack_size = 0;
    return 0;
}

BiTreeNode * tree_Init(BiTreeNode **root)
{
    (*root) = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    (*root)->str = 0;
    (*root)->left = NULL;
    (*root)->right = NULL;
    return *root;
}

//非递归创建二叉树



// in 10, 20, 15, 3, 4, 23, 21, 12, 90

BiTreeNode * Search_binary_tree_create(BiTreeNode **root, char params)
{

    char tree_son_flag = -1; // 1 标示左子树 2 标示右子树

    if (0 == (*root)->str) {
        (*root)->str = params;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return *root;
    }

    BiTreeNode *tree_cursor = *root;
    BiTreeNode *tree_cursor_parent = tree_cursor;
    BiTreeNode *new = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    new->str = params;
    new->left = NULL;
    new->right = NULL;

    while(1){


        if (NULL == tree_cursor){
            switch(tree_son_flag){
                case 1:
                    tree_cursor_parent->left = new;
                    break;
                case 2:
                    tree_cursor_parent->right = new;
                    break;
                default:
                    break;
            }
            return *root;
        }

        tree_cursor_parent = tree_cursor;
        if(tree_cursor->str >= params) {     
            tree_son_flag = 1;    
            tree_cursor = tree_cursor->left;
        }else if(tree_cursor->str < params){      
            tree_son_flag = 2;      
            tree_cursor = tree_cursor->right;
        }



    }
    
   
    
    return *root;


}


 void Search_binary_tree_order(BiTreeNode *root)
 {
    if (root){
        Search_binary_tree_order(root->left);
        printf("%d-", root->str);   
        Search_binary_tree_order(root->right);
    }
 }


void Search_binary_tree_delete(BiTreeNode *node)
{

}

BiTreeNode *Search_binary_tree_node(BiTreeNode **root,char params)
{


    BiTreeNode * cursor = root;
    if (cursor->str == params)
            return *root;


    while(NULL != cursor && cursor->str != params){
        if (cursor->str < params){
           cursor = cursor->right;
        }else if(cursor->str >= params){
           cursor = cursor->left;
        }
    }
    return cursor;
}


BiTreeNode * tree_create(BiTreeNode **root, Stack * StackParms, char params)
{
    
    BiTreeNode *Treenode = NULL;
    BiTreeNode *position = NULL;
//    BiTreeNode *tempTreeNode_ = NULL;
//    
//    tempTreeNode_ = (*root)->left;
    
    //创建根节点
    if (*root != NULL && isStackEmpty(StackParms)) {
        (*root)->str = params;
        (*root)->left = NULL;
        (*root)->right = NULL;
        //根节点压栈
        Stack_push(StackParms, *root);
        flag_tree = 1;
        return *root;
    }
    if(!isStackEmpty(StackParms)) {

        
        position = Stack_top(StackParms);
        if (params == '0') {
            if(NULL == (position)->left && 1 == flag_tree){
                flag_tree = 2;
            }
            else if(2 == flag_tree){
                Stack_pop(StackParms);
            }
            
        }
        else{
            BiTreeNode *new = (BiTreeNode *)malloc(sizeof(BiTreeNode));
            new->str = params;
            new->left = NULL;
            new->right = NULL;

            
            if(flag_tree == 1){
                position = Stack_top(StackParms);
                position->left = new;
                Stack_push(StackParms, position->left);
            }
            else if(flag_tree == 2){
                position = Stack_top(StackParms);
                
                position->right = new;
                Stack_pop(StackParms);
                Stack_push(StackParms, position->right);
                flag_tree = 1;
            }
        }
    }
  
    
    return *root;
}


// 先序遍历函数
void pre_order(const BiTreeNode *node)
{
    if(node)
    {
        
        pre_order(node->left);
        pre_order(node->right);
        printf("%c-",node->str);
    }
}

void in_traverse(BiTreeNode *pTree)  
{  
    if(pTree)  
    {  
        if(pTree->left)  
            in_traverse(pTree->left);  
        printf("%c-",pTree->str);  
        if(pTree->right)  
            in_traverse(pTree->right);   
    }  
}


void pre_order_unrecursion( BiTreeNode *node, Stack * StackParms)
{
    BiTreeNode *tempnode = NULL;

    if (!node) {
        return;
    }
    Stack_push(StackParms, node);
    printf("-%c-",node->str);
    flag_tree = 1;
    
    while(!isStackEmpty(StackParms)){
        tempnode = Stack_top(StackParms);
        if (tempnode->left != NULL&&  1 == flag_tree) {
            printf("-%c-",tempnode->left->str);
            Stack_push(StackParms, tempnode->left);
            flag_tree = 1;
        }else if(tempnode->left == NULL && 1 == flag_tree ){
            flag_tree = 2;

        }else if(tempnode->right != NULL && 2 == flag_tree){
            
            printf("-%c-",tempnode->right->str);
            Stack_pop(StackParms);
            Stack_push(StackParms, tempnode->right);
            flag_tree = 1;
        }else if(tempnode->right == NULL && 2 == flag_tree ){
            Stack_pop(StackParms);

        }
    }
}



static char flag = 1; //1 标示左子树 2标示右子树 3 标示满了

BiTreeNode * tree_create_ext(BiTreeNode **root, Stack * StackParms, char params)
{

	
	BiTreeNode *position = NULL;
	
	
    	
     if (*root != NULL && isStackEmpty(StackParms)) {
        (*root)->str = params;
        (*root)->left = NULL;
        (*root)->right = NULL;
        //根节点压栈
        Stack_push(StackParms, *root);
       // flag_tree = 1;
       position = Stack_top(StackParms);
        printf("position->str %c flag %d -- params %c\n", position->str, flag, params);
        flag = 1 ;
        return *root;
    }
  


	
   

    if (!isStackEmpty(StackParms))
    {
    	


    	if ( '0' != params)
    	{

    		position = Stack_top(StackParms);
    		
    		

    		BiTreeNode *new = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		    new->str = params;
		    new->left = NULL;
		    new->right = NULL;


    		if (NULL == position->left && 1 == flag)
	    	{
	    		position = Stack_top(StackParms);
                position->left = new;
                Stack_push(StackParms, position->left);   		
	    		
	    		printf("position->str %c flag %d -- params %c\n", position->str, flag, params);
	    		flag = 1;
	    	}else if (2 == flag){
	    		
	    		
	    			position = Stack_top(StackParms);
	    		if (NULL != position->right){
	    			while(NULL != position->right){
	    				printf(" while position->str %c flag %d -- params %c\n", position->str, flag, params);
	    				Stack_pop(StackParms);
	    				position = Stack_top(StackParms);
	    				
	    			}
	    			
	    		}
    			position = Stack_top(StackParms);
    				printf("position->str %c flag %d -- params %c\n", position->str, flag, params);
    			position->right = new;
	    		Stack_push(StackParms, position->right); 
	    		position = Stack_top(StackParms);
    		
	    		flag = 1;
	    		    		
	    				
	    	
	    	}
    	}else{
    		
    			position = Stack_top(StackParms);
    			if (NULL == position->left &&1 == flag) {
    				 
    				printf("position->str %c flag %d -- params %c\n", position->str, flag, params);
    				flag = 2;
    				return *root;
    			}
    			else if (2 == flag){
    				Stack_pop(StackParms);
    				
    				printf("position->str %c flag %d -- params %c\n", position->str, flag, params);
    				return *root;
    			}
    			


    	}
    	
    	

    }




   	return *root;
}


void tree_reversed_traversal(BiTreeNode *root, Stack * StackParms)
{

    BiTreeNode *tempnode = NULL;
    BiTreeNode *cachenode = NULL;


   
   if (root)
        Stack_push(StackParms, root);
    else 
        return;

    while(!isStackEmpty(StackParms)){

        tempnode = Stack_top(StackParms);

        if (NULL != tempnode->left && 1 == flag) {
            
           Stack_push(StackParms, tempnode->left);
           cachenode =  NULL;
           flag = 1;
        }else{
          

            flag = 2;
            tempnode = Stack_top(StackParms);
            
            if (NULL != tempnode->right && 2 == flag){
               
                 Stack_push(StackParms, tempnode->right);
                 cachenode = NULL;
                 flag = 1;
                
            }
            else{
               
                cachenode = tempnode = Stack_top(StackParms);
                printf("%c ", tempnode->str);
                Stack_pop(StackParms);           
                tempnode = Stack_top(StackParms);
                while (NULL != tempnode->right && cachenode->str == tempnode->right->str) {

                    cachenode = tempnode;
                     printf("%c ", tempnode->str);
                     
                     Stack_pop(StackParms);
                     tempnode = Stack_top(StackParms);
                    
                }
                cachenode = NULL;
                 flag = 2;

            }

           
        }

    }




    return;
}



void circle_print()
{
    int i = 0,j = 0;
    int radius = 4;

    for (i = 0; i <= radius; ++i)
    {
       
    }

}

int main(void)
{
    BiTreeNode *treeRoot;
    Stack varStack;
    //init
    Stack_init(&varStack);
    tree_Init(&treeRoot);
    
    //tree creat
    // tree_create_ext(&treeRoot, &varStack,'G');
    // tree_create_ext(&treeRoot, &varStack,'D');
    // tree_create_ext(&treeRoot, &varStack,'A');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'F');
    // tree_create_ext(&treeRoot, &varStack,'E');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'M');
    // tree_create_ext(&treeRoot, &varStack,'H');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'Z');
    // tree_create_ext(&treeRoot, &varStack,'0');
    // tree_create_ext(&treeRoot, &varStack,'0');
    
    


    // tree_create(&treeRoot, &varStack,'G');
    // tree_create(&treeRoot, &varStack,'D');
    // tree_create(&treeRoot, &varStack,'A');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'F');
    // tree_create(&treeRoot, &varStack,'E');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'M');
    // tree_create(&treeRoot, &varStack,'H');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'Z');
    // tree_create(&treeRoot, &varStack,'0');
    // tree_create(&treeRoot, &varStack,'0');
    

    // flag_tree = 0;
    // pre_order(treeRoot);
    // printf("\n");
    // //in_traverse(treeRoot);

    // printf("\n-------------------tree_reversed_traversal----------------\n");
    // flag = 1;
    // //isStackClean(&varStack);
    // tree_reversed_traversal(treeRoot, &varStack);
    // printf("\n-------------------tree_reversed_traversal----------------\n");


   // tree_reversed_traversal(treeRoot, &varStack);
    // printf("\n-------------------pre_order_unrecursion----------------\n");
    // flag = 1;
    // isStackClean(&varStack);
    // pre_order_unrecursion(treeRoot, &varStack);
    //  printf("\n-------------------pre_order_unrecursion----------------\n");


    //-----------------------BST------------------------------------

    // in 10, 20, 15, 3, 4, 23, 21, 12, 90

    Search_binary_tree_create(&treeRoot, 10);
    Search_binary_tree_create(&treeRoot,20);
    Search_binary_tree_create(&treeRoot,15);
    Search_binary_tree_create(&treeRoot, 3);
    Search_binary_tree_create(&treeRoot, 4);
    Search_binary_tree_create(&treeRoot,23);
    Search_binary_tree_create(&treeRoot, 21);
    Search_binary_tree_create(&treeRoot, 12);
    Search_binary_tree_create(&treeRoot, 90);
    
    
    Search_binary_tree_order(treeRoot);









    return 0;
}
