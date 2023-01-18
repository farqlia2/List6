//
// Created by julia on 1/10/2023.
//

#ifndef LIST6_COUNTER_H
#define LIST6_COUNTER_H

class Counter
{
public:

    static Counter MOCK_COUNTER;

    Counter();
    int incr();
    int decr();
    int get();

private:
    int count;
};




#endif //LIST6_COUNTER_H
