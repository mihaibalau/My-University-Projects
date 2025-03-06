package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myStack.MyIStack;
import Model.prgState.PrgState;
import Model.types.Type;

public class CompStmt implements  IStmt{
    IStmt first;
    IStmt snd;

    public CompStmt(IStmt _first, IStmt _second){
        this.first = _first;
        this.snd = _second;
    }

    public String toString() {
        return this.first.toString() + "; " + this.snd.toString();
    }

    public IStmt getFirst(){
        return first;
    }

    public IStmt getSecond(){
        return snd;
    }

    @Override
    public IStmt deepCopy() {
        return new CompStmt(this.first.deepCopy(), this.snd.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        return snd.typeCheck(first.typeCheck(typeEnv));
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getExeStack();
        stk.push(snd);
        stk.push(first);
        return null;
    }
}
