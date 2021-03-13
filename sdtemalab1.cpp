#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <algorithm>

using namespace std;
//afisarea vectorului
void print(vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}
//generam random n numere in vectorul a, numarul maxim fiind nr_max
void generate_a(vector<int>& a, int n, int nr_max)
{
    //stergem vectorul sa ne asiguram ca nu avem alte elemente
    a.clear();
    srand((int)time(0));
    for (int i = 0; i < n; i++)
        a.push_back((rand() % nr_max) + 1);
}
//verificam daca vectorul este sortat, returneaza 1 daca este sortat si 0 daca nu
int test_sort(vector<int> a)
{
    for (int i = 1; i < a.size(); i++)
        if (a[i-1]>a[i])
            return 0;
    return 1;
}
//calculam valoarea maxima din vector si o returnam
int maxim(vector<int> a)
{
    int m = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] > m)
            m = a[i];
    return m;
}
//BUBBLESORT
void bubblesort(vector<int>& a)
{
    bool ok = true;
    while(ok){
        ok = false;
        for (int i = 0; i < a.size(); i++){
            for (int j = i + 1; j < a.size(); j++)
                if (a[j-1] > a[j]){
                    swap(a[j], a[j-1]);
                    ok = true;
                }
            if (ok == false)
                return;
        }
    }
}
//COUNTSORT
void countsort(vector<int>& a)
{
    vector<int> fr;
    int m = maxim(a);
    fr.assign(m+1,0);
    for (int i = 0; i < a.size(); i++)
        fr[a[i]]++;
    int poz = 0;
    for (int i = 0; i <= m; i++)
        for(int j = 0; j < fr[i]; j++)
            a[poz++] = i;

}
//RADIXSORT
void countsort_for_radix(vector <int>& a, int mx, int p, int b){

    vector<vector<int>> B(b);

    for (int i = 0; i < a.size(); i++)
        B[(a[i]/p)%10].push_back(a[i]);

    int poz = 0;

    for (int i = 0; i < B.size(); i++)
        for(int j = 0; j < B[i].size(); j++)
            a[poz++] = B[i][j];
}
void radixsort(vector<int>& a, int b)
{
    int mx = maxim(a);
    for (int p = 1; mx/p > 0; p*=10)
        countsort_for_radix(a, mx, p, b);
}
//MERGESORT
void mergesort1(vector<int>&a, int l, int m, int r)
{
    vector<int> Left, Right;

    for (int i = l; i <= m; i++)
        Left.push_back(a[i]);

    for (int i = m + 1; i <= r; i++)
        Right.push_back(a[i]);

    int i = 0,
        j = 0,
        k = l;

    while (i < Left.size() && j < Right.size()){
        if (Left[i] < Right[j])
            a[k++] = Left[i++];
        else
            a[k++] = Right[j++];

    }

    while (i < Left.size())
        a[k++] = Left[i++];

    while (j < Right.size())
        a[k++] = Right[j++];
}

void mergesort(vector<int>&a ,int l, int r)
{
    if(l<r){
        int m = l+ (r-l)/2;
        mergesort(a,l,m);
        mergesort(a,m+1,r);
        mergesort1(a,l,m,r);
    }
}
//QUICKSORT
int part (vector<int>&a, int low, int high)
{
    int pivot = a[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return (i + 1);
}
void quicksort(vector<int>&a, int low, int high)
{
    if (low < high)
    {
        int p = part(a, low, high);
        quicksort(a, low, p - 1);
        quicksort(a, p + 1, high);
    }
}

//calculam timpul de sortare
void time(auto start,auto ends,vector<int> a)
{
    if (test_sort(a) == 0)
            cout<< "Nu se poate sorta ";
    else cout << "Timp in millisecunde : "<< chrono::duration<double>(ends-start).count()<< " ms ";
}


int main() {

    ifstream f("teste.in");
    vector<int> a;
    int n, teste, p, nr_max, i=0;
    cout<<"Numarul de teste dorite: ";
    f >> teste;
    cout<<teste<<endl;
    while ( i++ != teste)
       {
        cout<<endl << "Testul numarul "<<i<<endl;
        f >> n;
        n = pow(10,n);
        cout << "Vom sorta "<< n <<" numere"<<endl;
        f >> nr_max;
        cout << "Numarul maxim este: "<< nr_max<<endl;

        //SORTARE C++
        if (n < pow(10,7)){
            generate_a(a, n, nr_max);
            auto start0 = chrono::system_clock::now();
            sort(a.begin(), a.end());
            auto ends0 = chrono::system_clock::now();
            time(start0,ends0,a);
            cout<< "pentru sortarea in C++"<<endl;
        }
        else
            cout << "Timpul de executie este prea mare si s-a oprit pentru sortarea din C++." << endl;

        //BUBBLESORT
        if (n < pow(10,5)){
            generate_a(a,n,nr_max);
            auto start = chrono::system_clock::now();
            bubblesort(a);
            auto ends = chrono::system_clock::now();
            time(start,ends,a);
            cout<< "pentru Bubblesort"<<endl;
        }
        else
            cout << "Timpul de executie este prea mare si s-a oprit pentru Bubblesort." << endl;

        //COUNTSORT
        if (n < pow(10,11)){
            generate_a(a,n,nr_max);
            auto start1 = chrono::system_clock::now();
            countsort(a);
            auto ends1 = chrono::system_clock::now();
            time(start1,ends1,a);
            cout<< "pentru Countsort"<<endl;
        }
        else
            cout << "Timpul de executie este prea mare si s-a oprit pentru Countsort." << endl;

        //RADIXSORT
        if (n < pow(10,9)){
            generate_a(a,n,nr_max);
            auto start2 = chrono::system_clock::now();
            radixsort(a,10);
            auto ends2 = chrono::system_clock::now();
            time(start2,ends2,a);
            cout<< "pentru Radixsort"<<endl;
        }
        else
            cout << "Timpul de executie este prea mare si s-a oprit pentru Radixsort." << endl;

        //MERGESORT
        if (n < pow(10,8)){
            generate_a(a,n,nr_max);
            auto start3 = chrono::system_clock::now();
            mergesort(a, 0, a.size() - 1);
            auto ends3 = chrono::system_clock::now();
            time(start3,ends3,a);
            cout<< "pentru Mergesort"<<endl;
        }
        else
            cout << "Timpul de executie este prea mare si s-a oprit pentru Mergesort." << endl;

        //QUICKSORT
        if (n < pow(10,7)){
            generate_a(a,n,nr_max);
            auto start4 = chrono::system_clock::now();
            quicksort(a, 0, a.size() - 1);
            auto ends4 = chrono::system_clock::now();
            time(start4,ends4,a);
            cout<< "pentru Quicksort"<<endl;
        }
        else
            cout << "Timpul de executie este prea mare si s-a oprit pentru Quicksort." << endl;
       }

}
