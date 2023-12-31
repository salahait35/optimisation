#include <iostream>
#include <vector>
#include <stack>
#include <limits>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        // Téléchargez la bibliothèque inih depuis https://github.com/benhoyt/inih.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    void affiche_arrete(){cout<<"Arete : V"<<start<<" --------- +"<<cost<<" ---------> "<<end<<endl;}
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
    vector<pair<int,int> > chemin_a_partir_de_zero;
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

    }

    Graphe(bool go) /// CONSTRUCTEUR POUR LES TEST ET NON PAS POUR LE CAS GENERAL A UTILISER UNIQUEMENT POUR DEV
    {
        nombre_sommet = 6;

        tab_valeur_cabine_sommet.push_back(make_pair(0,0));
        tab_valeur_cabine_sommet.push_back(make_pair(1,200));
        tab_valeur_cabine_sommet.push_back(make_pair(2,200));
        tab_valeur_cabine_sommet.push_back(make_pair(3,300));
        tab_valeur_cabine_sommet.push_back(make_pair(4,700));
        tab_valeur_cabine_sommet.push_back(make_pair(5,1000));
        tab_valeur_cabine_sommet.push_back(make_pair(6,200));

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
    }

    /*  
        ici on fait en sorte d'avoir les deux pires cas donc selon l'exercice stocker tout ou bien importer chaque mois
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

            chemin_a_partir_de_zero.push_back(make_pair(i,somme_global));
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
#if DEBUG
        for(int j = 0; j< mes_sommets.size();j++)
        {
            mes_sommets[j].affiche_sommet();
        }
#endif

    }

    vector<pair<int,int> > les_chemin_vers_mon_sommet(int id)
    {
        vector<pair<int,int> > chemin_dispo_vers_mon_sommet;
        for(int i=0; i<mes_sommets.size();i++)
        {
            if(mes_sommets[i].connexions.size()>0){
            for(int j = 0;j<mes_sommets[i].connexions.size();j++)
            {
                if(mes_sommets[i].connexions[j].end == id)
                {
                    chemin_dispo_vers_mon_sommet.push_back(make_pair(mes_sommets[i].connexions[j].start,mes_sommets[i].connexions[j].cost));
                }
            }
            }
        }
        return chemin_dispo_vers_mon_sommet;
    } 

    void calcule_plus_court_chemin()
    {
        int cout_minimal = 0;
        stack <int> plus_court_chemin;
        stack <int> sommer_non_visite;
        vector <pair<int,int> > plus_court_chemin_vers_sommet;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                            //INIT

        plus_court_chemin.push(SOMMET_DEPART); // initialisation de notre pile du plus court chemin 

        for(int i = mes_sommets.size()-1;i>0;i-- )
        {
            sommer_non_visite.push(mes_sommets[i].id);
        }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        while (!sommer_non_visite.empty())
        {
            vector<pair<int,int> > temp = les_chemin_vers_mon_sommet(sommer_non_visite.top());
            //cout<<"chemin vers le sommet : "<<sommer_non_visite.top()<<endl<<endl;
            /// ALGORITHME PLUS COURT CHEMIN    
            /// 1 er cas ou il n'ya qu'une connexion possible a ce sommet, donc pas besoin de calculer le plus court chemin. 

            //cout<<endl<<"chemin vers le sommet : "<<sommer_non_visite.top()<<endl;


#if DEBUG
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

            /// BOUT DE CODE POUR LE DEBUG ///
            for(int i = 0; i < temp.size();i++)
            {

                cout<<"V"<<temp[i].first <<"+ -------"<<temp[i].second<< " -----------> "<<sommer_non_visite.top()<<endl;
            }
            /// FIN DE DEBUG 


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

            if(temp.size()==1)
            {
                plus_court_chemin.push(sommer_non_visite.top()); // on met dans la pile le sommet car il n'ya que cette connexion vers lui
                cout_minimal += temp[0].second; // on additionne le cout minimal
                plus_court_chemin_vers_sommet.push_back(make_pair(sommer_non_visite.top(),cout_minimal)); // on stock ici uniquement les cout minimal pour une
                // un sommet donc ici l'exemple sommet 2,2400
            }
            else
            {
                cout_minimal = numeric_limits<int>::max();
                int temp_min; 
                int sommet_prefixant = SOMMET_DEPART;
                for(int i = 0; i< temp.size();i++)
                {
                    int ecart = sommer_non_visite.top()-temp[i].first;
                    switch (ecart)
                    {
                    case 1:
                        temp_min = plus_court_chemin_vers_sommet[temp[i].first-1].second + VALEUR_DEF_ENTRE_SOMMET;
                        break;
                        
                    default:
                        if(temp[i].first == 0)
                        {
                            temp_min = chemin_a_partir_de_zero[sommer_non_visite.top()-1].second; // chemin depuis zero 
                        }
                        else{
                            temp_min = plus_court_chemin_vers_sommet[temp[i].first-1].second + VALEUR_DEF_ENTRE_SOMMET;
                            for(int k = 0; k<ecart;k++) // Cout(Vi) = Cout(Vi-1) + ( Vi * VALEUR_DEF_STOCKAGE_CABINE * NB_CABINES_POUR LE SOMMET )
                            {
                                temp_min += VALEUR_DEF_STOCKAGE_CABINE * (k) * tab_valeur_cabine_sommet[temp[i].first+k+1].second;
                            }
                        }
                        break;
                    }

                    if(temp_min < cout_minimal)
                    {
                        cout_minimal = temp_min;
                        sommet_prefixant = temp[i].first;
                    }
#if DEBUG
                    cout<<"sommet la : "<<temp[i].first<<" --------"<<temp_min<<"-------> "<<sommer_non_visite.top()<<endl;
#endif
                }
                plus_court_chemin_vers_sommet.push_back(make_pair(sommet_prefixant,cout_minimal));
  
            }
                sommer_non_visite.pop();
        }

    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                // PARTIE AFFICHAGE RESULTAT 

        cout<<endl<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
        cout<<endl<<endl<<"\t\t\t le cout minimal est de "<<plus_court_chemin_vers_sommet[nombre_sommet-1].second<<endl<<endl;
        cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
        
        cout<<" le chemin est : "<<nombre_sommet;
        int indice = nombre_sommet-1;
        while(indice != -1)
        {
            cout<<" <-------"<<plus_court_chemin_vers_sommet[indice].second<<"----- "<<plus_court_chemin_vers_sommet[indice].first;
            indice = plus_court_chemin_vers_sommet[indice].first - 1;
        }

        cout<<endl<<endl<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

        cout<<endl<<endl;

#if DEBUG
       for(int l=0;l<plus_court_chemin_vers_sommet.size();l++)
       {
        cout<<"indice "<<l+1<<" first = "<<plus_court_chemin_vers_sommet[l].first<<" second "<<plus_court_chemin_vers_sommet[l].second<<endl;
       }
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }



    void affiche_chemin_depuis_zero()
    {
        for(int t= 0; t<chemin_a_partir_de_zero.size();t++) 
        {
            cout<<chemin_a_partir_de_zero[t].first+1<<" le cout a partir de zero est de : "<<chemin_a_partir_de_zero[t].second<<endl;
        }
    }
    

};
int main()
{
#if USER
    Graphe zebi();
#else
    Graphe zebi(true);
#endif
    zebi.calcules_pire_cas();
    zebi.calcule_arete_entre_sommet();
    zebi.calcule_plus_court_chemin();

#if DEBUG
    zebi.affiche_chemin_depuis_zero();
#endif
    return 0;
}