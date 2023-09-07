
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

#define MAX 100
#define M1 100
#define M2 100
#define BLOCKS 10

int get_random(int low, int high) { // Funcion que genera numeros aleatorios para hacer las pruebas
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(low, high);
    return distribution(gen);
}

void generaRandomM1(vector<vector<int>> &matA)
{
    for (int i = 0; i < M1; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matA[i].push_back(get_random(0, 10));
        }
    }
}

void generaRandomM2(vector<vector<int>>& matB)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < M2; j++)
        {
            matB[i].push_back(get_random(0, 10));
        }
    }
}


void print(vector<vector<int>> matA)
{
    for (int i = 0; i < matA.size(); i++)
    {
        for (int j = 0; j < matA[0].size(); j++)
        {
            //cout <<" "<< i << " - " << j;
            cout << matA[i][j] << " ";
        }cout << endl;
    }
    cout << endl;
}

vector<vector<int>> mult_classic(vector<vector<int>> matA, vector<vector<int>> matB)
{
    vector<vector<int>> result(M1, vector<int>(M2, 0));
    for (int i = 0; i < M1; ++i) {
        for (int j = 0; j < M2; ++j) {
            for (int k = 0; k < MAX; ++k) {
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    return result;
}

vector<vector<int>> blocks(vector<vector<int>> matA, vector<vector<int>> matB, int b)
{
    vector<vector<int>> result(M1, vector<int>(M2, 0));
    for (int ii = 0; ii < MAX; ii += b) {
        for (int jj = 0; jj < MAX; jj += b) {
            for (int kk = 0; kk < MAX; kk += b) {
                for (int i = ii; i < ii + b; i++) {
                    for (int j = jj; j < jj + b; j++) {
                        for (int k = kk; k < kk + b; k++) {
                            result[i][j] += matA[i][k] * matB[k][j];
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main()
{
	vector<vector<int>> matA(M1), matB(MAX);
    generaRandomM1(matA);
    generaRandomM2(matB);
    //print(matA);
    //print(matB);

    auto start = std::chrono::system_clock::now();
    vector<vector<int>> resultado = mult_classic(matA, matB);
    //vector<vector<int>> resultado = blocks(matA, matB, BLOCKS);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<float> duration = end - start;
    //print(resultado);

    cout << "Duracion metodo bloques: " << duration.count() << " segundos" << endl;
}
