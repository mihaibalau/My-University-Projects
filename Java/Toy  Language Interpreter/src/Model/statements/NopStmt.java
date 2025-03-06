package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.prgState.PrgState;
import Model.types.Type;

public class NopStmt implements IStmt{

    public NopStmt(){}

    @Override
    public String toString(){
        return "NopStatement{}";
    }

    @Override
    public IStmt deepCopy() {
        return new NopStmt();
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        return null;
    }
}
