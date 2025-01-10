#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 创建新节点
struct TreeNode* newNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 计算最大深度 - 递归方法
int maxDepth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // 递归计算左右子树的深度
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    // 返回较大的深度 + 1 （当前节点）
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
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
    //   / \  / 
    //  4   5 6 
    //  /      /
    //  7     8
    //  /
    //  9   
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->left->left = newNode(7);
    root->left->left->left->left = newNode(9);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->left->left = newNode(8);
    // 计算并打印最大深度
    int depth = maxDepth(root);
    printf("二叉树的最大深度: %d\n", depth);

    // 释放内存
    freeTree(root);

    return 0;
}