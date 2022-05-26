#include "calculator.h"

Calculator::Calculator():
    operations_names({"+", "-", "*", "/", "^ (fast)"})
{

}


BigModInt Calculator::calculate(std::size_t op_index, const BigModInt& a, const BigModInt& b){
    switch(op_index){
        case 0:{
            return a+b;
            break;
        }
        case 1:{
            return a-b;
            break;
        }
        case 2:{
            return a*b;
            break;
        }
        case 3:{
            return a/b;
            break;
        }
        case 4:{
            return a/b; // ///////////////// need to add implementation of task 4 fast powering
            break;
        }
    default:
        break;
    }
}
