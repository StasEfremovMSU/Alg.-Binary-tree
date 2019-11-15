#include<iostream>
#include<algorithm>
#include <fstream>
#include<string>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#define pow2(n) (1 << (n))
using namespace std;

double count_op =0;
int u =0;

ofstream fout("super_results.txt");
int size_of_tree=0;

double met=0;
double ss=0;
int ttemp=200;
void sshow()
{
    if (u >(ttemp -50))                 {met+=count_op;}
    if (u ==ttemp)                      {ss=size_of_tree; met+=count_op; }
    if ( (u >ttemp)&&(u <(ttemp +50) )) {met +=count_op; }

    if (u > (ttemp+50)){ met=met/100; u=50;
        //if (MOV) fout << long_rot << "    " << simple_rot<<"    " << ss<< endl;
    cout << met << "  " << ss << endl;
    //cout << met2<< "  " << met3 << "  " << size_of_tree << endl;
    met=0;     }
}
bool my_eq(string a, string b){
    count_op++;
    if (a == b ) return 1;
    return 0;
}

bool my_less(string a, string b){
    count_op++;
    if (a < b ) return 1;
    return 0;
}

bool my_more(string a, string b){
    count_op++;
    if (a > b ) return 1;
    return 0;
}


char  mask (char a)
{
    if ( a == '.') a =' ';
    if ( a == ';') a =' ';
    if ( a == ':') a =' ';
    if ( a == '"') a =' ';
    if ( a == '?') a =' ';
    if ( a == '!') a =' ';
    if ( a == ',') a =' ';
    if ( a == '-') a =' ';
    return a;
}

struct bi_node
{
    string data;
    int count;
    struct bi_node *left;
    struct bi_node *right;
}*root;

class BiTree
{
    public:
        bi_node *findmin (bi_node *);
        bi_node *input (bi_node *);
        bi_node *del(bi_node *);
        bi_node *create    (string);
        bi_node *removemin (bi_node *);
        bi_node *remove (bi_node *, string );
        bi_node* insert(bi_node *, string );

        void display(bi_node *, int);
        void show (bi_node *);
        BiTree()
        {
            root = NULL;
        }
};



int main()
{
    int choice; string item; size_of_tree = 0;
    BiTree avl;
    while (1)
    {
        cout<<"-------------"<<endl;
        cout<<"BI Tree"<<endl;
        cout<<"------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"7.Delete Element from tree"<< endl;
        cout<<"8.Input Tree from file in.txt"<< endl;
        cout<<"9.Output Worlds from file in2.txt"<< endl;
        cout<<"10.Test of AVL Tree"<< endl;
        cout<<"Enter your Choice: "<< endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            root = avl.insert(root, item);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"Balanced AVL Tree:"<<endl;
            avl.display(root, 1);
            //avl.show(root);
            break;

        case 7:
            cout<< "Delet element:"<< endl;
            cin >> item;
            avl.remove(root, item);
            cout << endl;
            break;
        case 6:
            exit(1);
            break;
        case 8:
            root = avl.input(root);
            cout << "Size of Tree " << size_of_tree << endl;
            break;
        case 9:
            root = avl.del (root);
            cout << "Size of Tree " << size_of_tree << endl;
        break;
        case 10:

            LARGE_INTEGER timerFrequency, timerStart, timerStop;
        QueryPerformanceFrequency(&timerFrequency);
        QueryPerformanceCounter(&timerStart);

            root = avl.input(root);
            root = avl.del (root);


            QueryPerformanceCounter(&timerStop);
        double const t( static_cast<double>( timerStop.QuadPart -
        timerStart.QuadPart ) / timerFrequency.QuadPart );

        cout  << " t = " << t << endl;
        cout << "Size of Tree " << size_of_tree << endl;
        break;

///        default:
   //         cout<<"Wrong Choice"<<endl;
        }
    }


    fout.close();
    return 0;
}

bi_node *BiTree::create(string value)
{
        root = new bi_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        root->count =1;
        size_of_tree ++;
        return root;
}

bi_node *BiTree::insert(bi_node *root, string value)
{
    if (value!="")
{
    if (root == NULL)
    {
        count_op++;
        root = new bi_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        root->count =1;
        size_of_tree ++;
        u++;
        sshow();
    count_op = 0;
        return root;
    }
    else if (my_eq(value, root->data)){ root->count++; }
        else if (my_less (value ,root->data))
                {
                    root->left = insert(root->left, value);
                }
                else if (my_more (value, root->data) || my_eq(value, root->data))
                    {
                        root->right = insert(root->right, value);
                    }
}
    count_op++;
    sshow();
    count_op = 0;
    return root;
}

void BiTree::display(bi_node *tr, int level)
{
    int i;
    if (tr!=NULL)
    {
        display(tr->right, level + 1);
        printf("\n");
        if (tr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && tr != root; i++)
            cout<<"        ";
        cout << level << " " <<tr->data<< " "<< tr->count;
        display(tr->left, level + 1);
    }
}


bi_node *BiTree:: findmin(bi_node* p) // ïîèñê óçëà ñ ìèíèìàëüíûì êëþ÷îì â äåðåâå p
{
    count_op++;
	return p->left?findmin(p->left):p;
}

bi_node *BiTree:: removemin(bi_node* p)
{
    count_op++;
	if( p->left==0 )

		return p->right;
	p->left = removemin(p->left);
	return p;
}

/// ÍÅ ÓÄÀËßÅÒ ÏÎÑËÅÄÍÈÉ ÝËÅÌÅÍÒ
bi_node *BiTree:: remove(bi_node* p, string k)
{
	if( !p ) { return 0;}
	if( my_less(k, p->data) )
            p->left = remove(p->left,k);
	else if(my_more( k ,p->data ))
		p->right = remove(p->right,k);
	else
	{
		bi_node* q = p->left;
		bi_node* r = p->right;
		delete p;

		size_of_tree --; u++;
		if( !r ) return q;
		bi_node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;

		sshow(); count_op=0;
		return min;
	}
	return p;
}

bi_node *BiTree:: input(bi_node* root)
{
    std::ifstream file ("in.txt");
    if ( file== NULL ) { cout << " Can't Open File For Building, Sir "<< cout; return NULL;}
    string n; string tmp; int b;
        while ( getline(file, n,' ') )
    {
        //root = insert (root, n);
        if (n !=" ")
        {
            tmp = "";
            for  (int i=0; i <n.length(); i++)
            {
                if (n[i] == mask (n[i]))
                {
                    tmp += n[i];
                    if ( i== (n.length()-1)) {root = insert (root, tmp);}
                }
                else
                {
                    root = insert (root, tmp);
                    tmp = "";
                }

            }
        }

    }

  //  fclose (file);
    return root;
}

bi_node * BiTree:: del ( bi_node * root)
{
    std::ifstream file ("in2.txt");
    if ( file== NULL ) { cout << " Can't Open File For Removing, Sir "<< cout; return NULL;}

    string n; string tmp; int b;
        while ( getline(file, n,' ') )
    {
        //root = remove (root,n);

        if (n !=" ")
        {
            tmp = "";
            for  (int i=0; i <n.length(); i++)
            {
                if (n[i] == mask (n[i]))
                {
                    tmp += n[i];
                    if ( i== (n.length())) {root = remove (root, tmp);}
                }
                else
                {
                    root = remove (root, tmp);
                    tmp = "";
                }

            }
        }

    }

    return root;
}
