package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.Type;
import Model.values.Value;
import Model.dataStructures.myDictionary.MyIDict;

public class ValueExp implements Exp{
    Value e;

    public ValueExp(Value val){
        this.e = val;
    }

    public Value eval(MyIDict<String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyException{
        return this.e;
    }

    @Override
    public Type typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        return e.getType();
    }

    @Override
    public String toString() {
        return this.e.toString();
    }

    @Override
    public Exp deepCopy() {
        return new ValueExp(this.e);
    }
}
