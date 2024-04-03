//
// Created by Mihai on 3/31/2024.
//

#ifndef ALGORITMI_GENETICI_GENERATION_H
#define ALGORITMI_GENETICI_GENERATION_H

#endif //ALGORITMI_GENETICI_GENERATION_H
#include "Headers/Chromosome.h"
#include "Headers/Interval.h"
#include "Headers/Equation.h"
#include "Headers/NullStream.h"
#include <iomanip>
#include <vector>
#include <cmath>
using std::vector;
using std::cout;

class Generation{
private:
    static std::uniform_real_distribution<double> disX; // Uniform distribution [0, 1)
    vector<Chromosome>chroms;
    Interval interval;
    Equation equation;
    vector<double>probabInterval;
    int dimPop;
    int precision;
    double crossProbab;
    double mutProbab;
    int generations;

    // Helpers
    void selectChroms();
    void crossChroms(vector<Chromosome>& v, const vector<int>& ind);
    int binarySearch(double u);

public:
    Generation(int dimPop, const Interval& interval, const Equation& equation,
               int precision, double crossProbab, double mutProbab, int generations);

    Chromosome maximum();
    void printChroms();
    void printProbabSelectie();
    void printCrossSelection();
    void printMutation();
    void allSteps();
    void start();
};
std::uniform_real_distribution<double> Generation::disX(0,1); // Uniform distribution [0, 1)

Generation::Generation(int dimPop, const Interval& interval, const Equation& equation,
                       int precision, double crossProbab, double mutProbab, int generations=1) {

    this->interval = interval;
    this->equation = equation;
    this->precision = precision;
    this->dimPop = dimPop;
    this->crossProbab = crossProbab;
    this->mutProbab = mutProbab;
    this->generations = generations;
    this->probabInterval = vector<double>(dimPop);
    this->disX = std::uniform_real_distribution<double>(this->interval.a, this->interval.b);

    // get the size of a Chromosome
    int size = ceil(log2((interval.b - interval.a) * pow(10,precision) + 1));

    // create Chromosomes
    while(dimPop--){
        this->chroms.emplace_back(Chromosome(this->disX(gen), this->precision, this->interval.a, this->interval.b));
    }

}

Chromosome Generation::maximum() {
    double max = this->interval.a;
    Chromosome temp;
    for(int i = 0 ; i < this->chroms.size() ; i++)
        if(this->chroms[i].getFx() > max){
            max = this->chroms[i].getFx();
            temp = this->chroms[i];
        }
    return temp;
}

void Generation::printChroms() {
    for(int i = 0 ; i < this->chroms.size() ; i++){
        // daca le am calculat deja skip
        if(this->chroms[i].getSelectionProb() == -1){
            this->chroms[i].setGenes(this->chroms[i].encode(this->interval.a,this->interval.b,this->precision));
            this->chroms[i].setFx(equation.f(this->chroms[i].getX()));
        }

        cout<<std::setw(3);
        cout<<i+1<<": "<<this->chroms[i].getGenes()<<"  ";
        cout << "x = " << std::fixed << std::setprecision(10) << std::setw(10) << this->chroms[i].getX() << "  "; // Set precision, width, and fixed point
        cout << "f = " << this->chroms[i].getFx() << std::endl;
    }
    cout<<std::endl<<std::endl;
}

int Generation::binarySearch(double u) {
    int left = 0;
    int right = this->probabInterval.size() - 1;

    while(left <= right){
        int mid = left + (right-left)/2;

        if(this->probabInterval[mid] == u)
            return mid;
        if(this->probabInterval[mid] < u)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}

void Generation::selectChroms(){
    // best fitness jumps over selection
    Chromosome maxChr = maximum();
    vector<Chromosome> afterSelection;

    for(int i = 0 ; i < this->dimPop ; i++){
        if(this->chroms[i] == maxChr){
            afterSelection.push_back(this->chroms[i]);
            continue;
        }

        // generate a random chance
        double u = dis(gen);

        // find the interval coresponding to a chromosome
        int chrIndex = binarySearch(u);
        afterSelection.push_back(this->chroms[chrIndex]);
        cout<<"u = "<<u<<" selectam cromozomul "<<chrIndex+1<<std::endl;
    }
    this->chroms = afterSelection;
}

void Generation::printProbabSelectie() {
    // sum f(xi)
    double sum = 0;
    for(int i = 0 ; i < this->chroms.size() ; i++)
        sum += this->chroms[i].getFx();

    // Pi = f(xi) / sum(f(xi))
    for(int i = 0 ; i < this->chroms.size() ; i++)
        this->chroms[i].setSelectionProb(this->chroms[i].getFx() / sum);

    sum = 0;
    cout<<"Probabilitati selectie\n";
    for(int i = 0 ; i < this->chroms.size() ; i++){
        cout<<"cromozom  "<<i+1<<" probabilitate "<< this->chroms[i].getSelectionProb()<<std::endl;
        sum += this->chroms[i].getSelectionProb();
        this->probabInterval[i] = sum;
    }

    cout<<"\nIntervale probabilitati selectie\n";
    for(int i = 0 ; i < this->chroms.size() ; i++)
        cout<<this->probabInterval[i]<<" ";

    cout<<std::endl;
}

void Generation::crossChroms(vector<Chromosome>& v,const vector<int>& ind) {

    for(int i = 0 ; i+1 < v.size() ; i+= 2) {
        // get a cross point
        int crossPoint = rand() %  v[i].size();

        cout<<"Recombinare dintre cromozomul "<<ind[i]<<" cu cromozomul "<<ind[i+1] << std::endl;
        cout<<v[i].getGenes()<<" "<<v[i+1].getGenes()<<" punct "<<crossPoint<<std::endl;

        v[i].crossover(v[i + 1], crossPoint);
        cout<<"Rezultat "<<v[i].getGenes()<<" "<<v[i+1].getGenes()<<std::endl;

        v[i].setX(v[i].decode(this->interval.a, this->interval.b));
        v[i+1].setX(v[i+1].decode(this->interval.a, this->interval.b));

        v[i].setFx(equation.f(v[i].getX()));
        v[i+1].setFx(equation.f(v[i+1].getX()));

    }
}

void Generation::printCrossSelection(){

    vector<Chromosome> afterCross;
    vector<Chromosome> toBeCrossed;
    vector<int> chromsInd;
    for(int i = 0 ; i < this->chroms.size() ; i++){
        // generate a random chance at crossover
        double u = dis(gen);
        cout<<i+1<<". "
            <<"x= "<<this->chroms[i].getX()<<" "
            <<"u= "<<u;
        if(u < this->crossProbab) {
            cout << " <" << this->crossProbab;
            toBeCrossed.push_back(this->chroms[i]);
            chromsInd.push_back(i+1);
        }
        else
            afterCross.push_back(this->chroms[i]);
        cout<<std::endl;
    }

    // cross the selected ones
    crossChroms(toBeCrossed, chromsInd);

    for(int i = 0 ; i < toBeCrossed.size() ; i++)
        afterCross.push_back(toBeCrossed[i]);

    this->chroms = afterCross;
}

void Generation::printMutation() {
    bool checkAny = false;
    cout<<"Au fost modificati cromozomii:\n";
    for(int i = 0 ; i < this->chroms.size() ; i++)
        if(this->chroms[i].mutationIterative(this->mutProbab)) {
            cout << i+1 << '\n';
            this->chroms[i].setX(this->chroms[i].decode(this->interval.a, this->interval.b));
            this->chroms[i].setFx(equation.f(this->chroms[i].getX()));
            checkAny = true;
        }
    if(!checkAny) cout<<"Niciunul\n";
}

void Generation::allSteps(){

    // selection
    printProbabSelectie();
    selectChroms();
    cout<<"\nDupa selectie\n";
    printChroms();

    // crossover
    cout<<"Probabilitatea de incrucisare "<<this->crossProbab<<std::endl;
    printCrossSelection();
    cout<<"Dupa recombinare\n";
    printChroms();
    // mutation
    cout<<"Probabilitate de mutatie pentru fiecare gena "<<this->mutProbab<<std::endl;
    printMutation();
    printChroms();

    cout<<"Evolutia Maximului\n";
    printf("%f\n",maximum().getFx());
}

void Generation::start() {

    // init x, fx
    cout<<"Populatia initiala\n";
    printChroms();
    allSteps();

    NullBuffer nullbfr;
    std::ostream nullStream(&nullbfr);
    std::streambuf *coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(nullStream.rdbuf());

    for(int i = 1 ; i < this->generations ; i++){
        allSteps();
    }
    std::cout.rdbuf(coutBuffer);
}


/// randomizeaza cum se aleg astia la cross over
