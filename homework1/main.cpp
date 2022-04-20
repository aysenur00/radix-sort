#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

bool Reading_Numbers(vector<int> &vec, const char s[])
{
    ifstream input(s);
    int st;

    if (!input.is_open())
    {
        return false;
    }

    while (!input.eof())
    {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek()))
            input.get();
    }
    input.close();
    return true;
}

void OutputResultToFile(int *arr, unsigned int size)
{
    ofstream output("out.txt");

    for (int i = 0; i < size; i++)
        output << arr[i] << ' ';
}
int getMax(vector<int> A)
{
    int max = A[0];
    for (int i = 1; i < A.size(); i++)
        if (A[i] > max)
            max = A[i];
    return max;
}

void countingSort(vector<int> &A, int exp)
{
    vector<int> B(A.size(), 0);
    int min = 0;
    int max = 0;

    for (unsigned int m = 0; m < A.size(); m++)
    {
        if (A[m] < min)
            min = A[m];
    }

    for (unsigned int m = 0; m < A.size(); m++)
    {
        if (A[m] > max)
            max = A[m];
    }

    vector<int> C(max - min + 1, 0);

    for (int i = 0; i < A.size(); i++)
    {
        C[(A[i] / exp) % 10]++;
    }

    cout << endl;
    for (int i = 1; i < C.size(); i++)
    {
        C[i] = C[i] + C[i - 1];
    }

    for (int i = A.size() - 1; i > -1; i--)
    {
        B[C[(A[i] / exp) % 10] - 1] = A[i];
        C[(A[i] / exp) % 10]--;
    }

    for (int i = 0; i < A.size(); i++)
    {

        // cout << B[i] << " " << endl;

        A[i] = B[i];
    }
}
void print(vector<int> A)
{
    for (int i = 0; i < A.size(); i++)
        cout << A[i] << " ";
    cout << endl;
}
void radixSort(vector<int> &A)
{
    int m = getMax(A);
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        countingSort(A, exp);
    }
}
int main(int argc, const char *argv[])
{
    vector<int> A;

    if (argc < 2)
        return 0;
    if (!Reading_Numbers(A, argv[1]))
        return 0;

    radixSort(A);
    print(A);
    OutputResultToFile(&A[0], A.size());

    return 0;
}