



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






Stack * Stack_init(Stack * StackParams);
Stack * Stack_push(Stack * StackParams, BiTreeNode * a);
Stack * Stack_pop(Stack * StackParams);
BiTreeNode * Stack_top(Stack * StackParams);
int isStackEmpty(Stack * StackParams);
int isStackClean(Stack * StackParams);
BiTreeNode * tree_Init(BiTreeNode **root);
BiTreeNode * Search_binary_tree_create(BiTreeNode **root, char params);
void Search_binary_tree_order(BiTreeNode *root);
void Search_binary_tree_delete(BiTreeNode *node);
BiTreeNode *Search_binary_tree_node(BiTreeNode **root,char params);
BiTreeNode * tree_create(BiTreeNode **root, Stack * StackParms, char params);
void pre_order(const BiTreeNode *node);
void in_traverse(BiTreeNode *pTree);
void pre_order_unrecursion( BiTreeNode *node, Stack * StackParms);
BiTreeNode * tree_create_ext(BiTreeNode **root, Stack * StackParms, char params);
void tree_reversed_traversal(BiTreeNode *root, Stack * StackParms);