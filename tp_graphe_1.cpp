#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graphe {
public:
    int nombre_sommet;
    vector<pair<int, int> > arretes_sommet; 

    

    Graphe(){
        cout<<"veillez entrez un nombre de sommets"<<endl;
        cin>>nombre_sommet;


    }
};
int main()
{
    Graphe zebi;
    cout<<zebi.nombre_sommet;
    return 0;
}