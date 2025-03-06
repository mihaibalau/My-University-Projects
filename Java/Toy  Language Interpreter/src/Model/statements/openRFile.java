package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.StringType;
import Model.types.Type;
import Model.values.StringValue;
import Model.values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class openRFile implements IStmt{

    Exp exp;

    public openRFile(Exp _exp){
        this.exp = _exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {
        MyIDict<String, Value> symTbl = state.getSymTable();
        MyIDict<StringValue, BufferedReader> fileTbl = state.getFileTable();
        Value val = exp.eval(symTbl, state.getHeap());
        Type typeId = val.getType();

        if(!typeId.toString().equals(new StringType().toString()))
            throw new MyException("The file path provided in openRFile isn't a string!");

        StringValue filePath = (StringValue) val;
        if(fileTbl.isDefined(filePath))
            throw new MyException("This file path provided in openRFile already exist in file table!");

        try{
            BufferedReader br = new BufferedReader(new FileReader(filePath.getValue()));
            fileTbl.update(filePath, br);
        } catch (IOException e) {
            throw new MyIOException(e.toString());
        }
        return null;

    }

    @Override
    public openRFile deepCopy() {
        return new openRFile(exp.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        exp.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "openRFile{" + exp.toString() + "}";
    }
}
