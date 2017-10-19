#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int>* vec = new vector<int>();

    vec->push_back(10);
    vec->reserve(10);
    vec->push_back(12);

    vec->erase(vec->begin());

    cout << vec->size() << endl;
    cout << vec->capacity() << endl;

    for(int i = 0; i < vec->size(); i++){
        cout << vec->at(i) << " " << endl;
    }
    return 0;
}
