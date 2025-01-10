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

// 获取树的节点数量（用于预分配结果数组）
int getTreeSize(struct TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + getTreeSize(root->left) + getTreeSize(root->right);
}

// 迭代实现中序遍历
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    // 获取树的大小
    *returnSize = getTreeSize(root);
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    
    // 创建栈
    struct TreeNode** stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * (*returnSize));
    int top = -1;  // 栈顶指针
    int index = 0; // 结果数组索引
    
    struct TreeNode* current = root;
    
    while (current != NULL || top >= 0) {
        // 遍历到最左边
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        
        // 处理栈顶节点
        current = stack[top--];
        result[index++] = current->val;
        
        // 转向右子树
        current = current->right;
    }
    
    // 释放栈内存
    free(stack);
    return result;
}

// 释放树的内存
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// 测试代码
int main() {
    // 创建测试树
    //      1
    //     / \
    //    2   3
    //   / \
    //  4   5
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    // 执行中序遍历
    int size;
    int* result = inorderTraversal(root, &size);
    
    // 打印结果
    printf("中序遍历结果: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    // 释放内存
    free(result);
    freeTree(root);
    
    return 0;
}