package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.RefType;
import Model.types.Type;
import Model.values.RefValue;
import Model.values.Value;

public class readHeapExp implements Exp{

    Exp exp;

    public readHeapExp(Exp _exp){
        this.exp = _exp;
    }


    @Override
    public Value eval(MyIDict<String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyException {
        Value val;
        try{
            val = this.exp.eval(tbl, hp);
        } catch (MyException error) {
            throw new MyException(error.toString());
        }

        if(!(val instanceof RefValue))
            throw new MyException("Value eval from HeapExp failed!");

        RefValue rVal = (RefValue) val;
        Integer addr = rVal.getAddr();
        if(! hp.isDefined(addr))
            throw new MyException("The address from HeapExp Eval is invalid");
        return hp.lookup(addr);
    }

    @Override
    public Type typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typ = exp.typeCheck(typeEnv);
        if(typ instanceof RefType refT){
            return refT.getInner();
        }
        else
            throw new MyException("The rH argument is not a Ref Type");
    }

    @Override
    public Exp deepCopy() {
        return new readHeapExp(this.exp.deepCopy());
    }

    @Override
    public String toString() {
        return "readHeap(" + this.exp + ")";
    }
}
