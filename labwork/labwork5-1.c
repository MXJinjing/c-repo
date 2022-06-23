/*
    ���������Һ������ӽṹ��ʾ�Ķ�������ʵ�ֶ��������������򡢺���ĵݹ�ͷǵݹ鷽ʽ�������ֲ������ͳ�����ĸ߶ȡ�
    ��չ���⣺
    ����һ��ؼ������У�����һ��ƽ���������
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree {
    char data;
    struct binary_tree *lson;
    struct binary_tree *rson;
} btree;

//�Դ�#�������������������
char *btree_create(btree *root, char *s)
{
    root->data = *(s++);
    printf("%c\n", root->data);
    if (root->data != '#')
    {
        btree *templ = (btree *)malloc(sizeof(btree));
        btree *tempr = (btree *)malloc(sizeof(btree));
        printf("����%c��������:", root->data);
        s = btree_create(templ, s);
        if (templ->data != '#')
            root->lson = templ;
        else
            root->lson = NULL;
        printf("����%c��������:", root->data);
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
    stack[++top] = root; //���ڵ���ջ
    do
    {
        queue[++tail] = p = stack[top--]; //ȡ��ջ���ڵ������
        if (p->rson != NULL)
            stack[++top] = p->rson; //ջ���ڵ���������ڵ���ջ
        if (p->lson != NULL)
            stack[++top] = p->lson; //ջ���ڵ���������ڵ���ջ
    } while (top > -1);             //ѭ��ֱ��ջ��
    //output
    fprintf(fp, "���򣨷ǵݹ�)\t");
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
        }                                 //pָ��Ѱ������˵Ľڵ�
        queue[++tail] = p = stack[top--]; //ջ���ڵ��ջ�����ڵ������
        p = p->rson;                      //pָ�����������
    } while (p != NULL || top > -1);      //ѭ��ֱ��p��Ϊ����ջ��
    //output
    fprintf(fp, "���򣨷ǵݹ�)\t");
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
        }                 //pָ��Ѱ������˵Ľڵ�
        p = stack[top--]; //ջ���ڵ��ջ
        if (p->rson == NULL || p->rson == prev)
        {
            //���������Ϊ�գ���������������һ���������ģ����ڵ������
            queue[++tail] = prev = p, p = NULL;
        }
        else //������������ջ
            stack[++top] = p, p = p->rson;
    } while (top > -1); //ѭ��ֱ��ջ��
    //output
    fprintf(fp, "���򣨷ǵݹ�)\t");
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
        p = queue[++tail] = queue2[head2++]; //����2ͷ������
        if (p->lson != NULL)
            queue2[++tail2] = p->lson; //��������2
        if (p->rson != NULL)
            queue2[++tail2] = p->rson; //��������2
        p = NULL;
    } while (tail2 != head2); //ѭ��ֱ��2��
    fprintf(fp, "�ֲ�\t");
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
    fprintf(fp, "���򣨵ݹ�)\t");
    preorder_traversal(root, fp);
    fprintf(fp, "\n");
    preorder_traversal_2(root, fp);
    fprintf(fp, "���򣨵ݹ�)\t");
    inorder_traversal(root, fp);
    fprintf(fp, "\n");
    inorder_traversal_2(root, fp);
    fprintf(fp, "���򣨵ݹ�)\t");
    postorder_traversal(root, fp);
    fprintf(fp, "\n");
    postorder_traversal_2(root, fp);
    level_traversal(root, fp);
    fprintf(fp, "\n����=");
    fprintf(fp, "%d", ScanDepth(root));
    fclose(fp);
    return 0;
}
