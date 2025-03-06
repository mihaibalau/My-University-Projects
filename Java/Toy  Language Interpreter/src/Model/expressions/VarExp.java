package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.Type;
import Model.values.Value;

public class VarExp implements Exp{
    String id;

    public VarExp(String _id){
        this.id = _id;
    }

    @Override
    public Value eval(MyIDict <String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyException{
        return tbl.lookup(id);
    }

    @Override
    public Type typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        return typeEnv.lookup(id);
    }

    @Override
    public String toString(){
        return this.id;
    }

    @Override
    public Exp deepCopy() {
        return new VarExp(this.id);
    }
}
