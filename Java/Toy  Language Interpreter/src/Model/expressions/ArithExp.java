package Model.expressions;

import Exceptions.MyException;
import Model.dataStructures.myHeap.MyIHeap;
import Model.types.IntType;
import Model.types.Type;
import Model.values.IntValue;
import Model.values.Value;
import Model.dataStructures.myDictionary.MyIDict;


public class ArithExp implements Exp{
    Exp e1;
    Exp e2;
    int op; //1 - plus, 2 - minus, 3 - star, 4 - divide

    public ArithExp(char _op, Exp _e1, Exp _e2) {
        this.e1 = _e1;
        this.e2 = _e2;

        if (_op == '+')
            this.op = 1;
        else if (_op == '-')
            this.op = 2;
        else if (_op == '*')
            this.op = 3;
        else if (_op == '/')
            this.op = 4;
    }

    public ArithExp(Exp _e1, Exp _e2, int _op){
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
                    return new IntValue(n1 + n2);
                else if(op == 2)
                    return new IntValue(n1 - n2);
                else if(op == 3)
                    return new IntValue(n1 * n2);
                else if(op == 4){
                    if(n2 == 0)
                        throw new MyException("Division by zero!");
                    else
                        return new IntValue(n1/n2);
                }
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
        Type typ2;
        typ2 = e2.typeCheck(typeEnv);
        if(!typ2.equals(new IntType()))
            throw new MyException("First operand from arithmetic expression isn't integer.");
        return new IntType();
    }

    @Override
    public String toString() {
        String s = " unknown code ";
        if(this.op == 1)
            s = " + ";
        else if(this.op == 2)
            s = " - ";
        else if(this.op == 3)
            s = " * ";
        else if(this.op == 4)
            s = " / ";
        return this.e1 + s + this.e2;
    }

    @Override
    public Exp deepCopy() {
        return new ArithExp(this.e1.deepCopy(), this.e2.deepCopy(), this.op);
    }
}