#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

void main()
	{ TreeNode * n1, *n2, *n3 ,*n4, *n5 ,*n6 ,*n7,*n8,*n9,*n10,*n11, *n12, *n13, *n14, *n15;
		n1 = (TreeNode*)malloc(sizeof(TreeNode));
		n2 = (TreeNode*)malloc(sizeof(TreeNode));
		n3 = (TreeNode*)malloc(sizeof(TreeNode));
		n4 = (TreeNode*)malloc(sizeof(TreeNode));
		n5 = (TreeNode*)malloc(sizeof(TreeNode));
		n6 = (TreeNode*)malloc(sizeof(TreeNode));
		n7 = (TreeNode*)malloc(sizeof(TreeNode));
		n8 = (TreeNode*)malloc(sizeof(TreeNode));
		n9 = (TreeNode*)malloc(sizeof(TreeNode));
		n10 = (TreeNode*)malloc(sizeof(TreeNode));
		n11 = (TreeNode*)malloc(sizeof(TreeNode));
		n12 = (TreeNode*)malloc(sizeof(TreeNode));
		n13 = (TreeNode*)malloc(sizeof(TreeNode));
		n14= (TreeNode*)malloc(sizeof(TreeNode));
		n15 = (TreeNode*)malloc(sizeof(TreeNode));


		n1->data = 1;
		n2->data = 2;
		n3->data = 7;
		n4->data = 3;
		n5->data = 6;
		n6->data = 8;
		n7->data = 9;
		n8->data = 4;
		n9->data = 5;
		n10->data = NULL;
		n11->data = NULL;
		n12->data = NULL;
		n13->data = NULL;
		n14->data = 10;
		n15->data = 11;

		n1->left = n2;
		n2->left = n4;
		n3->left = n6;
		n4->left = n8;
		n5->left = n10;
		n6->left = n12;
		n7->left = n14;

		n1->right = n3;
		n2->right = n5;
		n3->right = n7;
		n4->right = n9;
		n5->right = n11;
		n6->right = n13;
		n7->right = n15;
}
preorder(x) {
	if (x != NULL) {
		printf(% d, x);

	}
}

