package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.IntType;
import Model.types.StringType;
import Model.types.Type;
import Model.values.IntValue;
import Model.values.StringValue;
import Model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class readFile implements IStmt{

    Exp exp;
    String id;

    public readFile(Exp _exp, String _id){
        this.exp = _exp;
        this.id = _id;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {
        MyIDict<String, Value> symTbl = state.getSymTable();
        MyIDict<StringValue, BufferedReader> fileTbl = state.getFileTable();

        if(!symTbl.isDefined(this.id))
            throw new MyException("The variable from readFile isn't declared in symTbl!");
        if(!symTbl.lookup(this.id).getType().equals(new IntType()))
            throw new MyException("The variable from readFile isn't declared as IntType!");

        Value val = exp.eval(symTbl, state.getHeap());
        Type typeId = val.getType();
        if(!typeId.toString().equals(new StringType().toString()))
            throw new MyException("The path from readFile isn't a string!");

        StringValue filePath = (StringValue) val;
        if(!fileTbl.isDefined(filePath))
            throw new MyException("The file from which you wasn't to read wasn't opened!");

        BufferedReader br;
        br = fileTbl.lookup(filePath);

        try {
            String line = br.readLine();
            IntValue intValue;

            if (line == null) {
                intValue = new IntValue(0);
            } else {
                try {
                    intValue = new IntValue(Integer.parseInt(line));
                } catch (NumberFormatException e) {
                    throw new MyException("Invalid integer format in file!");
                }
            }
            symTbl.update(this.id, intValue);

        }
        catch (IOException e){
            throw new MyIOException(e.toString());
        }
        return null;
    }

    @Override
    public String toString() {
        return "ReadFile{" + this.exp.toString() + ", " + this.id + "}";
    }

    @Override
    public readFile deepCopy() {
        return new readFile(exp.deepCopy(), id);
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.lookup(id);
        Type typeExp = exp.typeCheck(typeEnv);
        if (!typeExp.equals(new StringType())) {
            throw new MyException("ReadFileStmt: expression must be a string");
        }
        if (!typeVar.equals(new IntType())) {
            throw new MyException("ReadFileStmt: variable type must be integer");
        }
        return typeEnv;
    }
}
