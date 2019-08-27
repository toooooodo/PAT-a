#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef struct node *tree;
struct node {
	int key;
	int color; // 0->black, 1->red
	tree left, right;
};

bool cmp(int a, int b) {
	return abs(a) < abs(b);
}

int get_color(tree root) {
	if (root == NULL)
		return 0;
	else
		return root->color;
}

tree insert(vector<int>& pre, vector<int>& in, int pre_left, int pre_right, int in_left, int in_right) {
	if (pre_left > pre_right)
		return NULL;
	int mid = in_left;
	while (in[mid] != pre[pre_left] && mid <= in_right)
		mid++;
	tree root = (tree)malloc(sizeof(struct node));
	root->key = abs(in[mid]);
	if (in[mid] < 0)
		root->color = 1;
	else
		root->color = 0;
	root->left = insert(pre, in, pre_left + 1, pre_left + mid - in_left, in_left, mid - 1);
	root->right = insert(pre, in, pre_left + mid - in_left + 1, pre_right, mid + 1, in_right);
	return root;
}

int get_black(tree root) {
	if (root == NULL)
		return 0;
	int left_black = get_black(root->left);
	int right_black = get_black(root->right);
	if (root->color == 0)
		return max(left_black, right_black) + 1;
	else
		return max(left_black, right_black);
}

bool check_1(tree root) {
	return root->color == 0;
}

bool check_2(tree root) {
	if (root != NULL) {
		if (root->color == 1) {
			if (get_color(root->left) == 1 || get_color(root->right) == 1)
				return false;
			else
				return check_2(root->left) && check_2(root->right);
		}else
			return check_2(root->left) && check_2(root->right);
	}
	return true;
}

bool check_3(tree root) {
	if (root == NULL)
		return true;
	if (get_black(root->left) != get_black(root->right))
		return false;
	return check_3(root->left) && check_3(root->right);
}

int main() {
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int n;
		cin >> n;
		vector<int> pre, in;
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			pre.push_back(x);
			in.push_back(x);
		}
		sort(in.begin(), in.end(), cmp);
		tree root = insert(pre, in, 0, n - 1, 0, n - 1);
		if (check_1(root) && check_2(root) && check_3(root))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}