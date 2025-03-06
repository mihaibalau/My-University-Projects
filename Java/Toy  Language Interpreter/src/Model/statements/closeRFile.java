package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.BoolType;
import Model.types.StringType;
import Model.types.Type;
import Model.values.IntValue;
import Model.values.StringValue;
import Model.values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class closeRFile implements IStmt{

    Exp exp;

    public closeRFile(Exp _exp){
        this.exp = _exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {

        MyIDict<String, Value> symTbl = state.getSymTable();
        MyIDict<StringValue, BufferedReader> fileTbl = state.getFileTable();
        Value val = exp.eval(symTbl, state.getHeap());
        Type typeId = val.getType();

        if(!typeId.toString().equals(new StringType().toString()))
            throw new MyException("The file path provided in closeRFile isn't a string!");

        StringValue filePath = (StringValue) val;
        if(!fileTbl.isDefined(filePath))
            throw new MyException("This file path provided in closeRFile doesn't exist in file table!");

        BufferedReader br;
        br = fileTbl.lookup(filePath);

        try {
            br.close();
            fileTbl.remove(filePath);
        }
        catch (IOException e){
            throw new MyIOException(e.toString());
        }

        return null;
    }

    @Override
    public closeRFile deepCopy() {
        return new closeRFile(exp.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typ = exp.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "closeRFile{" + exp.toString() + "}";
    }
}
