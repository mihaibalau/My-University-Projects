package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.Type;
import Model.values.Value;
import Model.dataStructures.myDictionary.MyIDict;

public interface Exp {
    Value eval(MyIDict<String,Value> tbl, MyIHeap<Integer,Value> hp) throws MyException;

    Type typeCheck(MyIDict<String, Type> typeEnv) throws MyException;
    String toString();
    Exp deepCopy();
}
