#include <bits/stdc++.h>
using namespace std;
bool checkCycle(int node, vector<set<int>> &edges, vector<int> &vis, vector<int> &dfsvis)
{
    vis[node] = 1;
    dfsvis[node] = 1;
    for (auto i : edges[node])
    {
        if (!vis[i])
        {
            if (checkCycle(i, edges, vis, dfsvis))
            {
                return true;
            }
        }
        else if (dfsvis[i])
        {
            cout << "\nCycle is present between node " << i << " & " << node << "\n";
            return true;
        }
    }
    dfsvis[node] = 0;
    return false;
}

bool isCycle(int n, vector<set<int>> &edges)
{
    vector<int> vis(n + 1, 0);
    vector<int> dfsvis(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            if (checkCycle(i, edges, vis, dfsvis))
                return true;
        }
    }
    return false;
}

void topologicalSort(vector<int> &indeg, vector<set<int>> &edges, int n)
{
    queue<int> pq;
    for (int i = 1; i <= n; i++)
    {
        if (indeg[i] == 0)
        {
            pq.push(i);
        }
    }
    
    cout << "\nSerializability Order: ";
    while (!pq.empty())
    {
        
        int x = pq.front();
        pq.pop();
        cout << "T" << x << " ";
        for (auto i : edges[x])
        {
            indeg[i]--;
            if (indeg[i] == 0)
                pq.push(i);
        }
    }
}
void removeSpace(string &str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

int main()
{
    fstream file("inputfile.txt");
    string mystring;
    int count = 0;
    int num_trans = 0;
    if (file.is_open())
    {
        while (file.good() && count < 3)
        {
            getline(file, mystring);
            removeSpace(mystring);
            if (!count)
            {
                num_trans = (mystring.length() + 1 - 6) / 3;
            }

            count++;
        }

        vector<pair<int, string>> trans;

        while (file)
        {
            getline(file, mystring);

            removeSpace(mystring);
            trans.push_back(make_pair((mystring[1] - 48), mystring.substr(3, 5)));
        }
        trans.resize(trans.size()-1);
        cout << "-----------------Schedule-------------------\n";
        for (auto i : trans)
        {
            cout << "T" << i.first << " " << i.second << "\n";
        }
        if (num_trans == 1)
        {
            cout << "This is Conflict Serializable Schedule\n";
            cout << "Its Equivalent Serial Schedule :"<< "\n";
            return 0;
        }

        vector<set<int>> edges(num_trans + 1);
        pair<int, int> x;
        for (int i = 0; i < trans.size(); i++)
        {
            for (int j = i + 1; j < trans.size(); j++)
            {
                if (trans[i].second[0] == 'R')
                {
                    if (trans[i].first != trans[j].first && trans[j].second[0] == 'W' && trans[i].second[2] == trans[j].second[2])
                        edges[trans[i].first].insert(trans[j].first);
                }
                if (trans[i].second[0] == 'W')
                {
                    if (trans[i].first != trans[j].first && trans[j].second[2] == trans[i].second[2])
                        edges[trans[i].first].insert(trans[j].first);
                }
            }
        }
        vector<int> indeg(num_trans + 1, 0);
        indeg[0] = -1;
        cout << "\n-------------Conflicting Operations--------------\n";
        cout << "From -->  To\n";
        for (int i = 1; i <= num_trans; i++)
        {
            cout << "  " << i << "  -->  ";
            for (auto it : edges[i])
            {

                indeg[it]++;
                cout << it << " ";
            }
            cout << "\n";
        }

        bool flag = isCycle(num_trans, edges);
        flag ? cout << "\n This isn't a Conflict Serializable Schedule\n" : cout << "\nThis is Conflict Serilizable Schedule\n";

        if (flag == 1)
        {
            cout << "\n\n\n\n";
            return 0;
        }
        topologicalSort(indeg, edges, num_trans);
        cout << "\n\n\n\n";
    }
    else
    {
        cout << "Can't open file!!";
    }
}