/*name 	gaoce
 *ID 	5120379091*/

#include <iostream>
#include <stack>

using namespace std;

struct tree
{
    int data;
    tree *left,*right;
};
class Btree
{
    static int n;
    static int m;
public:
    tree *root;
    Btree()
    {
        root=NULL;
    }
    void create_Btree(int);
};                                          
int Btree::n=0;
int Btree::m=0;
void Btree::create_Btree(int x)
{
    tree *newnode=new tree;
    newnode->data=x;
    newnode->right=newnode->left=NULL;
    if(root==NULL)
        root=newnode;
    else
    {
        tree *back;
        tree *current=root;
        while(current!=NULL)
        {
            back=current;
            if(current->data>x)
                current=current->left;
            else
                current=current->right;
        }
        if(back->data>x)
            back->left=newnode;
        else
            back->right=newnode;
    }
}

class InorderIterator{
    public:
        InorderIterator(tree *node) {
            tree *current = node;
            while (NULL != current) {
                mStack.push(current);
                current = current->left;
            }
        }
         int & operator *()
         {
         	if (mStack.empty() == false)
         		return mStack.top()->data;
         }

         tree * operator ++(int)
         {
         	if (mStack.empty()) {
                return NULL;
            }
            tree *top = mStack.top();
            mStack.pop();
            if (NULL != top->right) {
                tree *current = top->right;
                while (NULL != current) {
                    mStack.push(current);
                    current = current->left;
                }
            }
            return top;
         }
    private:
        std::stack<tree*> mStack;
};

int main ()
{
	Btree A;
    int array[]={1,2,3,4,5,6,7};
    int v = 3;
    int k;
    k=sizeof(array)/sizeof(array[0]);
    for(int i=0;i<k;i++)
    {
        cout<<array[i]<<" ";
        A.create_Btree(array[i]);
    }
    cout<<endl<<"the number > 3 are "<<endl;
    InorderIterator it(A.root);
    while (1)
    {
    	if (it++ != NULL)
    	{
    		if (*it > 3)
    			cout<<*it<<endl;
    	}
    	else break;
    }
    return 0;
}