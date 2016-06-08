/*This program checks if the brackets are balanced in a given code and
returns the position of the unbalanced bracket in the order of first unbalanced
 closing bracket, first unbalanced opening bracket and if no unbalanced brackets
 it returns success
 */

#include <iostream>
#include <stack>
#include <string>

//Initialize a structure element of bracket that stores the bracket type and
//position. This structure element is used in the stack
struct Bracket {
    Bracket(int type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {

    std::string text;
    getline(std::cin, text);

    int error_position; //Counter to keep track of the first unbalanced bracket position
    bool error = false; //Error flag
    int first_open_bracket_position; //Counter that tracks the first open bracket position

    std::stack <Bracket> opening_brackets_stack;

    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        struct Bracket bracket1(next,position);

        if (next == '(' || next == '[' || next == '{') {
            //If the stack is empty then the first open bracket is the current position
            if(opening_brackets_stack.empty()){
              first_open_bracket_position = position;
            }
            //Push this bracket element into the stack
            opening_brackets_stack.push(bracket1);
        }

        if (next == ')' || next == ']' || next == '}') {

            //If the stack is empty, then a first closing bracket is an unbalanced string
            if(opening_brackets_stack.empty()){
              //std::cout<<"It is an Empty Stack"<<std::endl; //For Debugging
              error_position = position+1;
              error= true;
              break;
            }

            else{
              //Else Check if the top bracket of the stack is the correct opening bracket of
              //the current closing bracket. If yes, remove it.
              if(opening_brackets_stack.top().Matchc(next)){
                opening_brackets_stack.pop();
              }
              //If no, then it is an unbalanced string.Return the position
              else{
                //std::cout<<"Wrong closing bracket"<<std::endl; //For Debugging
                error=true;
                error_position=position+1;
                break;
              }

            }

        }

    }

    //Print the answer
    if (error){
      //std::cout<<"Closing Bracket Error"<<std::endl; // For Debugging
      std::cout<<error_position<<std::endl;
    }
    else if(!opening_brackets_stack.empty()){
      //std::cout<<"Opening Bracket Error"<<std::endl;  //For Debugging
      std::cout<<first_open_bracket_position+1<<std::endl;
    }
    else{
      std::cout<<"Success"<<std::endl;
    }
    return 0;
}
