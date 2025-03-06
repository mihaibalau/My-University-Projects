package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.prgState.PrgState;
import Model.types.Type;


public interface IStmt {
    PrgState execute(PrgState state) throws MyException, MyIOException;
    String toString();
    IStmt deepCopy();
    MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException;
}
