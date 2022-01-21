                            /*VAN emde boas trees
                                DAA package
                    Done by 20pw01-Abishek.A, 20pw30-SaiDinesh.B*/
#include <bits/stdc++.h>
using namespace std;
class VEB
{
public:
    int u;
    VEB* summary;
    vector <VEB*> clusters;

    int root(int u)
    {
        return (int)sqrt(u);
    }

    // Function to return cluster numbers in which key is present
    int high(int x)
    {
        return x / root(u);
    }

    // Function to return position of x in cluster
    int low(int x)
    {
        return x % root(u);
    }

    // Function to return the index from cluster number and position
    int index(int cluster, int position)
    {
        return cluster * root(u) + position;
    }

    // Constructor
    VEB(int size)
    {
        u = size;
        if (size <= 2)
        {
            // There is no summary for size 2
            summary = nullptr;
            clusters = vector<VEB*>(size, nullptr);
        }
        else
        {
            summary = new VEB(root(size));

            // Creating array in tree of size sqrt(u)
            clusters = vector<VEB*>(root(size), nullptr);
            for (int i = 0; i < root(size); i++)
            {
                clusters[i] = new VEB(root(size));
            }
        }
    }
};

// Function to check a key is present in the tree
bool isMember(VEB* N, int key)
{
    if (key >= N->u)
    {
        return false;
    }
    if (N->u == 2)
    {
        return N->clusters[key];
    }
    else
    {
        // Recursively go deep into the level of VEB tree using its cluster index and its position
        return isMember(N->clusters[N->high(key)],N->low(key));
    }
}

// Function to insert a key in the tree
void insert(VEB*& N, int key)
{
    if (N->u == 2)
    {
        N->clusters[key] = new VEB(1);
    }
    else
    {
        // Recursively using index of cluster and its position in cluster
        insert(N->clusters[N->high(key)],N->low(key));

        // Also do the same recursion in summary VEB
        insert(N->summary, N->high(key));
    }
}

// Function to return the minimum key from the tree
int minimum(VEB* N)
{
    if (N->u == 2)
    {
        if (N->clusters[0])
        {
            return 0;
        }
        else if (N->clusters[1])
        {
            return 1;
        }
        return -1; // tree is empty
    }
    else
    {
        // Recursively find summary for first 1 present in VEB
        int minimum_cluster = minimum(N->summary);
        int n;
        if (minimum_cluster == -1)
        {
            return -1; //No key present in the cluster
        }
        else
        {
            // Recursively find the position of the key in the minimum_cluster
            n = minimum(N->clusters[minimum_cluster]);
            return N->index(minimum_cluster, n);
        }
    }
}

// Function to return the maximum key from the tree
int maximum(VEB* N)
{
    if (N->u == 2)
    {
        if (N->clusters[1])
        {
            return 1;
        }
        else if (N->clusters[0])
        {
            return 0;
        }
        return -1; // tree is empty
    }
    else
    {
        // Recursively find the last 1 present in the summary
        int maximum_cluster = maximum(N->summary);
        int n;
        if (maximum_cluster == -1)
        {
            return -1; // No key present in the cluster
        }
        else
        {
            // Recursively find the position of the key in the maximum_cluster
            n = maximum(N->clusters[maximum_cluster]);
            return N->index(maximum_cluster, n);
        }
    }
}

// Function to return the successor of key in the tree
int successor(VEB* N, int key)
{
    if (N->u == 2)
    {
        if (key == 0 && N->clusters[1])
            return 1;
        else
            return -1;
    }
    else
    {
        // Check for successor in the same cluster
        int n = successor(N->clusters[N->high(key)], N->low(key));
        if (n != -1)
        {
            return N->index(N->high(key), n);
        }
        else
        {
            // Check for next 1 in summary
            int successor_cluster = successor(N->summary,N->high(key));

            // If no next 1 in the summary then return -1
            if (successor_cluster == -1)
                return -1;
            else
            {
                // Find the minimum key in the successor_cluster
                n = minimum(N->clusters[successor_cluster]);
                return N->index(successor_cluster, n);
            }
        }
    }
}

// Function to return the predecessor of key in the tree
int predecessor(VEB* N, int key)
{
    if (N->u == 2)
    {
        if (key == 1 && N->clusters[0])
            return 0;
        else
            return -1;
    }
    else
    {
        // Check for predecessor in the same cluster
        int n = predecessor(N->clusters[N->high(key)],N->low(key));
        if (n != -1)
            return N->index(N->high(key), n);
        else
        {
            int predecessor_cluster = predecessor(N->summary, N->high(key));
            // If no before 1 in the summary then return -1
            if (predecessor_cluster == -1)
                return -1;
            else
            {
                // Find the maximum key in the predecessor_cluster
                n = maximum(N->clusters[predecessor_cluster]);
                return N->index(predecessor_cluster, n);
            }
        }
    }
}

// Function to delete a key from the tree
void veb_delete(VEB*& N, int key)
{
    // Make key nullptr
    if (N->u == 2)
    {
        if (N->clusters[key])
        {
            delete N->clusters[key];
            N->clusters[key] = nullptr;
        }
    }
    else
    {
        veb_delete(N->clusters[N->high(key)], N->low(key));
        bool isanyinCluster = false;

        // Check any key is present within that cluster
        for (int i = N->high(key)*N->root(N->u); i < (N->high(key) + 1)*N->root(N->u); i++)
        {
            if (isMember(N->clusters[N->high(key)], i))
            {
                isanyinCluster = true;
                break;
            }
        }
        // If no member is present then update summary to zero
        if (isanyinCluster == false)
        {
            veb_delete(N->summary, N->high(key));
        }
    }
}

void print(VEB*&N, int u)
{
    for(int i=0; i<u; i++)
    {
        if(isMember(N,i)==true)
            cout << i << " ";
    }
}

int main()
{
    cout << "\n\tV A N   E M D E   B O A S   T R E E S\n" << endl;
    int k;
    long long int u;
    L:
    cout << "--------------------------------------------------------\n"<<endl;
    cout << "Enter value of k (k>=0) for VEB tree size u = 2^(2^k): ";
    cin >> k;
    if(k>0)
    {
        u = pow(2,pow(2,k));
    }
    else
    {
        cout << "Enter value of k in range k>0" << endl;
        goto L;
    }
    cout << "Size of VEB = " << u << endl;
    VEB* v = new VEB(u);
    int c, elt;
    do
    {
        cout << "\n--------------------------------------------------------\n"<<endl;
        cout << "  1 To insert elt\n";
        cout << "  2 To check elt is a member\n";
        cout << "  3 To delete an elt\n";
        cout << "  4 To find maximum elt in the VEB tree\n";
        cout << "  5 To find minimum elt in the VEB tree\n";
        cout << "  6 To find successor of an elt\n";
        cout << "  7 To find predecessor of an elt\n";
        cout << "  8 To print elements in tree\n";
        cout << "  0 To exit\n";
        cout << "\nEnter your choice: ";
        cin >> c;
        cout << "--------------------------------------------------------\n"<<endl;
        if(c==1)
        {
            L1:
            cout << "\nEnter valid elt to insert in VEB tree (0 <= elt < " << u << "): ";
            cin >> elt;
            if(elt>=0 && elt<u)
            {
                insert(v,elt);
                cout << elt << " is inserted in VEB tree." << endl;
            }
            else
            {
                cout << "Invalid insertion! Enter elt between 0 and " << u << endl;
                goto L1;
            }
        }
        else if(c==2)
        {
            cout << "\nEnter elt to check isMember: ";
            cin >> elt;
            if(isMember(v,elt)==false)
                cout << elt << " is not a member of VEB tree" << endl;
            else
                cout << elt << " is a member of VEB tree" << endl;
        }
        else if(c==3)
        {
            cout << "\nEnter elt to delete from VEB tree: ";
            cin >> elt;
            if(isMember(v,elt)==true)
            {
                veb_delete(v,elt);
                cout << elt << " is deleted successfully from VEB tree" << endl;
            }
            else
                cout << elt << " not found in VEB tree, unable to delete" << endl;
        }
        else if(c==4)
        {
            cout << "Maximum value in VEB: " << maximum(v) << endl;
        }
        else if(c==5)
        {
            cout << "Minimum value in VEB: " << minimum(v) << endl;
        }
        else if(c==6)
        {
            cout << "Enter elt to find its successor in VEB: ";
            cin >> elt;
            if(isMember(v,elt)==true)
            {
                if(successor(v,elt)!=-1)
                    cout << "Successor of " << elt << " is " << successor(v,elt) << endl;
                else
                    cout << "There is no successor for " << elt << " in the VEB tree" << endl;
            }
            else
            {
                cout << elt << " not present in tree so no successor" << endl;
            }
        }
        else if(c==7)
        {
            cout << "Enter elt to find its predecessor in VEB: ";
            cin >> elt;
            if(isMember(v,elt)==true)
            {
                if(predecessor(v,elt)!=1)
                    cout << "Predecessor of " << elt << " is " << predecessor(v,elt) << endl;
                else
                    cout << "There is no predecessor for " << elt << " in the VEB tree" << endl;
            }
            else
            {
                cout << elt << " not present in tree so no predecessor" << endl;
            }
        }
        else if(c==8)
        {
            cout << "The tree is: ";
            print(v,u);
        }
        else if(c==0)
        {
            exit(0);
        }
        else
        {
            cout << "\nPlease enter correct input" << endl;
        }
    }while(c!=0);
    return 0;
}
