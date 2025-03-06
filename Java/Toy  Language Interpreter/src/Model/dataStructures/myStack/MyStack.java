package Model.dataStructures.myStack;

import Exceptions.MyException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Stack;

public class MyStack <T> implements MyIStack <T> {

    Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<T>();
    }

    @Override
    public T pop() throws MyException{
        if (stack.empty())
            throw new MyException("Your stack is empty!");
        return this.stack.pop();
    }

    @Override
    public void push(T v) {
        this.stack.push(v);
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public String toString() {
        StringBuilder returnValue = new StringBuilder();
        for(T elem : this.stack)
            returnValue.append(elem.toString()).append("\n");
        return returnValue.toString();
    }

    @Override
    public List<T> getReverse(){
        List<T> reversedList = new ArrayList<>(stack);
        Collections.reverse(reversedList);
        return reversedList;
    }

    @Override
    public T peek(){
        return stack.peek();
    }

    @Override
    public int size() {
        return this.stack.size();
    }
}
