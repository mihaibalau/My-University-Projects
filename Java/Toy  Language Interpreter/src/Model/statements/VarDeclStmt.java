package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.prgState.PrgState;
import Model.types.Type;
import Model.values.Value;

public class VarDeclStmt implements IStmt{
    String name;
    Type type;

    public VarDeclStmt(String _name, Type _type){
        this.name = _name;
        this.type = _type;
    }
    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDict <String, Value> symTable = state.getSymTable();

        if(symTable.isDefined(this.name))
            throw new MyException("Imputed variable is already defined!");
        else
            symTable.update(this.name, this.type.defaultValue());

        return null;
    }

    @Override
    public String toString(){
        return this.type.toString() + " " + this.name ;
    }

    @Override
    public IStmt deepCopy() {
        return new VarDeclStmt(this.name, this.type);
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        typeEnv.update(name, type);
        return typeEnv;
    }
}
