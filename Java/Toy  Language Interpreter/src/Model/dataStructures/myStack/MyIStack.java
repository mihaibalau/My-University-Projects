package Model.dataStructures.myStack;

import Exceptions.MyException;

import java.util.List;

public interface MyIStack <T> {
    T pop() throws MyException;
    void push(T v);

    boolean isEmpty();

    List<T> getReverse();

    T peek();

    int size();
}
