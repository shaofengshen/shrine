// 给定一棵树的根节点 root，翻转这棵二叉树，并返回其根节点

// 翻转二叉树的定义：
// 1. 交换每个节点的左右子节点
// 2. 左右子树也要翻转

// 示例：
// 输入：root = [4,2,7,1,3,6,9]
// 输出：[4,7,2,9,6,3,1]

// 使用队列
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 创建新节点的辅助函数
struct TreeNode* newNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}


struct QueueNode {
    struct TreeNode *node;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enQueue(struct Queue* queue, struct TreeNode* node) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->node = node;
    temp->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }

    queue->rear->next = temp;
    queue->rear = temp;
}

struct TreeNode* deQueue(struct Queue* queue) {
    if (queue->front == NULL) return NULL;
    
    struct QueueNode* temp = queue->front;
    struct TreeNode* node = temp->node;
    
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return node;
}

// 迭代方法翻转二叉树
struct TreeNode* invertTreeIterative(struct TreeNode* root) {
    if (root == NULL) return NULL;
    
    struct Queue* queue = createQueue();
    enQueue(queue, root);
    
    while (queue->front != NULL) {
        struct TreeNode* current = deQueue(queue);
        
        // 交换左右子节点
        struct TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;
        
        // 将子节点加入队列
        if (current->left) enQueue(queue, current->left);
        if (current->right) enQueue(queue, current->right);
    }
    
    free(queue);
    return root;
}

// 打印树的层序遍历（用于验证结果）
void printLevelOrder(struct TreeNode* root) {
    if (root == NULL) return;
    
    struct Queue* queue = createQueue();
    enQueue(queue, root);
    
    printf("层序遍历结果: ");
    while (queue->front != NULL) {
        struct TreeNode* current = deQueue(queue);
        printf("%d ", current->val);
        
        if (current->left) enQueue(queue, current->left);
        if (current->right) enQueue(queue, current->right);
    }
    printf("\n");
    
    free(queue);
}

// 释放树的内存
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // 创建测试树
    //      4
    //     / \
    //    2   7
    //   / \ / \
    //  1  3 6  9
    struct TreeNode* root = newNode(4);
    root->left = newNode(2);
    root->right = newNode(7);
    root->left->left = newNode(1);
    root->left->right = newNode(3);
    root->right->left = newNode(6);
    root->right->right = newNode(9);
    
    printf("原始树:\n");
    printLevelOrder(root);
    
    // 翻转树
    root = invertTreeIterative(root);
    
    printf("翻转后的树:\n");
    printLevelOrder(root);
    
    // 释放内存
    freeTree(root);
    
    return 0;
}