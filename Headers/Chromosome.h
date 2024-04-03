//
// Created by Mihai on 3/31/2024.
//

#ifndef ALGORITMI_GENETICI_CHROMOSOME_H
#define ALGORITMI_GENETICI_CHROMOSOME_H

#endif //ALGORITMI_GENETICI_CHROMOSOME_H

#include <string>
#include <random>
#include <bitset>
using std::string;
std::random_device rd; // Seed for the random engine
std::mt19937 gen(rd()); // Mersenne Twister engine
std::uniform_real_distribution<double> dis(0.0, 1.0); // Uniform distribution [0, 1)


class Chromosome{
private:
    string genes;
    double x;
    double fx;
    double selectionProb;
public:
    // Constructors
    Chromosome();

    Chromosome(double n, int precision, double left, double right);
    //give the length
    //Chromosome(int bits);

    Chromosome& operator=(const Chromosome& obj);
    bool operator==(const Chromosome& obj);

    // Getters
    //return the genes
    string getGenes()const{return this->genes;}
    double getX()const{return this->x;}
    double getFx()const{return this->fx;}
    double getSelectionProb()const{return this->selectionProb;}

    // Setters
    void setX(const double& x){this->x = x;}
    void setFx(const double& fx){this->fx = fx;}
    void setGenes(const string& genes){this->genes = genes;}
    void setSelectionProb(const double& val){this->selectionProb = val;}

    // Methods
    // cross 2 chromosomes at a given point
    int size(){return this->genes.size();}
    void crossover(Chromosome& obj, const int& crossPoint);

    // rare mutation, give probability in %
    void mutationRare(double mutProbab);
    // iterate the genes and each one has a chance to a bitflip
    bool mutationIterative(double mutProbab);

    // convert to a real number
    double decode(double left, double right);

    // convert to binary representation
    string encode(double left, double right, int precision);
};
Chromosome::Chromosome() {

}
Chromosome::Chromosome(double n, int precision, double left, double right) {
    this->x = n;
    this->selectionProb = -1;
}
//Chromosome::Chromosome(int bits) {
//    while(bits--){
//        this->genes += rand() % 2 == 0 ? '0' : '1';
//    }
//
//    this->selectionProb = -1;
//}

Chromosome& Chromosome::operator=(const Chromosome& obj){
    this->genes = obj.genes;
    this->selectionProb = obj.selectionProb;
    this->fx = obj.fx;
    this->x = obj.x;
    return *this;
}
bool Chromosome::operator==(const Chromosome &obj) {
    return this->fx == obj.fx;
}

void Chromosome::crossover(Chromosome &obj, const int& crossPoint) {
    string aux = this->genes.substr(crossPoint, this->genes.size() - crossPoint);
    this->genes = this->genes.substr(0, crossPoint) + obj.genes.substr(crossPoint, this->genes.size() - crossPoint);
    obj.genes = obj.genes.substr(0, crossPoint) + aux;
}

void Chromosome::mutationRare(double mutProbab) {
    // if it hits, generate a random position for bit-flip
    if(dis(gen) < mutProbab){
        int index = rand() % this->genes.size();
        this->genes[index] = !(this->genes[index] - '0') + '0';
    }
}

// returns true if it got changed
bool Chromosome::mutationIterative(double mutProbab) {
    int cnt = 0;
    for (int i = 0; i < this->genes.size(); i++)
        if (dis(gen) < mutProbab) {
            this->genes[i] = !(this->genes[i] - '0') + '0';
            cnt++;
        }
    return cnt > 0;
}

double Chromosome::decode(double left, double right){
    // find the distance between bins
    double binSize = (right - left) / pow(2,this->genes.size());

    int numberDecimal = 0 ;
    int power = 0;

    for(int i = this->genes.size() - 1 ; i >= 0 ; i--){
        if(this->genes[i] == '1')
            numberDecimal += pow(2,power);
        power++;
    }

    return left + numberDecimal * binSize;
}


string Chromosome::encode(double left, double right, int precision) {
    // get the number of digits
    int digits = ceil(log2((right-left) * pow(10,precision)));

    // find the distance between bins
    double binSize = (right-left) / pow(2,digits);

    int multiplyer = 0;
    while(true){
        if(left + binSize * multiplyer <= this->x && this->x < left + binSize*(multiplyer+1)){
            break;
        }
        else multiplyer++;
    }

    std::bitset<sizeof(int) * 8> binary(multiplyer);
    return binary.to_string().substr(sizeof(int) * 8 - digits);
}
