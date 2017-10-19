#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    deque<int>* que = new deque<int>();
    deque<int>::iterator it;

    cout << que->size() << endl;

    for(int i = 0; i < 10; i++){
        que->push_back(i);
    }


    cout << que->size() << endl;

    for(it = que->begin(); it != que->end(); it++){
        cout << *it << " ";
    }

    cout << endl;

    que->pop_front();

    cout << que->size() << endl;

    for(it = que->begin(); it != que->end(); it++){
        cout << *it << " ";
    }

    cout << endl;

    deque<int>* que2 = new deque<int>();

    que2->assign(que->begin(), que->end());

    que->pop_front();

    cout << que2->size() << endl;

    for(deque<int>::reverse_iterator rit = que2->rbegin(); rit != que2->rend(); rit++){
        cout << *rit << " ";
    }

    cout << endl;

    it = que->begin();
    int a = *it;
    if(find(que->begin(), que->end(), a) != que->end()){
        cout << a << endl;
    }

    return 0;
}
