/*
    建立以左右孩子链接结构表示的二叉树，实现二叉树的先序、中序、后序的递归和非递归方式遍历，分层遍历、统计树的高度。
    扩展问题：
    给定一组关键字序列，建立一个平衡二叉树。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree {
    char data;
    struct binary_tree *lson;
    struct binary_tree *rson;
} btree;

//以带#的先序遍历构建二叉树
char *btree_create(btree *root, char *s)
{
    root->data = *(s++);
    printf("%c\n", root->data);
    if (root->data != '#')
    {
        btree *templ = (btree *)malloc(sizeof(btree));
        btree *tempr = (btree *)malloc(sizeof(btree));
        printf("创建%c的左子树:", root->data);
        s = btree_create(templ, s);
        if (templ->data != '#')
            root->lson = templ;
        else
            root->lson = NULL;
        printf("创建%c的右子树:", root->data);
        s = btree_create(tempr, s);
        if (tempr->data != '#')
            root->rson = tempr;
        else
            root->rson = NULL;
    }
    else if (*s == '\0')
        return 0;
    return s;
}

void preorder_traversal(btree *root, FILE *fp)
{
    if (root != NULL)
    {
        fprintf(fp, "%c", root->data);
        preorder_traversal(root->lson, fp);
        preorder_traversal(root->rson, fp);
    }
    return;
}

void inorder_traversal(btree *root, FILE *fp)
{
    if (root != NULL)
    {
        inorder_traversal(root->lson, fp);
        fprintf(fp, "%c", root->data);
        inorder_traversal(root->rson, fp);
    }
    return;
}

void postorder_traversal(btree *root, FILE *fp)
{
    if (root != NULL)
    {
        postorder_traversal(root->lson, fp);
        postorder_traversal(root->rson, fp);
        fprintf(fp, "%c", root->data);
    }
    return;
}

void *preorder_traversal_2(btree *root, FILE *fp)
{
    if (root == NULL)
        return;
    btree *stack[50], *queue[50], *p = NULL;
    int top = -1, tail = -1;
    stack[++top] = root; //根节点入栈
    do
    {
        queue[++tail] = p = stack[top--]; //取出栈顶节点入队列
        if (p->rson != NULL)
            stack[++top] = p->rson; //栈顶节点的右子树节点入栈
        if (p->lson != NULL)
            stack[++top] = p->lson; //栈顶节点的左子树节点入栈
    } while (top > -1);             //循环直到栈空
    //output
    fprintf(fp, "先序（非递归)\t");
    for (int i = 0; i <= tail; i++)
    {
        fprintf(fp, "%c", queue[i]->data);
    }
    fprintf(fp, "\n");
}

void *inorder_traversal_2(btree *root, FILE *fp)
{
    if (root == NULL)
        return;
    btree *stack[50], *queue[50], *p = root;
    int top = -1, tail = -1;
    do
    {
        while (p != NULL)
        {
            stack[++top] = p;
            p = p->lson;
        }                                 //p指针寻找最左端的节点
        queue[++tail] = p = stack[top--]; //栈顶节点出栈，根节点入队列
        p = p->rson;                      //p指针进入右子树
    } while (p != NULL || top > -1);      //循环直到p不为空且栈空
    //output
    fprintf(fp, "中序（非递归)\t");
    for (int i = 0; i <= tail; i++)
    {
        fprintf(fp, "%c", queue[i]->data);
    }
    fprintf(fp, "\n");
}

void *postorder_traversal_2(btree *root, FILE *fp)
{
    if (root == NULL)
        return;
    btree *stack[50], *queue[50], *p = root, *prev;
    int top = -1, tail = -1;
    do
    {
        while (p != NULL)
        {
            stack[++top] = p;
            p = p->lson;
        }                 //p指针寻找最左端的节点
        p = stack[top--]; //栈顶节点出栈
        if (p->rson == NULL || p->rson == prev)
        {
            //如果右子树为空，或者右子树是上一个被遍历的，根节点入队列
            queue[++tail] = prev = p, p = NULL;
        }
        else //否则右子树入栈
            stack[++top] = p, p = p->rson;
    } while (top > -1); //循环直到栈空
    //output
    fprintf(fp, "后序（非递归)\t");
    for (int i = 0; i <= tail; i++)
    {
        fprintf(fp, "%c", queue[i]->data);
    }
    fprintf(fp, "\n");
    return;
}

void *level_traversal(btree *root, FILE *fp)
{
    if (root == NULL)
        return;
    btree *queue2[50], *queue[50], *p = NULL;
    int tail2 = -1, tail = -1, head2 = 0;
    queue2[++tail2] = root;
    do
    {
        p = queue[++tail] = queue2[head2++]; //队列2头出队列
        if (p->lson != NULL)
            queue2[++tail2] = p->lson; //左子树入2
        if (p->rson != NULL)
            queue2[++tail2] = p->rson; //右子树入2
        p = NULL;
    } while (tail2 != head2); //循环直到2空
    fprintf(fp, "分层\t");
    for (int i = 0; i <= tail; i++)
    {
        fprintf(fp, "%c", queue[i]->data);
    }
    fprintf(fp, "\n");
    return;
}

int ScanDepth(btree *root)
{
    int l, r;
    if (root == NULL)
        return 0;
    else
    {
        l = ScanDepth(root->lson);
        r = ScanDepth(root->rson);
        if (l > r)
            return ++l;
        else
            return ++r;
    }
}

int main()
{
    FILE *fp = fopen("labwork5-1-out.txt", "w");
    btree *root = (btree *)malloc(sizeof(btree));
    //    btree_create(root,"ABE##F##CG###");
    btree_create(root, "ab#def##g###ch#i#k##j###");
    fprintf(fp, "先序（递归)\t");
    preorder_traversal(root, fp);
    fprintf(fp, "\n");
    preorder_traversal_2(root, fp);
    fprintf(fp, "中序（递归)\t");
    inorder_traversal(root, fp);
    fprintf(fp, "\n");
    inorder_traversal_2(root, fp);
    fprintf(fp, "后序（递归)\t");
    postorder_traversal(root, fp);
    fprintf(fp, "\n");
    postorder_traversal_2(root, fp);
    level_traversal(root, fp);
    fprintf(fp, "\n树高=");
    fprintf(fp, "%d", ScanDepth(root));
    fclose(fp);
    return 0;
}
