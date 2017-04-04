class TreeNode
{
    public:
        static bool isPerfect(TreeNode* root)
        {
            // TODO: implementation
            if(root == NULL)
                return true;
        }

        static TreeNode* leaf()
        {
            return new TreeNode();
        }

        static TreeNode* join(TreeNode* left, TreeNode* right)
        {
            //return (new TreeNode())->withChildren(left, right);
            return leaf()->withChildren(left, right);
        }

        TreeNode* withLeft(TreeNode* left)
        {
            this->left = left;
            return this;
        }

        TreeNode* withRight(TreeNode* right)
        {
            this->right = right;
            return this;
        }

        TreeNode* withChildren(TreeNode* left, TreeNode* right)
        {
            this->left = left;
            this->right = right;
            return this;
        }

        TreeNode* withLeftLeaf()
        {
            return withLeft(leaf());
        }

        TreeNode* withRightLeaf()
        {
            return withRight(leaf());
        }

        TreeNode* withLeaves()
        {
            return withChildren(leaf(), leaf());
        }

    //private:
        TreeNode* left;
        TreeNode* right;

        TreeNode()
          : left(NULL), right(NULL)
        {
        }
};
