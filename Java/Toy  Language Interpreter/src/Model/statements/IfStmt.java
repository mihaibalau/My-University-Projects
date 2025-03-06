package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myStack.MyIStack;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.BoolType;
import Model.types.Type;
import Model.values.BoolValue;
import Model.values.Value;

public class IfStmt implements IStmt{

    Exp exp;
    IStmt thenS;
    IStmt elseS;

    public IfStmt(Exp e, IStmt t, IStmt el){
        exp = e;
        thenS = t;
        elseS = el;
    }
    public String toString(){
        return "If ("+exp.toString()+ ") {" +thenS.toString()+ "} \n Else {" +elseS.toString()+ "}";
    }

    @Override
    public IStmt deepCopy() {
        return new IfStmt(this.exp.deepCopy(), this.thenS.deepCopy(), this.elseS.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typeExp = exp.typeCheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            thenS.typeCheck(typeEnv.clone());
            elseS.typeCheck(typeEnv.clone());
            return typeEnv;
        }
        else
            throw new MyException("The IF type check failed");
    }

    @Override
    public PrgState execute(PrgState state) throws MyException{
        MyIStack<IStmt> stk = state.getExeStack();
        MyIDict<String, Value> dict = state.getSymTable();
        Value val = exp.eval(dict, state.getHeap());

        if(!val.getType().toString().equals(new BoolType().toString()))
            throw new MyException(("Invalid condition verification!"));

        BoolValue v = (BoolValue) val;
        if(v.getVal())
            stk.push(thenS);
        else
            stk.push(elseS);
        return null;
    }
}

