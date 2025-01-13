#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 1000
#define MAX_WIDTH 1000

// 1. 首先定义二叉树节点结构
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 2. 函数声明
struct TreeNode* newNode(int value);
struct TreeNode* invertTreeIterative(struct TreeNode* root);
void freeTree(struct TreeNode* root);
void printBinaryTree(struct TreeNode* root);

// 3. 创建新节点的函数实现
struct TreeNode* newNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printBinaryTree(struct TreeNode* root) {
    if (!root) return;
    
    char matrix[MAX_HEIGHT][MAX_WIDTH];
    memset(matrix, ' ', sizeof(matrix));
    
    // 队列用于层次遍历
    struct TreeNode* queue[1000];
    int levels[1000];  // 存储每个节点的层级
    int positions[1000];  // 存储每个节点的位置
    int front = 0, rear = 0;
    
    // 将根节点入队
    queue[rear] = root;
    levels[rear] = 0;
    positions[rear] = MAX_WIDTH/2;
    rear++;
    
    int maxLevel = 0;
    
    // 层次遍历
    while (front < rear) {
        struct TreeNode* node = queue[front];
        int level = levels[front];
        int pos = positions[front];
        front++;
        
        // 更新最大层级
        if (level > maxLevel) maxLevel = level;
        
        // 打印当前节点
        char str[10];
        sprintf(str, "%d", node->val);
        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            matrix[level*2][pos+i] = str[i];
        }
        
        // 处理左子节点
        if (node->left) {
            queue[rear] = node->left;
            levels[rear] = level + 1;
            positions[rear] = pos - (1 << (maxLevel-level-1));
            
            // 打印连接线
            matrix[level*2+1][pos-1] = '/';
            rear++;
        }
        
        // 处理右子节点
        if (node->right) {
            queue[rear] = node->right;
            levels[rear] = level + 1;
            positions[rear] = pos + (1 << (maxLevel-level-1));
            
            // 打印连接线
            matrix[level*2+1][pos+1] = '\\';
            rear++;
        }
    }
    
    // 打印树
    for (int i = 0; i <= maxLevel*2; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            if (matrix[i][j] != ' ') {
                printf("%c", matrix[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    // 创建测试树
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    printf("原始树:\n");
    printBinaryTree(root);
    
    root = invertTreeIterative(root);
    
    printf("\n翻转后:\n");
    printBinaryTree(root);
    
    freeTree(root);
    return 0;
}