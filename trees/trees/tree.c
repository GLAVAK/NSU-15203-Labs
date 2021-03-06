#include "tree.h"

Tree_node * tree_create(ContentType content)
{
	Tree_node * tree = malloc(sizeof(Tree_node));
	tree->data = content;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

size_t tree_get_height(Tree_node * root)
{
	if (root == NULL) return 0;

	int left_height = tree_get_height(root->left);
	int right_height = tree_get_height(root->right);

	return (left_height > right_height ? left_height : right_height) + 1;
}

void tree_free(Tree_node * root)
{
	if (root->left != NULL) tree_free(root->left);
	if (root->right != NULL) tree_free(root->right);

	free(root);
}

Tree_node * tree_insert_raw(Tree_node * root, ContentType content, Direction direction)
{
	if (direction == LEFT && root->left != NULL)
	{
		return tree_insert_raw(root->left, content, LEFT);
	}
	else if (direction == RIGHT && root->right != NULL)
	{
		return tree_insert_raw(root->left, content, RIGHT);
	}
	else if (direction == LEFT)
	{
		root->left = tree_create(content);
		return root->left;
	}
	else // if (direction == RIGHT)
	{
		root->right = tree_create(content);
		return root->right;
	}
}

void tree_delete_node(Tree_node * root, Direction direction)
{
	if (direction == LEFT)
	{
		tree_free(root->left);
		root->left = NULL;
	}
	else // if (direction == RIGHT)
	{
		tree_free(root->right);
		root->right = NULL;
	}
}

Tree_node * tree_insert_balanced(Tree_node * root, ContentType content)
{
	if (content < root->data)
	{
		if (root->left == NULL)
		{
			root->left = tree_create(content);
			return root->left;
		}
		else
		{
			return tree_insert_balanced(root->left, content);
		}
	}
	else
	{
		if (root->right == NULL)
		{
			root->right = tree_create(content);
			return root->right;
		}
		else
		{
			return tree_insert_balanced(root->right, content);
		}
	}
}

Tree_node * tree_find(Tree_node * root, ContentType data)
{
	if (data == root->data)
	{
		return root;
	}
	else
	{
		Tree_node * found_in_left = NULL;
		Tree_node * found_in_right = NULL;

		if (root->left != NULL)
		{
			found_in_left = tree_find(root->left, data);
		}
		if (root->right != NULL)
		{
			found_in_right = tree_find(root->right, data);
		}

		if (found_in_left != NULL) return found_in_left;
		else if (found_in_right != NULL) return found_in_right;
		else return NULL;
	}
}