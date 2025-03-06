package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.BoolType;
import Model.types.IntType;
import Model.types.Type;
import Model.values.*;
import Model.dataStructures.myDictionary.MyIDict;

public class LogicExp implements Exp{
    Exp e1;
    Exp e2;
    int op; // 1 - AND ; 2 - OR

    public LogicExp(Exp _e1, Exp _e2, int _op){
        this.e1 = _e1;
        this.e2 = _e2;
        this.op = _op;
    }

    public Value eval(MyIDict<String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyException{

        Value v1, v2;
        v1 = e1.eval(tbl, hp);
        if(v1.getType().equals(new BoolType())){
            v2 = e2.eval(tbl, hp);
            if(v2.getType().equals((new BoolType()))){

                BoolValue b1 = (BoolValue) v1;
                BoolValue b2 = (BoolValue) v2;

                if(op == 1){
                    if(b1.getVal() && b2.getVal())
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else if(op == 2){
                    if(b1.getVal() || b2.getVal())
                        return new BoolValue(true);
                    else
                        return new BoolValue(false);
                }
                else
                    throw new MyException("Unknown operation!");

            }
            else
                throw new MyException("Second operand doesn't return a boolean value!");
        }
        else
            throw  new MyException("First operand doesn't return a boolean value!");
    }

    @Override
    public Type typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1 = e1.typeCheck(typeEnv);
        typ2 = e2.typeCheck(typeEnv);
        if(!typ1.equals(new BoolType()))
            throw new MyException("First operand from arithmetic expression isn't boolean.");
        if(!typ2.equals(new BoolType()))
            throw new MyException("First operand from arithmetic expression isn't boolean.");
        return new BoolType();
    }

    @Override
    public String toString() {
        return "LogicExpression{E1: " + this.e1 + " | Op: " + this.op + " | E2: " + this.e2 + "}";
    }

    @Override
    public Exp deepCopy() {
        return new LogicExp(this.e1.deepCopy(), this.e2.deepCopy(), this.op);
    }
}
