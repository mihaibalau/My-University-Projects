package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.BoolType;
import Model.types.IntType;
import Model.types.Type;
import Model.values.BoolValue;
import Model.values.IntValue;
import Model.values.Value;

public class RelationalExp implements Exp{

    Exp e1, e2;
    int op;

    public RelationalExp(Exp _e1, Exp _e2, int _op){
        this.e1 = _e1;
        this.e2 = _e2;
        this.op = _op;
    }

    @Override
    public Value eval(MyIDict<String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyException{
        Value v1, v2;
        v1 = e1.eval(tbl, hp);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl, hp);
            if(v2.getType().equals(new IntType())){
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int n1, n2;

                n1 = i1.getVal();
                n2 = i2.getVal();

                if(op == 1)
                    return new BoolValue(n1 < n2);
                else if(op == 2)
                    return new BoolValue(n1 <= n2);
                else if(op == 3)
                    return new BoolValue(n1 == n2);
                else if(op == 4)
                    return new BoolValue(n1 != n2);
                else if(op == 5)
                    return new BoolValue(n1 > n2);
                else if(op == 6)
                    return new BoolValue(n1 >= n2);
                else
                    throw new MyException("Unknown operation!");
            }
            else
                throw new MyException("Second operand is not an integer!");
        }
        else
            throw new MyException("First operand is not an integer!");
    }

    @Override
    public Type typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1 = e1.typeCheck(typeEnv);
        typ2 = e2.typeCheck(typeEnv);
        if(!typ1.equals(new IntType()))
            throw new MyException("First operand from arithmetic expression isn't integer.");
        if(!typ2.equals(new IntType()))
            throw new MyException("First operand from arithmetic expression isn't integer.");
        return new BoolType();
    }

    @Override
    public Exp deepCopy() {
        return null;
    }

    @Override
    public String toString(){
        String s = " unknown code ";
        if(this.op == 1)
            s = " < ";
        else if(this.op == 2)
            s = " <= ";
        else if(this.op == 3)
            s = " == ";
        else if(this.op == 4)
            s = " != ";
        else if(this.op == 5)
            s = " > ";
        else if(this.op == 6)
            s = " >= ";
        return this.e1 + s + this.e2;
    }
}
