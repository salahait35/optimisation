#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define VALEUR_DEF_ENTRE_SOMMET 2000

#define VALEUR_DEF_STOCKAGE_CABINE 2

#define SOMMET_DEPART 0


class arete{
    public:
    int start;
    int end;
    float cost;
    arete(int s,int e, float c){
        start = s;
        end = e;
        cost = c;
    }
    void affiche_arrete(){cout<<"Arete : "<<start<<" --------- "<<cost<<" ---------> "<<end<<endl;}
}; 

 class sommet{
    public:
    int id; 
    vector <arete> connexions;
    sommet(int iD){
        id = iD;
    }

    void affiche_sommet()
    {
        if(connexions.size()>0)
        {
        cout<<"***************************************"<<endl;
        cout<<" SOMMET ID : "<<id<<endl;
        for(int i=0;i<connexions.size();i++)
        {
            connexions[i].affiche_arrete();
        }
        cout<<"***************************************"<<endl;
        }
    }

};

class Graphe {

public:
    int nombre_sommet;
    vector<pair<int, int> > tab_valeur_cabine_sommet;
    vector<sommet> mes_sommets;



    Graphe(){
        cout<<"veillez entrez un nombre de sommets"<<endl;
        cin>>nombre_sommet;
        tab_valeur_cabine_sommet.push_back(make_pair(0,0));

        for(int i = 1;i<= nombre_sommet;i++)
        {
            int temp;
            cout<<"pour le sommet numero : "<<i<<" veuillez entrez le nombre de cabines. "<<endl;
            cin>>temp;
            tab_valeur_cabine_sommet.push_back(make_pair(i,temp));
            ////////// INIT SOMMET /////// 
        }
        std::cout <<endl<<endl<<endl<<endl<<endl<<endl; 
        for(int i = 0;i<= nombre_sommet;i++)
        {
            
            sommet temp(i);
            if( i != nombre_sommet)
            {
                arete init(i,i+1,VALEUR_DEF_ENTRE_SOMMET);
                temp.connexions.push_back(init);
            }
            mes_sommets.push_back(temp);
            cout<<"pour le sommet numero : "<<i<<"  voila le nombre de cabines  -------->  "<<tab_valeur_cabine_sommet[i].second<<endl;
        } 
        for(int j = 0; j< mes_sommets.size();j++)
        {
            mes_sommets[j].affiche_sommet();
        }

    }

    /*  ici on fait en sorte d'avoir les deux pires cas donc selon l'exercice stocker tout ou bien importer chaque mois
        la regles pour calculer le cout de chaque sommet est de : 
        Cout(Vi) = Cout(Vi-1) + ( Vi * VALEUR_DEF_STOCKAGE_CABINE * NB_CABINES_POUR LE SOMMET )  
        avec V0 = {0,0}
        Vi qui est un int, le numero du mois  
    */
    void calcules_pire_cas()
    {   
        std::cout <<endl<<endl;
        int somme_global = 0;
        for(int i = 0; i< mes_sommets.size()-1;i++)
        {
            somme_global += mes_sommets[i].connexions[0].cost;
        }
        cout<<"Pire cas en livraison chaque mois ------------> "<<somme_global<<endl;

        somme_global = 0;

        for(int i = 0; i< mes_sommets.size()-1;i++)
        {
            if(mes_sommets[i].id>0)
            {
                somme_global += ( VALEUR_DEF_STOCKAGE_CABINE * mes_sommets[i].id * tab_valeur_cabine_sommet[i+1].second );
            }
            else {somme_global += VALEUR_DEF_ENTRE_SOMMET;}
        }

        cout<<endl<<endl<<"Pire cas en stockage ------------> "<<somme_global<<endl; 
    }
    void calcule_arete_entre_sommet()
    {
        for(int i = 0;i<=mes_sommets.size();i++)
        {
            for(int j = i+2;j<mes_sommets.size();j++)
            {
                int temp;
                if(i>0)
                {temp = (mes_sommets[j].id -i-1) * VALEUR_DEF_STOCKAGE_CABINE * tab_valeur_cabine_sommet[j].second;}
                else{temp = (mes_sommets[j].id -1) * VALEUR_DEF_STOCKAGE_CABINE * tab_valeur_cabine_sommet[j].second;}
                if(temp<=VALEUR_DEF_ENTRE_SOMMET)
                {
                    arete temporaire(mes_sommets[i].id,mes_sommets[j].id,temp);
                    mes_sommets[i].connexions.push_back(temporaire);
                }
            } 
        }

        for(int j = 0; j< mes_sommets.size();j++)
        {
            mes_sommets[j].affiche_sommet();
        }


    }

};
int main()
{
    Graphe zebi;
    zebi.calcules_pire_cas();
    zebi.calcule_arete_entre_sommet();
    return 0;
}